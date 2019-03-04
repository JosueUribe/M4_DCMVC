/*!===========================================================================*
 * Header Files
 *===========================================================================*/
#include "pwm_thread.h"
#include "sf_message_payloads.h"

/*!===========================================================================*
 * Local Preprocessor #define Constants
 *===========================================================================*/
#define CLOCK_B                     1
#define DEFAULT_DUTY_CYCLE          5
#define DEFAULT_ADC_VALUE         512
#define DELTA_DUTY                  5
#define PWM_THREAD_SLEEP            2 /* Milliseconds to sleep */


/*!===========================================================================*
 * External Type Declarations
 *===========================================================================*/
extern TX_QUEUE g_cdc_queue;
extern const sf_message_post_cfg_t g_post_cfg;
extern const sf_message_acquire_cfg_t g_acquire_cfg;

const sf_message_acquire_cfg_t g_acquire_cfg =
{
    .buffer_keep = false,
};

const sf_message_post_cfg_t g_post_cfg =
{
    .priority = SF_MESSAGE_PRIORITY_NORMAL,
    .p_callback = NULL,
};

/*!===========================================================================*
 * Local Type Declarations
 *===========================================================================*/
static uint8_t duty_cycle = DEFAULT_DUTY_CYCLE;
static uint16_t received_adc_value = DEFAULT_ADC_VALUE; /* to store queued value from ADC thread */
static char send_trace[100]; /* to store debug strings */

UINT tx_status_pwm = TX_SUCCESS;

void pwm_thread_entry(void)
{
    /*Open timer object by calling [R_GPT_TimerOpen] function*/
    g_timer0.p_api->open(g_timer0.p_ctrl, g_timer0.p_cfg);

    /*Auto start is false, so we need to start the timer manually by calling [R_GPT_Start]*/
    g_timer0.p_api->start(g_timer0.p_ctrl);

    while (1)
    {
        tx_status_pwm = tx_queue_receive(&g_cdc_to_pwm_queue, &received_adc_value, TX_WAIT_FOREVER);  //receive adc values from adc_thread_entry
       if (TX_SUCCESS != tx_status_pwm)
       {
           sprintf(send_trace, "Error %d receiving data from queue\r", tx_status_pwm);
           tx_queue_send(&g_cdc_queue, send_trace, TX_NO_WAIT);
       }

       duty_cycle = (uint8_t)(received_adc_value * 100 / 1023);   //convert adc value to percentage value

       g_timer0.p_api->dutyCycleSet(g_timer0.p_ctrl, duty_cycle, TIMER_PWM_UNIT_PERCENT, CLOCK_B);

       /*Console traces*/
       sprintf(send_trace, "Duty Cycle: %d\r", duty_cycle);
       tx_queue_send(&g_cdc_queue, send_trace, TX_NO_WAIT);

       /* Pointers to event message and data */
       sf_message_header_t *p_message  = NULL;
       sf_message_payload_t *p_payload = NULL;
       /* Get buffer from Messaging framework. */
       ssp_err_t err = g_sf_message0.p_api->bufferAcquire(g_sf_message0.p_ctrl, (sf_message_header_t **) &p_message, &g_acquire_cfg, TX_NO_WAIT);

       if (SSP_SUCCESS != err)
       {
           while(1); /* Trap if error */
       }
       else
       {
           /* Creating message in buffer. */
           p_message->event_b.class_code = SF_MESSAGE_EVENT_CLASS_PWM_DATA;
           p_message->event_b.code  = SF_MESSAGE_EVENT_UPDATE_DUTY_CYCLE;
           p_payload = (sf_message_payload_t*)(p_message+1);
           p_payload->pwm_data_payload.Duty_Cycle = duty_cycle;

           /* Posting message. */
           sf_message_post_err_t post_err;
           err = g_sf_message0.p_api->post(g_sf_message0.p_ctrl, (sf_message_header_t *) p_message, &g_post_cfg, &post_err, TX_NO_WAIT);

           if (SSP_SUCCESS != err)
           {
               while(1);
           }
       }
       tx_thread_sleep (PWM_THREAD_SLEEP);
     }
}


/*!===========================================================================
 *
 * @file pwm_thread_entry.c
 *
 * @section RH REVISION HISTORY (top to bottom: first revision to last revision)
 *
 * - 01-Oct-2018 Gpe. Josue Uribe  Rev 1
 *   - Task: Initial_PWM_Generation.
 *
 * - 01-Feb-2019 Victor Alvarado Rev 2
 *   - Task: Implement communication between ADC and PWM
 *
 * - 08-Feb-2019 Victor Alvarado Rev 3
 *   - Task: Add traces for errors receiving data from queue
 *
 * - 25-Feb-2019 Gpe. Josue Uribe  Rev 4
 *   - Task: Use SSP Messaging framework to update duty cycle on the GUI.
 *
 * - 03-Mar-2019 Gpe. Josue Uribe  Rev 5
 *   - Task: Include pointers to Event Message and data in the infinite loop.
 *===========================================================================*/

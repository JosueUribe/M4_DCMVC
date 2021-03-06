/*!===========================================================================*
 * Header Files
 *===========================================================================*/
#include <hall_effect_thread.h>
#include "sf_message_payloads.h"
#include "math.h"

/*!===========================================================================*
 * Local Preprocessor #define Constants
 *===========================================================================*/
#define PERIOD_TIMER_VALUE_MS     1
#define SECONDS_PER_MINUTE        60.0
#define PULSES_PER_TURN           4.0
#define HALL_EFFECT_THREAD_SLEEP  1

/*!===========================================================================*
 * External Type Declarations
 *===========================================================================*/
extern TX_QUEUE g_cdc_queue;
extern const sf_message_post_cfg_t g_post_cfg;
extern const sf_message_acquire_cfg_t g_acquire_cfg;

/*!===========================================================================*
 * Global Type Declarations
 *===========================================================================*/
static uint16_t elapsed_time_ms = 0;
static uint16_t time_ms = PERIOD_TIMER_VALUE_MS;
static uint16_t timer_counts = 0;
static uint16_t pulses_count = 0;
static bool elapsed_time_flag = false;
static char send_trace[100];  //to store debug strings

sf_message_post_err_t post_err;

/*!===========================================================================*
 * Local Type Declarations
 *===========================================================================*/
uint16_t calculate_rpm(void);


/* HALL_EFFECT entry function */
void hall_effect_thread_entry(void)
{
    uint16_t rpm = 0;

    g_external_irq08.p_api->open(g_external_irq08.p_ctrl,g_external_irq08.p_cfg);

    /*Open timer object by calling [R_GPT_TimerOpen] function*/
    g_timer1.p_api->open(g_timer1.p_ctrl, g_timer1.p_cfg);

    /*Auto start is false, so we need to start the timer manually by calling [R_GPT_Start]*/
    g_timer1.p_api->start(g_timer1.p_ctrl);

    /* TODO: add your own code here */
    while (1)
    {
        if(true == elapsed_time_flag)
        {
            rpm = calculate_rpm();
            elapsed_time_flag = false;
            timer_counts = 0;
            pulses_count = 0;
            /*Send value to PID module*/

            /*print console debug traces*/
            sprintf(send_trace, "Elap Time ms: %d, RPMs: %d\r", elapsed_time_ms, rpm);
            tx_queue_send(&g_cdc_queue, send_trace, TX_NO_WAIT);

            /* Pointers to event message and data */
            sf_message_header_t *p_message  = NULL;
            sf_message_payload_t *p_payload = NULL;

            /* Get buffer from Messaging framework. */
            ssp_err_t err = g_sf_message0.p_api->bufferAcquire(g_sf_message0.p_ctrl, (sf_message_header_t **) &p_message, &g_acquire_cfg, TX_NO_WAIT);

            /* Trap if error */
            if (SSP_SUCCESS != err)
            {
                while(1);
            }
            else
            {
                /* Creating message in buffer. */
                p_message->event_b.class_code = SF_MESSAGE_EVENT_CLASS_HALL_EFFECT_FEEDBACK;
                p_message->event_b.code  = SF_MESSAGE_EVENT_HALL_EFFECT_RPMS_MESSAGE;
                p_payload = (sf_message_payload_t*)(p_message+1);
                p_payload->hall_effect_feedback_payload.rpms_to_gui = rpm;

                /* Posting message. */
                err = g_sf_message0.p_api->post(g_sf_message0.p_ctrl, (sf_message_header_t *) p_message, &g_post_cfg, &post_err, TX_NO_WAIT);

                if (SSP_SUCCESS != err)
                {
                    while(1);
                }
            }
        }
        tx_thread_sleep (HALL_EFFECT_THREAD_SLEEP);
    }
}


/*!===========================================================================*
 * Function Declarations

 *===========================================================================*/
uint16_t calculate_rpm(void)
{
    float elapsed_time_seconds =(elapsed_time_ms)/(1000.0);
    float rev_per_min = ((SECONDS_PER_MINUTE)/(elapsed_time_seconds));
    uint16_t rev_rouded = (uint16_t)ceil(roundf(rev_per_min));
    return rev_rouded;
}


/*!===========================================================================*
 * Callback Definitions
 *===========================================================================*/
void timer_callback_turn(timer_callback_args_t  *p_args)
{
    timer_counts++;
}

void hall_sensor_pulses_callback(external_irq_callback_args_t *p_args)
{
    pulses_count++;
    /*sprintf(send_trace, "Pulses: %d\r", pulses_count);
    tx_queue_send(&g_cdc_queue, send_trace, TX_NO_WAIT);*/
    if(pulses_count >= PULSES_PER_TURN)
    {
        elapsed_time_ms = (uint16_t)(timer_counts*time_ms);
        elapsed_time_flag = true;
        /*sprintf(send_trace, "4 pulses\r");*/
        tx_queue_send(&g_cdc_queue, send_trace, TX_NO_WAIT);
    }
}



/*!===========================================================================
 *
 * @file hall_effect_thread_entry.c
 *
 * @section RH REVISION HISTORY (top to bottom: first revision to last revision)
 *
 * - 09-Feb-2019 Victor Alvarado  Rev 1
 *   - Task: Initial File
 *
 * - 16-Feb-2019 Victor Alvarado Rev 2
 *   - Task: Read hall effect pulses and fix timing
 *
 * - 22-Feb-2019 Victor Alvarado Rev 3
 *   - Task: Fix in RPM calculus
 *
 * - 03-Mar-2019 Gpe. Josue Uribe Rev 4
 *   - Task: Post RPMs to the Main Thread
 *
 *===========================================================================*/


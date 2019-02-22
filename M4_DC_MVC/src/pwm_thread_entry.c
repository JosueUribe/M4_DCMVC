/*!===========================================================================*
 * Header Files
 *===========================================================================*/
#include "pwm_thread.h"

/*!===========================================================================*
 * Local Preprocessor #define Constants
 *===========================================================================*/
#define CLOCK_B                     1
#define DEFAULT_DUTY_CYCLE          5
#define DEFAULT_ADC_VALUE         512
#define DELTA_DUTY                  5
#define MAX_DUTY_CYCLE_PERCENT    100
#define PWM_THREAD_SLEEP          100


/*!===========================================================================*
 * External Type Declarations
 *===========================================================================*/
extern TX_QUEUE g_cdc_queue;

/*!===========================================================================*
 * Local Type Declarations

 *===========================================================================*/
static uint8_t duty_cycle = DEFAULT_DUTY_CYCLE;
static char send_trace[100];  //to store debug strings

UINT TX_status_pwm = TX_SUCCESS;

static uint16_t received_adc_value = DEFAULT_ADC_VALUE;   //to store received value from adc thread

void pwm_thread_entry(void)
{
    /*Open timer object by calling [R_GPT_TimerOpen] function*/
    g_timer0.p_api->open(g_timer0.p_ctrl, g_timer0.p_cfg);

    /*Auto start is false, so we need to start the timer manually by calling [R_GPT_Start]*/
    g_timer0.p_api->start(g_timer0.p_ctrl);

    while (1)
    {
        TX_status_pwm = tx_queue_receive(&g_cdc_to_pwm_queue, &received_adc_value, TX_WAIT_FOREVER);  //receive adc values from adc_thread_entry
       if (TX_SUCCESS != TX_status_pwm)
       {
           sprintf(send_trace, "Error %d receiving data from queue\r", TX_status_pwm);
           tx_queue_send(&g_cdc_queue, send_trace, TX_NO_WAIT);
       }

       duty_cycle = (uint8_t)(received_adc_value * 100 / 1023);   //convert adc value to percentage value

       g_timer0.p_api->dutyCycleSet(g_timer0.p_ctrl, duty_cycle, TIMER_PWM_UNIT_PERCENT, CLOCK_B);

       /*Console traces*/
       sprintf(send_trace, "Duty Cycle: %d\r", duty_cycle);
       tx_queue_send(&g_cdc_queue, send_trace, TX_NO_WAIT);


       tx_thread_sleep (2);
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
 *===========================================================================*/

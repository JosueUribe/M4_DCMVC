/*!===========================================================================*
 * Header Files
 *===========================================================================*/
#include "pwm_thread.h"

/*!===========================================================================*
 * Local Preprocessor #define Constants
 *===========================================================================*/
#define CLOCK_B                     1
#define DEFAULT_DUTY_CYCLE          5
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
static char send_trace[30];  //to store debug strings

void pwm_thread_entry(void)
{
    /*Open timer object by calling [R_GPT_TimerOpen] function*/
    g_timer0.p_api->open(g_timer0.p_ctrl, g_timer0.p_cfg);

    /*Auto start is false, so we need to start the timer manually by calling [R_GPT_Start]*/
    g_timer0.p_api->start(g_timer0.p_ctrl);

    while (1)
    {
       g_timer0.p_api->dutyCycleSet(g_timer0.p_ctrl, duty_cycle, TIMER_PWM_UNIT_PERCENT, CLOCK_B);
       sprintf(send_trace, "Duty Cycle: %d\r", duty_cycle);
       tx_queue_send(&g_cdc_queue, send_trace, 0);
       duty_cycle = (duty_cycle + DELTA_DUTY) % MAX_DUTY_CYCLE_PERCENT;

       if(duty_cycle == 0)
       {
          duty_cycle = 5;
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
 *===========================================================================*/

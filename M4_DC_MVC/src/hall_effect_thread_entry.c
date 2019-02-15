/*!===========================================================================*
 * Header Files
 *===========================================================================*/
#include <hall_effect_thread.h>

/*!===========================================================================*
 * Local Preprocessor #define Constants
 *===========================================================================*/
#define PERIOD_TIMER_VALUE_MS     1
#define SECONDS_PER_MINUTE        60
#define PULSES_PER_TURN           15

/*!===========================================================================*
 * External Type Declarations
 *===========================================================================*/
extern TX_QUEUE g_cdc_queue;

/*!===========================================================================*
 * Global Type Declarations
 *===========================================================================*/
uint16_t elapsed_time_ms = 0;
uint16_t time_ms = PERIOD_TIMER_VALUE_MS;
uint16_t timer_counts = 0;
uint16_t pulses_count = 0;
bool elapsed_time_flag = false;
static char send_trace[30];  //to store debug strings

/*!===========================================================================*
 * Function prototypes
 *===========================================================================*/
float calculate_rpm(void);


/* HALL_EFFECT entry function */
void hall_effect_thread_entry(void)
{
    uint16_t rpm = 0;

    g_external_irq10.p_api->open(g_external_irq10.p_ctrl,g_external_irq10.p_cfg);

    /*Open timer object by calling [R_GPT_TimerOpen] function*/
    g_timer1.p_api->open(g_timer1.p_ctrl, g_timer1.p_cfg);

    /*Auto start is false, so we need to start the timer manually by calling [R_GPT_Start]*/
    g_timer1.p_api->start(g_timer1.p_ctrl);

    /* TODO: add your own code here */
    while (1)
    {
        if(true == elapsed_time_flag)
        {
            rpm = (uint16_t)calculate_rpm();
            elapsed_time_flag = false;
            timer_counts = 0;
            pulses_count = 0;
            /*Send value to PID module*/

            /*print console debug traces*/
            sprintf(send_trace, "Elapsed time per turn is: %d, number per rpm is = %d\r", elapsed_time_ms, rpm);
            tx_queue_send(&g_cdc_queue, send_trace, TX_NO_WAIT);
        }
        /*tx_thread_sleep (1);*/
    }
}


/*!===========================================================================*
 * Function Declarations

 *===========================================================================*/
float calculate_rpm(void)
{
    float elapsed_time_seconds = (elapsed_time_ms)/(1000);
    float rpm = ((SECONDS_PER_MINUTE*PULSES_PER_TURN)/(elapsed_time_seconds));
    return rpm;
}


/*!===========================================================================*
 * Callback Declarations

 *===========================================================================*/
void timer_callback_turn(timer_callback_args_t  *p_args)
{
    timer_counts++;
}

void hall_sensor_pulses_callback(external_irq_callback_args_t *p_args)
{
    pulses_count++;
    if(pulses_count >= PULSES_PER_TURN)
    {
        elapsed_time_ms = timer_counts*time_ms;
        elapsed_time_flag = true;
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
 *===========================================================================*/


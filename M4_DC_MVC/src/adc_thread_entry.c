#include "adc_thread.h"
#include "math.h"

#define C_FILTER_ORDER (int)128
#define ADC_THREAD_SLEEP     90
#define DEFAULT_DUTY_CYCLE   5
#define MAX_DIGITAL_VALUE    1023
#define MAX_PERCENTAGE       100
#define INERTIAL_DUTY_CYCLE  16

/*!===========================================================================*
 * External Type Declarations
 *===========================================================================*/
extern TX_QUEUE g_cdc_queue;
extern TX_QUEUE g_cdc_to_pwm_queue;


UINT TX_status_adc = TX_SUCCESS;
uint16_t u16ADC_Data = 0;
uint16_t u16ADC_FilteredData = 0;
static uint8_t duty_cycle = DEFAULT_DUTY_CYCLE;
static uint16_t SendFilteredData = 0;
static uint16_t SendRawData = 0;
static double revolutions_per_minute = 0;
static char send_adc_trace[100];  //to store debug strings

/*!===========================================================================*
 * Function prototypes
 *===========================================================================*/
double rmp_from_polynomial(int duty_c);


void adc_thread_entry(void)
{
    /*ADC set-up*/
    g_adc0.p_api->open(g_adc0.p_ctrl, g_adc0.p_cfg);
    g_adc0.p_api->scanCfg(g_adc0.p_ctrl, g_adc0.p_channel_cfg);
    g_adc0.p_api->scanStart(g_adc0.p_ctrl);

    while (1)
    {
        g_adc0.p_api->read(g_adc0.p_ctrl, ADC_REG_CHANNEL_0, &u16ADC_Data);

        /*this filters data to avoid sensibility in small variations*/
        u16ADC_FilteredData = (uint16_t)((u16ADC_Data + (C_FILTER_ORDER - 1)*u16ADC_FilteredData) / C_FILTER_ORDER);
        SendFilteredData = u16ADC_FilteredData;
        SendRawData = u16ADC_Data;

        /*This calculates duty cycle*/
        duty_cycle = (uint8_t)(u16ADC_Data * MAX_PERCENTAGE / MAX_DIGITAL_VALUE);
        revolutions_per_minute = rmp_from_polynomial(duty_cycle);

        /*send data to PID module*/


        TX_status_adc = tx_queue_send(&g_cdc_to_pwm_queue, &SendRawData, TX_NO_WAIT); //sends data to PWM
        if (TX_SUCCESS != TX_status_adc)
        {
            sprintf(send_adc_trace, "Error %d transmitting data\r", TX_status_adc);
            tx_queue_send(&g_cdc_queue, send_adc_trace, TX_NO_WAIT);
        }


        /*Console traces*/
        /*sprintf(send_adc_trace, "ADC: %d, RPMs: %f\r", u16ADC_Data,revolutions_per_minute);
        tx_queue_send(&g_cdc_queue, send_adc_trace, TX_NO_WAIT);*/

        tx_thread_sleep (2);
    }

    g_adc0.p_api->close(g_adc0.p_ctrl);
}

double rmp_from_polynomial(int duty_c)
{
    double d_c = (double)(duty_c);
    double rev = 0;

    if (INERTIAL_DUTY_CYCLE < duty_c)
    {
        rev = (double)(((3e-4)*d_c*d_c*d_c)-(0.056*d_c*d_c)+(5.0976*d_c)-36.655);
    }
    return rev;
}


/*!===========================================================================
 *
 * @file adc_thread_entry.c
 *
 * @section RH REVISION HISTORY (top to bottom: first revision to last revision)
 *
 * - 31-Dec-2018 Gpe. Josue Uribe  Rev 1
 *   - Task: Initial_ADC_Polling Implementation.
 *
 * - 01-Feb-2019 Victor Alvarado Rev 2
 *   - Task: Implement communication between ADC and PWM
 *
 * - 08-Feb-2019 Victor Alvarado Rev 3
 *   - Task: Add traces for errors transmiting data.
 *
 * - 15-Feb-2019 Victor Alvarado Rev 4
 *   - Task: Conversion from digital value to RPMs
 *
 *===========================================================================*/

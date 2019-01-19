#include "adc_thread.h"

#define C_FILTER_ORDER (int)128
#define ADC_THREAD_SLEEP     90

/*!===========================================================================*
 * External Type Declarations
 *===========================================================================*/
extern TX_QUEUE g_cdc_queue;


uint16_t u16ADC_Data = 0;
uint16_t u16ADC_FilteredData = 0;
static char send_adc_trace[30];  //to store debug strings

void adc_thread_entry(void)
{
    /*ADC set-up*/
    g_adc0.p_api->open(g_adc0.p_ctrl, g_adc0.p_cfg);
    g_adc0.p_api->scanCfg(g_adc0.p_ctrl, g_adc0.p_channel_cfg);
    g_adc0.p_api->scanStart(g_adc0.p_ctrl);

    while (1)
    {
        g_adc0.p_api->read(g_adc0.p_ctrl, ADC_REG_CHANNEL_0, &u16ADC_Data);

        u16ADC_FilteredData = (u16ADC_Data + (C_FILTER_ORDER - 1)*u16ADC_FilteredData) / C_FILTER_ORDER;

        sprintf(send_adc_trace, "ADC raw data: %d\r", u16ADC_Data);
        tx_queue_send(&g_cdc_queue, send_adc_trace, 0);

        tx_thread_sleep (ADC_THREAD_SLEEP);
    }

    g_adc0.p_api->close(g_adc0.p_ctrl);
}


/*!===========================================================================
 *
 * @file pwm_thread_entry.c
 *
 * @section RH REVISION HISTORY (top to bottom: first revision to last revision)
 *
 * - 31-Dec-2018 Gpe. Josue Uribe  Rev 1
 *   - Task: Initial_ADC_Polling Implementation.
 *
 *===========================================================================*/

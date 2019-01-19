/* HAL-only entry function */
#include "hal_data.h"

/*#define C_FILTER_ORDER (int)128

uint16_t u16ADC_Data;
uint16_t u16ADC_FilteredData;
const uint32_t delay = 50;

extern TX_QUEUE g_cdc_queue;

char send_str[80];
sprintf(send_str, "ADC");
tx_queue_send(&g_cdc_queue, send_str, TX_WAIT_FOREVER);*/

void hal_entry(void)
{/*
    g_adc0.p_api->open(g_adc0.p_ctrl, g_adc0.p_cfg);
    g_adc0.p_api->scanCfg(g_adc0.p_ctrl, g_adc0.p_channel_cfg);
    g_adc0.p_api->scanStart(g_adc0.p_ctrl);

    while(1)
    {
       g_adc0.p_api->read(g_adc0.p_ctrl, ADC_REG_CHANNEL_0, &u16ADC_Data);
       u16ADC_FilteredData = (u16ADC_Data + (C_FILTER_ORDER - 1)*u16ADC_FilteredData) / C_FILTER_ORDER;
       sprintf(send_str, "ADC: %d\r", u16ADC_FilteredData);
       tx_queue_send(&g_cdc_queue, send_str, TX_WAIT_FOREVER);
    }*/
}

/* generated thread header file - do not edit */
#ifndef PWM_THREAD_H_
#define PWM_THREAD_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
#ifdef __cplusplus
extern "C" void pwm_thread_entry(void);
#else
extern void pwm_thread_entry(void);
#endif
#ifdef __cplusplus
extern "C"
{
#endif
extern TX_QUEUE g_cdc_to_pwm_queue;
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* PWM_THREAD_H_ */

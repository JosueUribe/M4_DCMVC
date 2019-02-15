/* generated thread header file - do not edit */
#ifndef HALL_EFFECT_THREAD_H_
#define HALL_EFFECT_THREAD_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
#ifdef __cplusplus
extern "C" void hall_effect_thread_entry(void);
#else
extern void hall_effect_thread_entry(void);
#endif
#include "r_icu.h"
#include "r_external_irq_api.h"
#include "r_gpt.h"
#include "r_timer_api.h"
#ifdef __cplusplus
extern "C"
{
#endif
/* External IRQ on ICU Instance. */
extern const external_irq_instance_t g_external_irq10;
#ifndef hall_sensor_pulses_callback
void hall_sensor_pulses_callback(external_irq_callback_args_t *p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer1;
#ifndef timer_callback_turn
void timer_callback_turn(timer_callback_args_t *p_args);
#endif
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* HALL_EFFECT_THREAD_H_ */

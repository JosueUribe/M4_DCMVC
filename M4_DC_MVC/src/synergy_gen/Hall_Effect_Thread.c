/* generated thread source file - do not edit */
#include "hall_effect_thread.h"

TX_THREAD hall_effect_thread;
void hall_effect_thread_create(void);
static void hall_effect_thread_func(ULONG thread_input);
static uint8_t hall_effect_thread_stack[1024] BSP_PLACE_IN_SECTION_V2(".stack.hall_effect_thread") BSP_ALIGN_VARIABLE_V2(BSP_STACK_ALIGNMENT);
void tx_startup_err_callback(void *p_instance, void *p_data);
void tx_startup_common_init(void);
#if (4) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_external_irq10) && !defined(SSP_SUPPRESS_ISR_ICU10)
SSP_VECTOR_DEFINE( icu_irq_isr, ICU, IRQ10);
#endif
#endif
static icu_instance_ctrl_t g_external_irq10_ctrl;
static const external_irq_cfg_t g_external_irq10_cfg =
{ .channel = 10,
  .trigger = EXTERNAL_IRQ_TRIG_FALLING,
  .filter_enable = true,
  .pclk_div = EXTERNAL_IRQ_PCLK_DIV_BY_64,
  .autostart = true,
  .p_callback = hall_sensor_pulses_callback,
  .p_context = &g_external_irq10,
  .p_extend = NULL,
  .irq_ipl = (4), };
/* Instance structure to use this module. */
const external_irq_instance_t g_external_irq10 =
{ .p_ctrl = &g_external_irq10_ctrl, .p_cfg = &g_external_irq10_cfg, .p_api = &g_external_irq_on_icu };
#if (9) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_timer1) && !defined(SSP_SUPPRESS_ISR_GPT6)
SSP_VECTOR_DEFINE_CHAN(gpt_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 6);
#endif
#endif
static gpt_instance_ctrl_t g_timer1_ctrl;
static const timer_on_gpt_cfg_t g_timer1_extend =
{ .gtioca =
{ .output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW },
  .gtiocb =
  { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW },
  .shortest_pwm_signal = GPT_SHORTEST_LEVEL_OFF, };
static const timer_cfg_t g_timer1_cfg =
{ .mode = TIMER_MODE_PERIODIC, .period = 1, .unit = TIMER_UNIT_PERIOD_MSEC, .duty_cycle = 50, .duty_cycle_unit =
          TIMER_PWM_UNIT_RAW_COUNTS,
  .channel = 6, .autostart = false, .p_callback = timer_callback_turn, .p_context = &g_timer1, .p_extend =
          &g_timer1_extend,
  .irq_ipl = (9), };
/* Instance structure to use this module. */
const timer_instance_t g_timer1 =
{ .p_ctrl = &g_timer1_ctrl, .p_cfg = &g_timer1_cfg, .p_api = &g_timer_on_gpt };
extern bool g_ssp_common_initialized;
extern uint32_t g_ssp_common_thread_count;
extern TX_SEMAPHORE g_ssp_common_initialized_semaphore;

void hall_effect_thread_create(void)
{
    /* Increment count so we will know the number of ISDE created threads. */
    g_ssp_common_thread_count++;

    /* Initialize each kernel object. */

    UINT err;
    err = tx_thread_create (&hall_effect_thread, (CHAR *) "HALL_EFFECT", hall_effect_thread_func, (ULONG) NULL,
                            &hall_effect_thread_stack, 1024, 5, 5, 1, TX_AUTO_START);
    if (TX_SUCCESS != err)
    {
        tx_startup_err_callback (&hall_effect_thread, 0);
    }
}

static void hall_effect_thread_func(ULONG thread_input)
{
    /* Not currently using thread_input. */
    SSP_PARAMETER_NOT_USED (thread_input);

    /* Initialize common components */
    tx_startup_common_init ();

    /* Initialize each module instance. */

    /* Enter user code for this thread. */
    hall_effect_thread_entry ();
}

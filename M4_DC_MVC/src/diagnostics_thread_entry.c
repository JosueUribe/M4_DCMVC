/*!===========================================================================*
 * Header Files
 *===========================================================================*/
#include <diagnostics_thread.h>

/*!===========================================================================*
 * Local Preprocessor #define Constants
 *===========================================================================*/
#define DIAGNOSTICS_THREAD_SLEEP    10 /* Milliseconds to sleep */

/*!===========================================================================*
 * External Type Declarations
 *===========================================================================*/

/*!===========================================================================*
 * Local Type Declarations
 *===========================================================================*/
static ioport_level_t battery_shortcut = IOPORT_LEVEL_LOW;
static ioport_level_t ground_shortcut = IOPORT_LEVEL_LOW;

bsp_leds_t leds;

/* diagnostics thread entry function */
void diagnostics_thread_entry(void)
{
    R_BSP_LedsGet(&leds);
    while(1)
    {
        g_ioport.p_api->pinRead(IOPORT_PORT_06_PIN_14,&ground_shortcut);
        g_ioport.p_api->pinRead(IOPORT_PORT_06_PIN_13,&battery_shortcut);

        if(ground_shortcut)
        {
            g_ioport.p_api->pinWrite(leds.p_leds[1], IOPORT_LEVEL_LOW);
        }
        else
        {
            g_ioport.p_api->pinWrite(leds.p_leds[1], IOPORT_LEVEL_HIGH);
        }

        if(battery_shortcut)
        {
            g_ioport.p_api->pinWrite(leds.p_leds[2], IOPORT_LEVEL_LOW);
        }
        else
        {
            g_ioport.p_api->pinWrite(leds.p_leds[2], IOPORT_LEVEL_HIGH);
        }

        tx_thread_sleep (DIAGNOSTICS_THREAD_SLEEP);
    }
}

/*!===========================================================================
 *
 * @file diagnostics_thread_entry.c
 *
 * @section RH REVISION HISTORY (top to bottom: first revision to last revision)
 *
 * - 08-Feb-2019 Victor Alvarado  Rev 1
 *   - Task: Initial file.
 *
 *- 09-March-2019  Gpe. Josue Uribe Rev 2
 *   - Task: Update ports and pins for shortcut detection.
 *
 *===========================================================================*/

/*!===========================================================================*
 * Header Files
 *===========================================================================*/
#include <diagnostics_thread.h>

/*!===========================================================================*
 * Local Preprocessor #define Constants
 *===========================================================================*/

/*!===========================================================================*
 * External Type Declarations
 *===========================================================================*/

/*!===========================================================================*
 * Local Type Declarations

 *===========================================================================*/
ioport_level_t button_level = IOPORT_LEVEL_LOW;
bsp_leds_t Leds;

/* diagnostics thread entry function */
void diagnostics_thread_entry(void)
{
    R_BSP_LedsGet(&Leds);
    while(1)
    {
        g_ioport.p_api->pinRead(IOPORT_PORT_00_PIN_01,&button_level);
                if(IOPORT_LEVEL_HIGH == button_level)
                {
                    g_ioport.p_api->pinWrite(Leds.p_leds[1], IOPORT_LEVEL_HIGH);
                }
                else
                {
                    g_ioport.p_api->pinWrite(Leds.p_leds[1], IOPORT_LEVEL_LOW);
                }

        tx_thread_sleep (1);
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
 *===========================================================================*/

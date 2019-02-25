/*!===========================================================================*
 * Header Files
 *===========================================================================*/
#include "usb_console_thread.h"

/*!===========================================================================*
 * Local Preprocessor #define Constants
 *===========================================================================*/
#define ID_CHARS_SIZE 160

/*!===========================================================================*
 * Local Type Declarations
 *===========================================================================*/
uint8_t rx_msg[ID_CHARS_SIZE];

void usb_console_thread_entry(void)
{

      while (1)
      {
         /* Get debug string from Queue */
         tx_queue_receive(&g_cdc_queue, rx_msg, TX_WAIT_FOREVER);

         /* Write debug String to USB device framework */
         g_sf_comms0.p_api->write(g_sf_comms0.p_ctrl, rx_msg, strlen(rx_msg), TX_NO_WAIT);
         tx_thread_sleep (1);
      }
}

/*!===========================================================================
 *
 * @file usb_console_thread_entry.c
 *
 * @section RH REVISION HISTORY (top to bottom: first revision to last revision)
 *
 * - 01-Oct-2018 Gpe. Josue Uribe  Rev 1
 *   - Task: Initial USB console file.
 *
 *===========================================================================*/

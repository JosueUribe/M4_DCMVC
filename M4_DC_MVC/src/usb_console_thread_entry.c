#include "usb_console_thread.h"

/* USB Serial Port Thread entry function */

UINT rx_status = 8;
void usb_console_thread_entry(void)
 {
      char rx_msg[80];
      while (1)
      {
         //get debug string from Queue
         rx_status = tx_queue_receive(&g_cdc_queue, rx_msg, TX_WAIT_FOREVER);

         //Write debug String to USB device framework.
         g_sf_comms0.p_api->write(g_sf_comms0.p_ctrl, rx_msg, strlen(rx_msg), TX_NO_WAIT);
         tx_thread_sleep (1);
      }
}

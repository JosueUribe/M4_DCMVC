/*!===========================================================================*
 * Header Files
 *===========================================================================*/
#include <diagnostics_thread.h>

/*!===========================================================================*
 * Local Preprocessor #define Constants
 *===========================================================================*/
#define DIAGNOSTICS_THREAD_SLEEP    30 /* Milliseconds to sleep */

/*!===========================================================================*
 * External Type Declarations
 *===========================================================================*/
extern const sf_message_post_cfg_t g_post_cfg;
extern const sf_message_acquire_cfg_t g_acquire_cfg;

/*!===========================================================================*
 * Local Type Declarations
 *===========================================================================*/
static ioport_level_t battery_shortcut = IOPORT_LEVEL_LOW;
static ioport_level_t ground_shortcut = IOPORT_LEVEL_LOW;
/* Pointers to event message and data */
static sf_message_header_t *p_message  = NULL;
static sf_message_payload_t *p_payload = NULL;
static sf_message_post_err_t post_err;
static bsp_leds_t leds;
static ssp_err_t err;

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

        /* Get buffer from Messaging framework. */
        err = g_sf_message0.p_api->bufferAcquire(g_sf_message0.p_ctrl, (sf_message_header_t **) &p_message, &g_acquire_cfg, TX_NO_WAIT);

        if (SSP_SUCCESS != err)
        {
             while(1); /* Trap if error */
        }
        else
        {

            /* Creating message in buffer. */
            p_message->event_b.class_code = SF_MESSAGE_EVENT_CLASS_DIAGNOSTICS_DATA;
            p_message->event_b.code  = SF_MESSAGE_EVENT_GROUND_SHORTCUT;
            p_payload = (sf_message_payload_t*)(p_message+1);
            p_payload->diagnostics_data_payload.ground_short = ground_shortcut;

            /* Posting message. */
            err = g_sf_message0.p_api->post(g_sf_message0.p_ctrl, (sf_message_header_t *) p_message, &g_post_cfg, &post_err, TX_NO_WAIT);

            if(SSP_SUCCESS != err)
            {
                 while(1);
            }
         }

        if(battery_shortcut)
        {
            g_ioport.p_api->pinWrite(leds.p_leds[2], IOPORT_LEVEL_LOW);
        }
        else
        {
            g_ioport.p_api->pinWrite(leds.p_leds[2], IOPORT_LEVEL_HIGH);
        }

        /* Get buffer from Messaging framework. */
        err = g_sf_message0.p_api->bufferAcquire(g_sf_message0.p_ctrl, (sf_message_header_t **) &p_message, &g_acquire_cfg, TX_NO_WAIT);

        if (SSP_SUCCESS != err)
        {
            while(1); /* Trap if error */
        }
        else
        {
             /* Creating message in buffer. */
             p_message->event_b.class_code = SF_MESSAGE_EVENT_CLASS_DIAGNOSTICS_DATA;
             p_message->event_b.code  = SF_MESSAGE_EVENT_BATTERY_SHORTCUT;
             p_payload = (sf_message_payload_t*)(p_message+1);
             p_payload->diagnostics_data_payload.battery_short = battery_shortcut;

             /* Posting message. */
             err = g_sf_message0.p_api->post(g_sf_message0.p_ctrl, (sf_message_header_t *) p_message, &g_post_cfg, &post_err, TX_NO_WAIT);

             if (SSP_SUCCESS != err)
             {
                  while(1);
             }
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
 *- 08-Feb-2019 Victor Alvarado  Rev 1
 *   - Task: Initial file.
 *
 *- 09-March-2019  Gpe. Josue Uribe Rev 2
 *   - Task: Update ports and pins for shortcut detection.
 *
 *- 12-March-2019  Gpe. Josue Uribe Rev 3
 *   - Task: Use SSP Messaging framework to update shortcut detections on the GUI.
 *
 *===========================================================================*/

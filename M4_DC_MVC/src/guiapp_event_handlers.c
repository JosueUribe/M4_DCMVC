/*!===========================================================================*
 * Header Files
 *===========================================================================*/
#include "gui/guiapp_resources.h"
#include "gui/guiapp_specifications.h"
#include "main_thread.h"
#include "system_api.h"
#include <stdio.h>

/*!===========================================================================*
 * Local Preprocessor #define Constants
 *===========================================================================*/

/*!===========================================================================*
 * External Type Declarations
 *===========================================================================*/
extern GX_WINDOW_ROOT * p_window_root;

/*!===========================================================================*
 * Local Type Declarations
 *===========================================================================*/
static UINT show_window(GX_WINDOW * p_new, GX_WIDGET * p_widget, bool detach_old);
static void update_text(GX_WIDGET * p_widget, GX_RESOURCE_ID id, char * p_text);
static void update_state_data(GX_EVENT *event_ptr);

static char g_local_duty_cycle_str [4] = "000";
static char g_local_rpms_speed_str [6] = "00000";

static system_state_t g_gui_state;

UINT main_screen_handler(GX_WINDOW *widget, GX_EVENT *event_ptr)
{

    UINT result = gx_window_event_process(widget, event_ptr);

    switch (event_ptr->gx_event_type)
    {
        case GX_SIGNAL(ID_WINDOWCHANGER_SYS, GX_EVENT_CLICKED):
            show_window((GX_WINDOW*)&system_diagnostics, (GX_WIDGET*)widget, true);
            break;
        case GXEVENT_MSG_REFRESH_SYSTEM_DATA:
            /* Update System data in the GUI. */
             update_state_data(event_ptr);
             snprintf(g_local_duty_cycle_str, sizeof(g_local_duty_cycle_str), "%d", g_gui_state.pwm_duty_cycle_data);
             snprintf(g_local_rpms_speed_str, sizeof(g_local_rpms_speed_str), "%d", g_gui_state.rpms_speed_data);
             update_text((GX_WIDGET *) widget, ID_CMD_TEXT, g_local_duty_cycle_str);
             update_text((GX_WIDGET *) widget, ID_SPEED_TEXT, g_local_rpms_speed_str);
             break;
        default:
            result = gx_window_event_process(widget, event_ptr);
            break;
    }
    return result;

}

UINT system_diagnostics_handler(GX_WINDOW *widget, GX_EVENT *event_ptr)
{
    UINT result = gx_window_event_process(widget, event_ptr);

    switch (event_ptr->gx_event_type)
    {
        case GX_SIGNAL(ID_WINDOWCHANGER_MAIN, GX_EVENT_CLICKED):
            show_window((GX_WINDOW*)&main_screen, (GX_WIDGET*)widget, true);
            break;
        default:
            result = gx_window_event_process(widget, event_ptr);
            break;
    }

    return result;
}


static UINT show_window(GX_WINDOW * p_new, GX_WIDGET * p_widget, bool detach_old)
{
    UINT err = GX_SUCCESS;

    if (!p_new->gx_widget_parent)
    {
        err = gx_widget_attach(p_window_root, p_new);
    }
    else
    {
        err = gx_widget_show(p_new);
    }

    gx_system_focus_claim(p_new);

    GX_WIDGET * p_old = p_widget;
    if (p_old && detach_old)
    {
        if (p_old != (GX_WIDGET*)p_new)
        {
            gx_widget_detach(p_old);
        }
    }

    return err;
}

static void update_text(GX_WIDGET * p_widget, GX_RESOURCE_ID id, char * p_text)
{
    GX_PROMPT * p_prompt = NULL;

    UINT err = gx_widget_find(p_widget, (USHORT)id, GX_SEARCH_DEPTH_INFINITE, (GX_WIDGET **) &p_prompt);
    if (GX_SUCCESS == err)
    {
        err = gx_prompt_text_set(p_prompt, p_text);
        if (GX_SUCCESS != err) {
            while(1);
        }

    } else {
        while(1);
    }
}

static void update_state_data(GX_EVENT *event_ptr)
{
    system_payload_t * p_payload;

    /* Get mutex lock before accessing the pointer to the state data sent from the
     *  main thread, then save a local copy of the state data to be used by the GUI. */
    tx_mutex_get(&g_state_data_mutex,TX_WAIT_FOREVER);

    p_payload = (system_payload_t *) event_ptr->gx_event_payload.gx_event_ulongdata;
    g_gui_state = p_payload->state;

    tx_mutex_put(&g_state_data_mutex);
}

/*!===========================================================================
 *
 * @file guiapp_event_handlers.c
 *
 * @section RH REVISION HISTORY (top to bottom: first revision to last revision)
 *
 * - 25-Feb-2019 Gpe. Josue Uribe  Rev 1
 *   - Task: Initial Event handler file.
 *
 * - 03-Mar-2019 Gpe. Josue Uribe  Rev 2
 *   - Task: Update RPMs in the GUI.
 *
 *===========================================================================*/



/*
 * system_api.h
 *
 */

#ifndef SYSTEM_API_H_
#define SYSTEM_API_H_

typedef enum
{
    /* Some classes do not use the event enumeration. */
    GXEVENT_MSG_UNUSED = GX_FIRST_APP_EVENT,
    /* System data refresh. */
    GXEVENT_MSG_REFRESH_SYSTEM_DATA,

} gx_event_message_t;

typedef struct st_system_state
{
    uint8_t             pwm_duty_cycle_data;
    uint16_t            user_speed_data;
} system_state_t;

typedef struct st_system_payload
{
    GX_EVENT        gx_event;
    system_state_t  state;
} system_payload_t;


#endif /* SYSTEM_API_H_ */

/*!===========================================================================
 *
 * @file system_api.h
 *
 * @section RH REVISION HISTORY (top to bottom: first revision to last revision)
 *
 * - 15-Feb-2019 Gpe. Josue Uribe  Rev 1
 *   - Task: Initial system_api.h file with system_payload_t, system_state_t, gx_event_message_t declarations.
 *
 *===========================================================================*/

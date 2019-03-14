/* generated messaging header file - do not edit */
#ifndef SF_MESSAGE_PAYLOADS_H_
#define SF_MESSAGE_PAYLOADS_H_
#include "sf_touch_panel_api.h"
#include "pwm_data_api.h"
#include "hall_effect_feedback_api.h"
#include "diagnostics_data_api.h"
typedef union u_sf_message_payload
{
    sf_touch_panel_payload_t sf_touch_panel_payload;
    pwm_data_payload_t pwm_data_payload;
    hall_effect_feedback_payload_t hall_effect_feedback_payload;
    diagnostics_data_payload_t diagnostics_data_payload;
} sf_message_payload_t;
#endif /* SF_MESSAGE_PAYLOADS_H_ */

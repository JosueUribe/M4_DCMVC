/*
 * diagnostics_data_api.h
 *
 */

#ifndef DIAGNOSTICS_DATA_API_H_
#define DIAGNOSTICS_DATA_API_H_

typedef struct diagnostics_data_payload
{
    ioport_level_t battery_short;
    ioport_level_t ground_short;
}diagnostics_data_payload_t;

#endif /* DIAGNOSTICS_DATA_API_H_ */

/*!===========================================================================
 *
 * @file hall_effect_feedback_api.h
 *
 * @section RH REVISION HISTORY (top to bottom: first revision to last revision)
 *
 * - 12-March-2019 Gpe. Josue Uribe  Rev 1
 *   - Task: Initial diagnostics_data_api.h file with battery_short and ground_short
 *
 *===========================================================================*/

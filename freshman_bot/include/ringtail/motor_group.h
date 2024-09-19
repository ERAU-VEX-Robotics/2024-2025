/**
 * @file motor_group.h
 *
 * @brief Definitions for the motor group and related functions
 *
 * @details This file contains the type definition for Ringtail's motor group
 * structure, the base unit for all Ringtail functions. In reality, the motor
 * group struct is just an array of 21 8 bit integers, which account for all 21
 * smart ports on the v5 brain.
 */

#ifndef RINGTAIL_MOTOR_GROUP_H_
#define RINGTAIL_MOTOR_GROUP_H_

// This line tells a C++ compiler that these functions are C functions. This is
// important for compilation reasons. See https://stackoverflow.com/a/1041880
#ifdef __cplusplus
extern "C" {
using namespace pros;
using namespace pros::c;
#endif

#include "pros/motors.h"

#include <stdint.h>

/**
 * Ringtail's motor group is defined to be an array of int8_t of length 21, as a
 * single v5 brain has 21 ports that can be used for a motor. While no one in
 * their right mind would have a use case for all 21 motors in 1 group, there's
 * no harm in using the technical limit, as long as we have a limit.
 *
 * Setting a defined limit allows us to just pass the array to and from
 * functions without having to also pass the length. Because values that aren't
 * initialized in an array in C are set to 0, we can check once user-defined
 * values stop by seeing if the port value is 0.
 */
#define RGT_MG_SIZE 21

typedef int8_t rgt_motor_group[RGT_MG_SIZE];

/*******************************************************************************
 *                              Movement Functions                             *
 ******************************************************************************/

/**
 * @brief Causes all the motors to stop using the currently assigned brake mode
 *
 * @details This function calls the PROS motor_brake function for each motor in
 * the group.
 *
 * The motor_brake function stops the motor using the currently
 * configured brake mode.
 *
 * @param mg The motor group to brake
 *
 * @return 1 if all motor operations were successful, PROS_ERR otherwise.
 * Basically just returns what motor_move does.
 */
int32_t rgt_mg_brake(const rgt_motor_group mg);

/**
 * @brief Sets the voltage for all the motors, from -127 to 127.
 *
 * @details This function calls the PROS motor_move function for each motor in
 * the group.
 *
 * The motor_move function sets a motor's voltage to the given value, from -127
 * to 127.
 *
 * @param mg The motor group to set the voltage for
 * @param voltage The new motor group voltage from -127 to 127
 *
 * @return 1 if all motor operations were successful, PROS_ERR otherwise
 * Basically just returns what motor_move does.
 */
int32_t rgt_mg_move(const rgt_motor_group mg, const int8_t voltage);

/**
 * @brief Sets the absolute position for all motors to move to
 *
 * @details This function calls the PROS motor_move_absolute function for each
 * motor in the group.
 *
 * The motor_move_absolute function sets a target absolute position
 * for the motor to move to, with the position being relative to the position of
 * the motor when initialized or when it was last reset with
 * motor_tare_position.
 *
 * Note that this function is not blocking, i.e. it returns immediately, instead
 * of waiting until the movement is complete.
 *
 * @param mg The motor group to set the position for
 * @param position The absolute position to move to in the motor’s encoder units
 * @param velocity The maximum allowable velocity for the movement in RPM
 *
 * @return 1 if all motor operations were successful, PROS_ERR otherwise.
 * Basically just returns what motor_move does.
 */
int32_t rgt_mg_move_absolute(const rgt_motor_group mg, const double position,
                             const int32_t velocity);

/**
 * @brief Sets the relative position for all motors to move to
 *
 * @details This function calls the PROS motor_move_relative function for each
 * motor in the group.
 *
 * The motor_move_relative function sets a target relative position
 * for the motor to move to, with the position being relative to the motor's
 * current position.
 *
 * Note that this function is not blocking, i.e. it returns immediately, instead
 * of waiting until the movement is complete.
 *
 * @param mg The motor group to set the position for
 * @param position The relative position to move to in the motor’s encoder units
 * @param velocity The maximum allowable velocity for the movement in RPM
 *
 * @return 1 if all motor operations were successful, PROS_ERR otherwise.
 * Basically just returns what motor_move does.
 */
int32_t rgt_mg_move_relative(const rgt_motor_group mg, const double position,
                             const int32_t velocity);

/**
 * @brief Sets the velocity for all motors in the group to run at
 *
 * @details This function calls the PROS motor_move_velocity function for each
 * motor in the group.
 *
 * The motor_move_velocity function sets a motor's velocity. This velocity
 * depends on the motor's internal gearing. Motors with red cartridges have a
 * limit of +-100 RPM, motors with green cartridges have a limit of +-200
 * RPM, and motors with blue cartridges have a limit of +-600 RPM.
 *
 * Setting the motor cartridge is important to ensure that the PID controller
 * has an accurate reading of the velocity
 *
 * The function uses an internal PID controller to hold the velocity.
 *
 * @param mg The motor group to set the velocity for
 * @param velocity The new motor velocity from +-100, +-200, or +-600 depending
 * on the motor’s gearset
 *
 * @return 1 if all motor operations were successful, PROS_ERR otherwise.
 * Basically just returns what motor_move does.
 */
int32_t rgt_mg_move_velocity(const rgt_motor_group mg, const int32_t velocity);

/**
 * @brief Sets the voltage for all the motors to run at, from -12000mV to
 * +12000mV
 *
 * @details This function calls the PROS motor_move_voltage function for each
 * motor in the group.motor
 *
 * The motor_move_voltage function sets a motor's raw voltage from -12000
 * millivolts to +12000 millivolts
 *
 * @param mg A motor group to set the voltage for
 * @param voltage The new motor voltage, from -12000mV to +12000mV
 *
 * @return 1 if all motor operations were successful, PROS_ERR otherwise.
 * Basically just returns what motor_move does.
 */
int32_t rgt_mg_move_voltage(const rgt_motor_group mg, const int16_t voltage);

/**
 * @brief Changes the velocity for a profiled movement (move absolute/relative)
 *
 * @details This function calls the PROS motor_modify_profiled_velocity function
 * for each motor in the group.
 *
 * The motor_modify_profiled_velocity function changes the output velocity for a
 * profiled movement (motor_move_absolute or motor_move_relative). It has no
 * effect if the motor is not following a profiled movement.
 *
 * @param mg The motor group to set the velocity for
 * @param velocity The new motor velocity from +-100, +-200, or +-600 depending
 * on the motor’s gearset
 *
 * @return 1 if all motor operations were successful, PROS_ERR otherwise.
 * Basically just returns what motor_move does.
 */
int32_t rgt_mg_modify_profiled_velocity(const rgt_motor_group mg,
                                        const int32_t velocity);

/*******************************************************************************
 *                             Telemetry Functions *
 ******************************************************************************/

/**
 * @brief Returns the average current draw of all motors in the group
 *
 * @details This function calculates the average current draw of all the motors.
 * It obtains the current draw  for each motor by calling the PROS
 * motor_get_current_draw function.
 *
 * The function gets the values for each motor and finds and returns the
 * average.
 *
 * @param mg The motor group to get the average current draw for
 *
 * @return The average current draw for each motor in the group.
 */
double rgt_mg_get_average_current_draw(const rgt_motor_group mg);

/**
 * @brief Retrieves the current draw for each motor in the group
 *
 * @details This function gets the current draw for each motor in the group, and
 * writes those values to an array passed in as an argument. It uses the PROS
 * motor_get_current_draw function to get the current draw for each motor.
 *
 * @param mg The motor group to get the average current draw for
 * @param current_draws An array to write all the motor current draws to. Should
 * be initialized to the number of elements in mg.
 */
void rgt_mg_get_current_draws(const rgt_motor_group mg, double *current_draws);

/**
 * @brief Returns the average position of all the motors in the group
 *
 * @details This function calculates the average position of all the motors. It
 * obtains the position for each motor by calling the PROS motor_get_position
 * function.
 *
 * The function gets the values for each motor and finds and returns the
 * average.
 *
 * @param mg The motor group to get the average position for
 *
 * @return The average position for all the motors in the group
 */
double rgt_mg_get_average_position(const rgt_motor_group mg);

/**
 * @brief Retrieves the position for each motor in the group
 *
 * @details This function gets the position for each motor in the group, and
 * writes those values to an array passed in as an argument. It uses the PROS
 * motor_get_position function to get the position for each motor.
 *
 * @param mg The motor group to get the positions for
 * @param positions An array to write all the motor positions to. Should
 * be initialized to the length value from the motor group.
 */
void rgt_mg_get_positions(const rgt_motor_group mg, double *positions);

/**
 * @brief Returns the average velocity for all the motors in the group
 *
 * @details This function calculates the average velocity of all the motors. It
 * obtains the velocity for each motor by calling the PROS
 * motor_get_actual_velocity function.
 *
 * The function gets the values for each motor and finds and returns the
 * average.
 *
 * @param mg The motor group to get the average velocity
 * for
 *
 * @return The average velocity for all the motors in the group
 */
double rgt_mg_get_average_velocity(const rgt_motor_group mg);

/**
 * @brief Retrieves the velocity for each motor in the group
 *
 * @details This function gets the velocity for each motor in the group, and
 * writes those values to an array passed in as an argument. It uses the PROS
 * motor_get_actual_velocity function to get the velocity for each motor.
 *
 * @param mg The motor group to get the average velocity from
 * for
 * @param velocities An array to write all the motor velocities to. Should
 * be initialized to the length value from the motor group.
 */
void rgt_mg_get_velocities(const rgt_motor_group mg, double *velocities);

/*******************************************************************************
 *                           Configuration Functions *
 ******************************************************************************/

/**
 * @brief Sets the brake mode for all motors in the group
 *
 * @details This function sets the motor brake mode for all the motors in the
 * group. The brake mode determines the behavior of the motor when it is stopped
 *
 * @param mg The motor group to set the brake mode for
 * @param brake_mode The PROS motor brake mode to use. See the PROS
 * motor_brake_mode_e_t definition:
 * https://pros.cs.purdue.edu/v5/api/c/motors.html#motor-brake-mode-e-t
 *
 * @return 1 if all motor operations were successful, PROS_ERR otherwise.
 * Basically just returns what motor_move does.
 */
int32_t rgt_mg_set_brake_mode(const rgt_motor_group mg,
                              const motor_brake_mode_e_t brake_mode);

/**
 * @brief Sets the encoder units for all motors in the group
 *
 * @details This function sets the encoder units for all the motors in the
 * group. The encoder units are the units used to report the value read from the
 * internal motor shaft encoder.
 *
 * @param mg The motor group to set the encoder units for
 * @param encoder_units The PROS motor brake mode to use. See the PROS
 * motor_encoder_units_e_t definition:
 * https://pros.cs.purdue.edu/v5/api/c/motors.html#motor-encoder-units-e-t
 *
 * @return 1 if all motor operations were successful, PROS_ERR otherwise.
 * Basically just returns what motor_move does.
 */
int32_t rgt_mg_set_encoder_units(const rgt_motor_group mg,
                                 const motor_encoder_units_e_t encoder_units);

/**
 * @brief Sets the gearing for all motors in the group
 *
 * @details This function sets the gearing for all the motors in the group. The
 * gearing refers to the internal motor cartridges, which can be red, green, or
 * blue.
 *
 * ALL MOTORS IN A GROUP SHOULD HAVE THE SAME CARTRIDGE. It doesn't make sense
 * for motors with different cartridges to be in the same motor group.
 *
 * @param mg The motor group to set the gearing for
 * @param gearing The PROS motor brake mode to use. See the PROS
 * motor_gearset_e_t definition:
 * https://pros.cs.purdue.edu/v5/api/c/motors.html#motor-gearset-e-t
 *
 * @return 1 if all motor operations were successful, PROS_ERR otherwise.
 * Basically just returns what motor_move does.
 */
int32_t rgt_mg_set_gearing(const rgt_motor_group mg,
                           const motor_gearset_e_t gearing);

/**
 * @brief Resets the positions of all motors in the group
 *
 * @details This function resets the absolute motor positions of each motor in
 * the group to the motor's current position, i.e. the current position is now
 * 0.
 *
 * @param mg The motor group to reset the positions for
 *
 * @return 1 if all motor operations were successful, PROS_ERR otherwise.
 * Basically just returns what motor_move does.
 */
int32_t rgt_mg_reset_positions(const rgt_motor_group mg);

#ifdef __cplusplus
}
#endif

#endif /* RINGTAIL_MOTOR_GROUP_H_ */

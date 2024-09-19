/**
 * @file reference_controllers.h
 *
 * @brief Implementations of the math for various commonly used motion
 * controllers.
 */

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief A Bangbang controller
 *
 * @details Returns the on_voltage if the current value is less than the target.
 * Otherwise, it returns the off_voltage
 *
 * @param target The desired value of the sensor used for the controller
 * @param current The current sensor value for the controller
 * @param on_voltage The voltage to supply if current < target
 * @param off_voltage The voltage to supply if current > target
 */
double bangbang(double target, double current, int16_t on_voltage,
                int16_t off_voltage);

/**
 * @brief PID function for use with Ringtail's generic controller system
 *
 * See the George Gillard Intro to PID Controllers document for information on
 * what PID Controllers are:
 * https://www.georgegillard.com/component/osdownloads/routedownload/robotics/introduction-to-pid-controllers-2nd-edition
 * Also take a look at the BLRS Wiki page on PID Controllers:
 * https://wiki.purduesigbots.com/software/control-algorithms/pid-controller
 *
 * @param error The error between the target value and current value
 * @param kP The Proportional constant
 * @param kI The Integral constant
 * @param kD The Derivative constant
 * @param integral A pointer to a double to store the accumulated error
 * @param prev_error The previously recorded error
 * @param clear_integral A boolean to indicate if the controller state should be
 * reset (integral and previous error set to 0)
 */
double pid(double error, double kP, double kI, double kD, double *integral,
           double prev_error, bool clear_integral);

/**
 * @brief Take Back Half function for use with Ringtail's generic controller
 * system
 *
 * @details Take Back Half controllers are controllers that slowly increase
 * their output voltage up from an initial "base value". Voltage is increased
 * until the sign of the error quantity changes, at which point the base value
 * is set to half of the output plus a "tbh" quantity (which is initialized to
 * zero). This "tbh" quantity is then set to the output. The "tbh" quantity is
 * the controller's guess at the ideal voltage to reach the set point. Each time
 * "tbh" is set, the controller's guess gets better. Note that the rate of
 * voltage increase is determined by a gain. kH, by which the error is
 * multiplied before being added to the output.
 *
 * See the BLRS Wiki link for more (assuming the link is valid):
 * https://wiki.purduesigbots.com/software/control-algorithms/take-back-half-tbh-controller
 */

void tbh(double error, double prev_error, double *output, double *tbh,
         double kH);

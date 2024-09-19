/**
 * @file pneumatics.h
 *
 * @brief Function and type definitions for controlling pneumatic pistons
 *
 * @details Ringtail provides mechanisms for controlling pneumatic pistons,
 * making pneumatics slightly easier to use. The main function provided by this
 * is to just eliminate code reuse.
 *
 */

#include <stdbool.h>
#include <stdint.h>

typedef struct {
	uint8_t port;  // The port of the solenoid that controls the piston(s)
	bool extended; // State variable - whether the piston(s) is/are extended
} Rgt_Pneumatic_Piston;

/**
 * @brief Initializes a Rgt_Pneumatic_Piston struct and sets PROS port config
 *
 * @details This function, given an ADI port, handles the setup of that port as
 * an ADI Digital Output and sets up a Rgt_Pneumatic_Piston struct.
 */
Rgt_Pneumatic_Piston rgt_pneumatic_init(uint8_t port);

/**
 * @brief Extends the piston(s) controlled by a single port
 *
 * @param p A pointer to the Rgt_Pneumatic_Piston port to extend
 */
void rgt_pneumatic_extend(Rgt_Pneumatic_Piston *p);

/**
 * @brief Retracts the piston(s) controlled by a single port
 *
 * @param p A pointer to the Rgt_Pneumatic_Piston port to retract
 */
void rgt_pneumatic_retract(Rgt_Pneumatic_Piston *p);

/**
 * @brief Toggles the state of the piston(s)
 *
 * @param p A pointer to the Rgt_Pneumatic_Piston port to toggle the state of
 */
void rgt_pneumatic_toggle(Rgt_Pneumatic_Piston *p);

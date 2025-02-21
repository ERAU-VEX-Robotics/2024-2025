#ifndef GUI_H_
#define GUI_H_

/**
 * @file gui.h
 *
 * @brief Function definitions for the GUI used for selecting autonomous and
 * debugging info
 *
 * @details Rob has a GUI that is used to select an autonomous routine as well
 * as display debugging information. This file contains function prototypes used
 * to set up the GUI, as well the auton_id variable, which is used to determine
 * which autonomous routine to run.
 */

// Defining the possible autonomous routines Rob can run
enum Auton_Routine {
	NONE,	// Do nothing
	TEST,	// A slot for a routine actively being tested
	MATCH,	// The match routine
	SKILLS, // The programming skills routine
};
// The global variable used in main.c to determine which autonomous to run
extern enum Auton_Routine auton_id;

/**
 * @brief Initializes the GUI
 *
 * @details This function handles all the initialization of the GUI, mainly
 * comprised of calls to LVGL, a graphics library that PROS ships with
 */
void gui_init(void);

#endif /* GUI_H_ */
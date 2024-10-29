#include "spike.h"

#include "pros/misc.h"

#include "ringtail/pneumatics.h"

/**
 * @file spike.c
 *
 * @brief Function implementations and local variables for controlling the spike
 */

// Initialize a piston object for the spike
static Rgt_Pneumatic_Piston spike_piston = {1, false};

// Spike toggle implementation
void spike_toggle(void) {
    rgt_pneumatic_toggle(&spike_piston);
}

// Spike opcontrol implementation
void spike_opcontrol(controller_digital_e_t toggle_button) {
    if (controller_get_digital(E_CONTROLLER_MASTER, toggle_button)) {
        spike_toggle();
    }
}
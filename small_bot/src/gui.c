/**
 * @file gui.c
 *
 * @brief Contains the code to set up the GUI for sb
 *
 * @details This file contains all the necessary LVGL objects and function calls
 * to set up the GUI for sb.
 */

#include "gui.h"

#include "liblvgl/lvgl.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Initialize the auton ID global
enum Auton_Routine auton_id = NONE;

// Set up the LVGL image files to be used
LV_IMG_DECLARE(eagle_screech_brain_screen_dark)
LV_IMG_DECLARE(eagle_screech_brain_screen)

// "Windows" for each menu. In reality, each window is actually an image, with
// objects created as children to the image
lv_obj_t *main_window;
lv_obj_t *auton_window;

// Functions used as callbacks for the navigation buttons
void show_auton_page(lv_event_t *e);
void show_main_page(lv_event_t *e);
// Function to set up the navigation buttons
void gui_nav_init(void);

// Styles used to make objects look good
lv_style_t main_style;
lv_style_t pg_style;
lv_style_t btn_style;
lv_style_t btn_pr_style;
lv_style_t btnm_bg_style;
// Function to wrap the setup of styles
void gui_style_init(void);

// Function to set up the auton menu
void gui_auton_init(void);
// LVGL objects used in the autonomous menu that need to be updated
lv_obj_t *auton_selected_lbl;
// The function used to update auton_id based on input in the autonomous menu
void update_auton_id(lv_event_t *e);

// The options in the auton selection function
const char *auton_select_options[] = {"Match", "Skills", "\n",
                                      "Test",  "None",   ""};

void gui_init(void) {
	/**
	 * Create each image to serve as the parent object for each menu. Also set
	 * the image source to the correct image file and set the position of each
	 * image to the middle of the screen.
	 */
	main_window = lv_img_create(lv_scr_act());
	lv_img_set_src(main_window, &eagle_screech_brain_screen);
	lv_obj_align(main_window, LV_ALIGN_CENTER, 0, 0);

	auton_window = lv_img_create(lv_scr_act());
	lv_img_set_src(auton_window, &eagle_screech_brain_screen_dark);
	lv_obj_align(auton_window, LV_ALIGN_CENTER, 0, 0);
	// Set the main menu to active
	lv_obj_add_flag(auton_window, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(main_window, LV_OBJ_FLAG_HIDDEN);

	gui_style_init();
	gui_nav_init();
	gui_auton_init();
}

// Function definitions for the navigation button callbacks
void show_auton_page(lv_event_t *e) {
	lv_obj_add_flag(main_window, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(auton_window, LV_OBJ_FLAG_HIDDEN);
}
void show_main_page(lv_event_t *e) {
	lv_obj_add_flag(auton_window, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(main_window, LV_OBJ_FLAG_HIDDEN);
}

// Initialize the navigation buttons
void gui_nav_init(void) {
	lv_obj_t *btn_main_to_auton = lv_btn_create(main_window);
	lv_obj_add_event_cb(btn_main_to_auton, show_auton_page, LV_EVENT_CLICKED,
	                    NULL);
	lv_obj_align(btn_main_to_auton, LV_ALIGN_TOP_LEFT, 20, 20);
	lv_obj_add_style(btn_main_to_auton, &main_style, LV_STATE_DEFAULT);
	lv_obj_add_style(btn_main_to_auton, &btn_style, LV_STATE_DEFAULT);
	lv_obj_add_style(btn_main_to_auton, &btn_pr_style, LV_STATE_PRESSED);
	lv_obj_set_size(btn_main_to_auton, 150, 50);

	lv_obj_t *lbl = lv_label_create(btn_main_to_auton);
	lv_obj_align(lbl, LV_ALIGN_CENTER, 0, 0);
	lv_label_set_text(lbl, "Auton Menu");

	lv_obj_t *btn_auton_to_main = lv_btn_create(auton_window);
	lv_obj_add_event_cb(btn_auton_to_main, show_main_page, LV_EVENT_CLICKED,
	                    NULL);
	lv_obj_align(btn_auton_to_main, LV_ALIGN_TOP_LEFT, 20, 20);
	lv_obj_add_style(btn_auton_to_main, &main_style, LV_STATE_DEFAULT);
	lv_obj_add_style(btn_auton_to_main, &btn_style, LV_STATE_DEFAULT);
	lv_obj_add_style(btn_auton_to_main, &btn_pr_style, LV_STATE_PRESSED);
	lv_obj_set_size(btn_auton_to_main, 150, 50);

	lbl = lv_label_create(btn_auton_to_main);
	lv_obj_align(lbl, LV_ALIGN_CENTER, 0, 0);
	lv_label_set_text(lbl, "Main Menu");
}

// Initialize the autonomous menu
void gui_auton_init(void) {

	lv_obj_t *auton_btnm = lv_btnmatrix_create(auton_window);
	lv_obj_align(auton_btnm, LV_ALIGN_RIGHT_MID, 0, 0);
	lv_obj_set_size(auton_btnm, 225, 150);
	lv_btnmatrix_set_map(auton_btnm, auton_select_options);
	lv_obj_add_style(auton_btnm, &main_style,
	                 LV_PART_MAIN | LV_PART_ITEMS | LV_STATE_DEFAULT);
	lv_obj_add_style(auton_btnm, &btnm_bg_style,
	                 LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_add_style(auton_btnm, &btn_style, LV_PART_ITEMS | LV_STATE_DEFAULT);
	lv_obj_add_style(auton_btnm, &btn_pr_style,
	                 LV_PART_ITEMS | LV_STATE_PRESSED);
	lv_obj_add_event_cb(auton_btnm, update_auton_id, LV_EVENT_CLICKED, NULL);

	auton_selected_lbl = lv_label_create(auton_window);
	lv_obj_align(auton_selected_lbl, LV_ALIGN_BOTTOM_LEFT, 20, -20);
	lv_label_set_text(auton_selected_lbl, "No Auton Selected");
}

void update_auton_id(lv_event_t *e) {
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *obj = lv_event_get_target(e);
	uint32_t id = lv_btnmatrix_get_selected_btn(obj);
	const char *text = lv_btnmatrix_get_btn_text(obj, id);

	if (!strcmp(text, auton_select_options[0])) {
		auton_id = MATCH;
		lv_label_set_text(auton_selected_lbl, text);
	} else if (!strcmp(text, auton_select_options[1])) {
		auton_id = SKILLS;
		lv_label_set_text(auton_selected_lbl, text);
	} else if (!strcmp(text, auton_select_options[3])) {
		auton_id = TEST;
		lv_label_set_text(auton_selected_lbl, text);
	} else if (!strcmp(text, auton_select_options[4])) {
		auton_id = NONE;
		lv_label_set_text(auton_selected_lbl, text);
	} else {
		auton_id = NONE;
		lv_label_set_text(auton_selected_lbl, text);
	}
}

// gui_style_init Definition - initializes all the lv_style_t objects how we
// want them
void gui_style_init(void) {
	// Define some LVGL colors
	const lv_color_t COLOR_NORMAL_BG = lv_color_hex(0x041a31);
	const lv_color_t COLOR_TEXT = lv_color_hex(0xdfdfdf);
	const lv_color_t COLOR_BTN_PRESSED = lv_color_hex(0x02101f);
	const lv_color_t COLOR_BTN_BORDER = lv_color_hex(0xf8c649);

	/**
	 * Initialize the main object style using the provided plain style.
	 * Doing so ensures all style values are defined. So, we only have to
	 * change values we care about
	 */
	lv_style_init(&main_style);
	lv_style_set_bg_color(&main_style, COLOR_NORMAL_BG);
	lv_style_set_text_color(&main_style, COLOR_TEXT);
	lv_style_set_text_font(&main_style, &lv_font_montserrat_16);

	// Set up the button style with a different border color, lower opacity, and
	// round corners
	lv_style_init(&btn_style);
	lv_style_set_border_color(&btn_style, COLOR_BTN_BORDER);
	lv_style_set_border_width(&btn_style, 2);
	lv_style_set_bg_opa(&btn_style, LV_OPA_50);
	lv_style_set_radius(&btn_style, 30);

	// Make pressed buttons darker and more opaque
	lv_style_init(&btn_pr_style);
	lv_style_set_bg_color(&btn_pr_style, COLOR_BTN_PRESSED);
	lv_style_set_bg_opa(&btn_pr_style, 200);

	/**
	 * LVGL button matrixes are groups of buttons that all call the same
	 * callback function, with their text as an argument used to differentiate
	 * which button was pressed.
	 *
	 * So, to make the button matrix style, we take the button style and adjust
	 * some of the padding parameters
	 */
	lv_style_init(&btnm_bg_style);
	lv_style_set_border_color(&btnm_bg_style, COLOR_BTN_BORDER);
	lv_style_set_border_width(&btnm_bg_style, 2);
	lv_style_set_bg_opa(&btnm_bg_style, LV_OPA_20);
	lv_style_set_border_opa(&btnm_bg_style, LV_OPA_50);
}

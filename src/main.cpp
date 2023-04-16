#include "pros/rtos.hpp"
#include "Drivetrain.hpp"
#include "Robot.hpp"
#include "Intake.hpp"
#include "Catapult.hpp"
#include "main.hpp"
#include "ports.hpp"
#include "odometry.hpp"
#include "Expansion.hpp"
#include "okapi/impl/device/motor/motor.hpp"
#include "okapi/impl/device/motor/motorGroup.hpp"
#include "cmath"
#include "string"

double const TILE_LENGTH = 1.8266667; // feet
double const ROBOT_LENGTH = 1.5; // feet
double const ROLLER_LENGTH = 0.1666667; // feet

double const t = 1.826667;
double const r = 0.166667;

lv_obj_t * changeColor;
lv_obj_t * buttonLabel;
lv_obj_t * setLabel;
bool redOrBlue = false; //Red is false | Blue is true
char* buttonText = "r";
static lv_res_t btn_click_action(lv_obj_t * btn)
{
	redOrBlue = !redOrBlue;
	if (redOrBlue == true) {
		buttonText = "b";
	} else if (redOrBlue == false) {
		buttonText = "r";
	}
	lv_label_set_text(setLabel,buttonText);
	return LV_RES_OK;
}

void initialize() {
	changeColor = lv_btn_create(lv_scr_act(),NULL);
	lv_btn_set_action(changeColor, LV_BTN_ACTION_CLICK, btn_click_action);
	lv_obj_set_size(changeColor, 200, 50);
	buttonLabel = lv_label_create(changeColor, NULL);
	lv_label_set_text(buttonLabel, buttonText);
	setLabel = lv_label_create(lv_scr_act(),NULL);
	lv_label_set_text(setLabel,"Funny");
}

void disabled() {}
void competition_initialize() {}
void opcontrol() {
	Drivetrain const drivetrain{ ports::LEFT_BACK_MOTOR, ports::RIGHT_BACK_MOTOR, ports::LEFT_FRONT_MOTOR, ports::RIGHT_FRONT_MOTOR, ports::LEFT_MIDDLE_MOTOR, ports::RIGHT_MIDDLE_MOTOR };
	Intake const intake{ ports::INTAKE_LEFT, ports::INTAKE_RIGHT };
	Expansion const expansion{ ports::EXPANSION_PISTON_LEFT, ports::EXPANSION_PISTON_RIGHT};
	Roller const roller { ports::ROLLER, redOrBlue, ports::OPTICAL_SENSOR, ports::OPTICAL_SENSOR_BACK };
	Catapult const catapult {ports::CATAPULT_MOTOR, ports::LIMIT_SWITCH};
	Robot robot{ drivetrain, intake, expansion, roller, catapult};

	while (true) {
		robot.update(buttonText);
		pros::Task::delay(1);
	}
}
void autonomous() {}


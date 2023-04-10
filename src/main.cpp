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

void initialize() {}
void disabled() {}
void competition_initialize() {}
void opcontrol() {
	Drivetrain const drivetrain{ ports::LEFT_BACK_MOTOR, ports::RIGHT_BACK_MOTOR, ports::LEFT_FRONT_MOTOR, ports::RIGHT_FRONT_MOTOR, ports::LEFT_MIDDLE_MOTOR, ports::RIGHT_MIDDLE_MOTOR };
	Intake const intake{ ports::INTAKE_LEFT, ports::INTAKE_RIGHT };
	Expansion const expansion{ ports::EXPANSION_PISTON_LEFT, ports::EXPANSION_PISTON_RIGHT};
	Roller const roller { ports::ROLLER };
	Catapult const catapult {ports::CATAPULT_MOTOR, ports::POTENTIOMETER};
	Robot robot{ drivetrain, intake, expansion, roller, catapult};

	while (true) {
		robot.update();
		pros::Task::delay(1);
	}
}
void autonomous() {}
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

#include "okapi/impl/device/rotarysensor/integratedEncoder.hpp"
// #include "okapi/impl/chassis/controller/chassisControllerBuilder.hpp"
// #include "okapi/impl/device/motor/motorGroup.hpp"
// #include <cstdint>

#include "cmath"
#define PI 3.14159265
#include "string"

double const TILE_LENGTH = 1.8266667; // feet
double const ROBOT_LENGTH = 1.5; // feet
double const ROLLER_LENGTH = 0.1666667; // feet

// double const ROLLER_LENGTH = TILE_LENGTH - 13.46;

void initialize() {}
void disabled() {}
void competition_initialize() {}

void opcontrol() {
	Drivetrain const drivetrain{ ports::LEFT_BACK_MOTOR, ports::RIGHT_BACK_MOTOR, ports::LEFT_FRONT_MOTOR, ports::RIGHT_FRONT_MOTOR };
	Intake const intake{ ports::INTAKE_LEFT, ports::INTAKE_RIGHT };
	Expansion const expansion{ ports::EXPANSION_PISTON_LEFT, ports::EXPANSION_PISTON_RIGHT};
	Roller const roller { ports::ROLLER };
	Catapult const catapult {ports::CATAPULT_MOTOR, ports::LIMIT_SWITCH_CATAPULT};
	Robot robot{ drivetrain, intake, expansion, roller, catapult};

	while (true) {
		robot.update();
		pros::Task::delay(1);
	}
}

void autonomous() {}
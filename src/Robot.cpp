#include "pros/misc.h"
#include <iostream>
#include "Robot.hpp"
#include "Catapult.hpp"

Robot::Robot(Drivetrain drivetrain, Intake intake, Expansion expansion, Roller roller, Catapult catapult)
	: m_drivetrain(drivetrain), m_intake(intake), m_expansion(expansion), m_roller(roller), m_catapult(catapult) {}
void Robot::update_drivetrain() {
	m_drivetrain.update(m_controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), m_controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
	if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
		m_drivetrain.next_reference_frame();
	} else if (m_controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
		m_drivetrain.update(80, 0);
	}
}
void Robot::update_intake() {
	if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
		m_intake.toggle(false);
	}
	else if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
		m_intake.toggle(true);
	}
}
void Robot::update_expansion() {
	if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
		m_expansion.trigger();
	}
}
void Robot::update_roller() {
	if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
		m_roller.spin_wheel(1); 
	}
	if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
		m_roller.spin_wheel(-1); 
	}
	if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
		m_roller.switch_color();
	}
}
void Robot::update_catapult() {
	// to shoot it, already in launch position 
	if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
		// launches catapult forward
		m_catapult.spin_motor(0, 2500); 
		// moves it back to loading position
		m_catapult.spin_motor(1, 2500);
	}
	// presumably used to set it to load position
	if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
		m_catapult.spin_motor(0, 500);
	}
}
void Robot::update() {
	update_drivetrain();
	update_intake();
	update_expansion();
	update_roller();
	update_catapult();
}

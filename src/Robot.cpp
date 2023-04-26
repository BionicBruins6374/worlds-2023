#include "ports.hpp"
#include "pros/misc.h"
#include "pros/rtos.h"
#include <iostream>
#include "Robot.hpp"

Robot::Robot(Drivetrain drivetrain, Intake intake, Expansion expansion, Roller roller, Catapult catapult)
	: m_drivetrain(drivetrain), m_intake(intake), m_expansion(expansion), m_roller(roller), m_catapult(catapult)
	 {}

void Robot::update_controller() {
	// m_controller_partner.print(1,1, "Intake Motor Temp: %f", m_intake.get_temp());
	// m_controller.print(1,1,"Velocity: %f", m_catapult.get_voltage());
}


void Robot::update_drivetrain() {
	m_drivetrain.update( m_controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), m_controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) * -1);
	if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
		m_drivetrain.next_reference_frame();
	} else if (m_controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
		m_drivetrain.update(80, 0);
	}
}

void Robot::spinRollerIntake(std::string color) {
	pros::Task { [this, color] {
		m_intake.toggle(false);
		while(true) {
			if (m_roller.checkForOptical(color) == 1) {
				m_intake.toggle(false);
				break;
			} else if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
				m_intake.toggle(false);
				break;
			}
			pros::Task::delay(5);
		}
	} };
}
void Robot::spinOppositeRoller(std::string color) {
	pros::Task { [this, color] {
		m_intake.toggle(true);
		std::printf("%d\n",m_roller.checkForOptical(color));
		while(true) {
			if (m_roller.checkForOptical(color) == 1) {
				m_intake.toggle(true);
				break;
			} else if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
				m_intake.toggle(true);
				break;
			}
			pros::Task::delay(5);
		}
	} };
}

void Robot::update_intake_roller(std::string color) {
	m_roller.turn_light_on();
		if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
			spinRollerIntake(color);
		} else if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
			spinOppositeRoller(color);
		}
}

void Robot::autonomous_spin(std::string color) {
	m_roller.turn_light_on();
	m_intake.toggle(false);
	while (true) {
	if (m_roller.checkForOptical(color) == 1) {
		m_intake.toggle(false);
		break;
	}
	}
}

void Robot::update_expansion() {
	if (m_controller_partner.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT) || m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT) ) {
		m_expansion.trigger();
	}
}

void Robot::update_catapult() {
	// to shoot it, already in launch position 
	if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
		
		m_catapult.spin_motor(1);
		m_catapult.spin_motor(1);
		std::printf("%d", m_catapult.switch_ideal_value); 
	}
	if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
		m_catapult.spin_motor(1);
	}
	// presumably used to set it to load position
	if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
		m_catapult.set_voltage(12000);
	}
	if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
		m_catapult.break_cata();
	}
}



void Robot::update(std::string color) {
	update_drivetrain();
	update_intake_roller(color);
	update_expansion();
	update_catapult();
	update_controller();
}





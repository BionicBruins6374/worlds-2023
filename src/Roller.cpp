#include <cstdio>
#include <iostream>
#include "Roller.hpp"
#include "constants.hpp"
#include "pros/optical.hpp"

Roller::Roller(int8_t const port, bool redOrBlue, int8_t optical_front_port, int8_t optical_side_port) : 
m_motor{ port, pros::E_MOTOR_GEAR_BLUE }
, optical_front(optical_front_port)
, optical_side(optical_side_port )
 {
	m_motor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
	blue_alliance = redOrBlue;
}
void Roller::switch_color() const {
	// moves motor 180 degrees forward at a fast pace (switches roller color)
	m_motor.move_relative(180, 100);
}
void Roller::fine_adjust(RollerCode code) {
	switch (code) {
		case FORWARD:
			m_motor.move_velocity(127);
			m_on = true;
			break;
		case BACKWARD:
			m_motor.move_velocity(-127);
			m_on = true;
			break;
		case STOP:
			if (m_on == true) {
				m_motor.move_velocity(0);
				m_on = false;
			}
			break;
	};
}

void Roller::spin_wheel(double scaler) {
	// If motor previously on, turn it off
	if (m_on) {
		m_motor.move_velocity(0);
		m_on = false;
	}
	// If motor off, turn it on 
	else {
		m_motor.move_velocity(100 * scaler);
		m_on = true;
	}
}

void Roller::turn_off() {
	m_on = false;
	m_motor.move_velocity(0);
}

void Roller::optical_spin() {
	if (!blue_alliance) {
		while (true) {
			if (optical_front.get_hue() >= 345 && optical_front.get_hue() <= 360 || optical_front.get_hue() >= 0 && optical_front.get_hue() <= 15 ) {
      			m_motor.move_velocity(100);
				pros::Task::delay(5);
    		} 
			else {
      			m_motor.move_velocity(0);
				return;
    		}
		}
	}

	else if (blue_alliance) {
		while (true) {
			if (optical_front.get_hue() >= 210 && optical_front.get_hue() <= 280) {
				m_motor.move_velocity(100);
				pros::Task::delay(5);
			} 
			else {
				m_motor.move_velocity(0);
				return;
			}
		}
	}
	
    
}

void Roller::optical_spin(std::string color) {
	if (color == "r") {
		while (true) {
			if (optical_front.get_hue() >= 345 && optical_front.get_hue() <= 360 || optical_front.get_hue() >= 0 && optical_front.get_hue() <= 15 ) {
      			m_motor.move_velocity(100);
				pros::Task::delay(5);
    		} 
			else {
      			m_motor.move_velocity(0);
				return;
    		}
		}
	}
	else if (color == "b") {
		while (true) {
			if (optical_front.get_hue() >= 210 && optical_front.get_hue() <= 280) {
				m_motor.move_velocity(100);
				pros::Task::delay(5);
			} 
			else {
				m_motor.move_velocity(0);
				return;
			}
		}
	}
}



void Roller::switch_type() {
	if (roller_type == OPTICAL) {
		roller_type = MANUAL_CONTROL;
	}
	else {
		roller_type = OPTICAL;
	}
}
void Roller::main_spin_roller(int scaler, std::string color )  {
	switch (roller_type) {
		case OPTICAL:
			optical_spin(color);
			break;
		case MANUAL_CONTROL:
			spin_wheel(scaler);
			break;	
	}
}












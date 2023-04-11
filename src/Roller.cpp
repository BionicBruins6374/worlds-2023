#include "Roller.hpp"
#include "constants.hpp"

Roller::Roller(int8_t const port) : m_motor{ port, pros::E_MOTOR_GEAR_BLUE } {
	m_motor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
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
	return;
}

void Roller::switch_type() {
	if (roller_type == OPTICAL) {
		roller_type = MANUAL_CONTROL;
	}
	else {
		roller_type = OPTICAL;
	}
}
void Roller::main_spin_roller(int scaler )  {
	switch (roller_type) {
		case OPTICAL:
			optical_spin();
			break;
		case MANUAL_CONTROL:
			spin_wheel(scaler);
			break;	
	}
}












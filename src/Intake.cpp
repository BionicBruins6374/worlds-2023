#include "Intake.hpp"
#include "constants.hpp"
Intake::Intake(int8_t const left_port, int8_t const right_port) : m_left_motor{ left_port }, 
m_right_motor{ right_port, pros::E_MOTOR_GEAR_BLUE, true } {}
void Intake::set_on(bool value) {
	m_on = value;
	int velocity = 0;
	if (m_on) {
		velocity = reverse_velocity(constants::INTAKE_VELOCITY);
	}
	m_left_motor.move_velocity(velocity);
	// m_right_motor.move_velocity(velocity);
}

void Intake::toggle(bool const reverse) {
	if (m_on) {
		m_reverse = false;
	}
	m_reverse = reverse;
	set_on(!m_on);
}

int32_t Intake::reverse_velocity(int32_t const velocity) const {
	if (m_reverse) {
		return -1 * velocity;
	}
	return velocity;
}

int32_t Intake::get_temp()  {
	return m_left_motor.get_temperature();
}


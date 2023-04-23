#pragma once

#include "pros/adi.hpp"
#include "pros/motors.hpp"

class Catapult {
private:
	pros::Motor m_motor;
	pros::ADIDigitalIn m_limit_switch;

public:
    Catapult(int8_t left_back_motor_port, std::uint8_t port); 
	void spin_motor(int voltage_option, int shift_amount);
	void spin_motor(int voltage_option);

	void spin_motor_no_limit(double shift_amount);
	void set_voltage(double voltage);
	int switch_ideal_value = 0;
};

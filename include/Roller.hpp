#pragma once

#include <cstdint>
#include "pros/motors.hpp"
#include "pros/optical.hpp"

class Roller {
private:
	pros::Motor m_motor;
	bool m_on = false;
	pros::Optical optical_front;
	pros::Optical optical_side;
	bool blue_alliance;

public:
	enum RollerCode {
		FORWARD = 0,
		BACKWARD = 1,
		STOP = 2
	};

	enum RollerType {
		OPTICAL = 0,
		MANUAL_CONTROL = 1
	};


	RollerType roller_type = OPTICAL;

	Roller(int8_t const port, bool redOrBlue, int8_t optical_front_port, int8_t optical_side_port);
	void switch_color() const;
	void fine_adjust(RollerCode code);
	void spin_wheel(double scaler) ;	
	void turn_off();
	void optical_spin();
	void optical_spin(std::string color, int direction);
	void switch_type();
	void main_spin_roller(int scaler) ;
	void main_spin_roller(int scaler, std::string color) ;
	bool checkForOptical(std::string color);
	void turn_light_on();
};
#pragma once

#include "pros/misc.h"
#include "pros/misc.hpp"

#include "Drivetrain.hpp"
#include "Intake.hpp"
#include "Expansion.hpp"
#include "Roller.hpp"
#include "Catapult.hpp"


class Robot {
private:
	pros::Controller m_controller{ pros::E_CONTROLLER_MASTER };
	pros::Controller m_controller_partner { pros::E_CONTROLLER_PARTNER };
	Drivetrain m_drivetrain;
	Intake m_intake;
	Expansion m_expansion;
	Roller m_roller;
	Catapult m_catapult;
	void update_drivetrain();
	void update_intake_roller(std::string color);
	void update_expansion();

	void update_catapult();
	void update_controller(); 
public:

	Robot(Drivetrain drivetrain, Intake intake, Expansion expansion, Roller roller, Catapult catapult);
	void update();
	void update(std::string color);
	Catapult get_cata();
};


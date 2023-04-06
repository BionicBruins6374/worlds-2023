#pragma once

#include "pros/misc.hpp"

#include "Drivetrain.hpp"
#include "Intake.hpp"
#include "Expansion.hpp"
#include "Roller.hpp"
#include "Catapult.hpp"


class Robot {
private:
	pros::Controller m_controller{ pros::E_CONTROLLER_MASTER };
	Drivetrain m_drivetrain;
	Intake m_intake;
	Expansion m_expansion;
	Roller m_roller;
	Catapult m_catapult;
	void update_drivetrain();
	void update_intake();
	void update_expansion();
	void update_roller();
	void update_catapult();
public:

	Robot(Drivetrain drivetrain, Intake intake, Expansion expansion, Roller roller, Catapult catapult);
	void update();
};


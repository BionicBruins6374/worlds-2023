#include "okapi/impl/device/rotarysensor/IMU.hpp"
#include "pros/adi.hpp"
#include "pros/rtos.hpp"
#include "Drivetrain.hpp"
#include "Robot.hpp"
#include "Intake.hpp"
#include "Catapult.hpp"
#include "main.hpp"
#include "ports.hpp"
#include "odometry.hpp"
#include "Expansion.hpp"
#include "Inertial.hpp"
#include "okapi/impl/device/motor/motor.hpp"
#include "okapi/impl/device/motor/motorGroup.hpp"
#include "cmath"
#include "string"

double const TILE_LENGTH = 1.8266667; // feet
double const ROBOT_LENGTH = 1.5; // feet
double const ROLLER_LENGTH = 0.1666667; // feet

double const t = 1.826667;
double const r = 0.166667;

lv_obj_t * changeColor;
lv_obj_t * buttonLabel;
lv_obj_t * setLabel;
bool redOrBlue = false; //Red is false | Blue is true
char* buttonText = "r";
static lv_res_t btn_click_action(lv_obj_t * btn)
{
	redOrBlue = !redOrBlue;
	if (redOrBlue == true) {
		buttonText = "b";
	} else if (redOrBlue == false) {
		buttonText = "r";
	}
	lv_label_set_text(setLabel,buttonText);
	return LV_RES_OK;
}

void initialize() {
	changeColor = lv_btn_create(lv_scr_act(),NULL);
	lv_btn_set_action(changeColor, LV_BTN_ACTION_CLICK, btn_click_action);
	lv_obj_set_size(changeColor, 200, 50);
	buttonLabel = lv_label_create(changeColor, NULL);
	lv_label_set_text(buttonLabel, buttonText);
	setLabel = lv_label_create(lv_scr_act(),NULL);
	lv_label_set_text(setLabel,"Funny");

	
	// okapi::IMU(ports::INERTIAL_1).calibrate();
	// okapi::IMU(ports::INERTIAL_2).calibrate();
}

void disabled() {}
void competition_initialize() {}
void opcontrol() {
	Drivetrain const drivetrain{ ports::LEFT_BACK_MOTOR, ports::RIGHT_BACK_MOTOR, ports::LEFT_FRONT_MOTOR, ports::RIGHT_FRONT_MOTOR, ports::LEFT_MIDDLE_MOTOR, ports::RIGHT_MIDDLE_MOTOR };
	Intake const intake{ ports::INTAKE_LEFT, ports::INTAKE_RIGHT };
	Expansion const expansion{ ports::EXPANSION_PISTON_LEFT, ports::EXPANSION_PISTON_RIGHT};
	Roller const roller { ports::ROLLER, redOrBlue, ports::OPTICAL_SENSOR, ports::OPTICAL_SENSOR_BACK };
	Catapult const catapult {ports::CATAPULT_MOTOR, ports::LIMIT_SWITCH};
	Robot robot{ drivetrain, intake, expansion, roller, catapult};

	while (true) {
		robot.update(buttonText);
		pros::Task::delay(1);
	}
}

void launch_piston(void* hi) {
	pros::ADIDigitalOut pissLeft = pros::ADIDigitalOut{ports::EXPANSION_PISTON_LEFT};
	// pros::ADIDigitalOut pissRight = pros::ADIDigitalOut{ports::EXPANSION_PISTON_RIGHT};
	pissLeft.set_value(true); 
}

void auton_indirect(std::shared_ptr<ChassisController> chassis, Roller roller, Catapult cata, Intake intake, std::string alliance_color) {
	// start facing left if at top
	chassis->moveDistance(t * 1_ft);
	chassis->turnAngle(-90_deg); // clockwise 

	chassis->moveDistance((t-1.5) * 1_ft); // 1.5 is bot length in feet
	
	roller.main_spin_roller(1, alliance_color); // roller

	chassis->moveDistance((t-1.5) * -1_ft);
	
	chassis->turnAngle(-135_deg);

	chassis->moveDistance(sqrt( (pow((3*t/2),2) + pow((t - r + t/2),2) ) ) * 1_ft);
	chassis->turnAngle(-90_deg);

	chassis->moveDistance( (pow(sqrt(0.5 * t),2) + pow(sqrt(0.5 * t),2) - 0.1) * 1_ft );
	
	pros::c::task_create(launch_piston, (void*) "hi" , TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT,  "cata spin");
	cata.spin_motor(0);
	cata.spin_motor(1);

	chassis->moveDistance(0.1_ft); // move a tiny bit more forward (the 0.1)
	chassis->turnAngle(360_deg);
	
	// intake
	intake.toggle(false);
	pros::Task::delay(2000);
	intake.toggle(false);

	chassis->turnAngle(90_deg); // counterclock 90
	chassis->moveDistance( (pow(sqrt(0.5 * t),2) + pow(sqrt(0.5 * t),2) ) * 1_ft);
	
	// intake
	intake.toggle(false);
	pros::Task::delay(2000);
	intake.toggle(false);

	chassis->moveDistance( (pow(sqrt(0.5 * t),2) + pow(sqrt(0.5 * t),2) ) * 1_ft);
	chassis->turnAngle(90_deg); // counterclock 90
	
	// intake
	intake.toggle(false);
	pros::Task::delay(2000);
	intake.toggle(false);

}
void autonomous() {
	Drivetrain drivetrain{ ports::LEFT_BACK_MOTOR, ports::RIGHT_BACK_MOTOR, ports::LEFT_FRONT_MOTOR, ports::RIGHT_FRONT_MOTOR, ports::LEFT_MIDDLE_MOTOR, ports::RIGHT_MIDDLE_MOTOR };
	Intake intake{ ports::INTAKE_LEFT, ports::INTAKE_RIGHT };
	Expansion expansion{ ports::EXPANSION_PISTON_LEFT, ports::EXPANSION_PISTON_RIGHT};
	Roller roller { ports::ROLLER, redOrBlue, ports::OPTICAL_SENSOR, ports::OPTICAL_SENSOR_BACK };
	Catapult catapult {ports::CATAPULT_MOTOR, ports::LIMIT_SWITCH};
	Robot robot{ drivetrain, intake, expansion, roller, catapult};
	pros::Task::delay(1000);	


	okapi::MotorGroup left_m = okapi::MotorGroup({ okapi::Motor(ports::LEFT_BACK_MOTOR), okapi::Motor( ports::LEFT_MIDDLE_MOTOR), okapi::Motor(ports::LEFT_FRONT_MOTOR)});
	okapi::MotorGroup right_m = okapi::MotorGroup ({okapi::Motor(ports::RIGHT_BACK_MOTOR), okapi::Motor(ports::RIGHT_MIDDLE_MOTOR), okapi::Motor(ports::RIGHT_FRONT_MOTOR)});
	
	auto chass = build_PID(left_m, right_m, ports::INERTIAL_1, ports::INERTIAL_2);
	auto odom = build_odometry (left_m, right_m);

	okapi::IntegratedEncoder left_front_encoder = okapi::IntegratedEncoder(ports::LEFT_FRONT_MOTOR);
	okapi::IntegratedEncoder left_middle_encoder = okapi::IntegratedEncoder(ports::LEFT_MIDDLE_MOTOR);
	okapi::IntegratedEncoder left_back_encoder = okapi::IntegratedEncoder(ports::LEFT_BACK_MOTOR);
	okapi::IntegratedEncoder right_front_encoder = okapi::IntegratedEncoder(ports::RIGHT_FRONT_MOTOR);
	okapi::IntegratedEncoder right_middle_encoder = okapi::IntegratedEncoder(ports::RIGHT_MIDDLE_MOTOR);
	okapi::IntegratedEncoder right_back_encoder = okapi::IntegratedEncoder(ports::RIGHT_BACK_MOTOR);

	std::printf("left back: %f \n", left_back_encoder.get());
	std::printf("right back: %f \n", right_back_encoder.get());
	std::printf("left front: %f \n", left_front_encoder.get());
	std::printf("right front: %f \n", right_front_encoder.get());

	left_front_encoder.reset(); 
	left_middle_encoder.reset(); 
	left_back_encoder.reset(); 
	right_front_encoder.reset(); 
	right_middle_encoder.reset(); 
	right_back_encoder.reset();

	// so we can launch farther for auton
	// expansion.trigger();

	std::printf("move forward 2ft\n");
	
	auton_indirect(chass, roller, catapult,intake, buttonText);
	
}
// void autonomous() {
	// pros::Task::delay(100);
	// pros::ADIDigitalOut dig = pros::ADIDigitalOut{'H'};
	// dig.set_value(false);
	// std::printf("changed to false");
	// pros::Task::delay(300);
	// dig.set_value(true);

// }


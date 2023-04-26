#include "okapi/impl/chassis/controller/chassisControllerBuilder.hpp"
#include "okapi/impl/device/motor/motorGroup.hpp"
#include <cstdint>

using namespace okapi;

std::shared_ptr<OdomChassisController> build_odometry(okapi::MotorGroup left_motor, okapi::MotorGroup right_motor) {
	return okapi::ChassisControllerBuilder()
		.withMotors(left_motor, right_motor)
		.withDimensions(AbstractMotor::gearset::blue, {{3_in, 12_in}, imev5BlueTPR})
		.withOdometry() 
		.buildOdometry(); 
}
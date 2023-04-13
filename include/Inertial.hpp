#include "okapi/impl/chassis/controller/chassisControllerBuilder.hpp"
#include "okapi/api/chassis/controller/chassisControllerPid.hpp"

#include "okapi/impl/device/motor/motorGroup.hpp"
#include <cstdint>


std::shared_ptr<okapi::ChassisController> build_PID (okapi::MotorGroup left_motor, okapi::MotorGroup right_motor, int inertial1, int inertial2);
#include "okapi/impl/chassis/controller/chassisControllerBuilder.hpp"
#include "okapi/api/chassis/controller/chassisControllerPid.hpp"
#include "okapi/impl/device/rotarysensor/IMU.hpp"

#include "okapi/impl/device/motor/motorGroup.hpp"
#include "ports.hpp"
#include <cstdint>
#include <iostream>

using namespace okapi;

std::shared_ptr<ChassisController> build_PID (const okapi::MotorGroup left_motor, const okapi::MotorGroup right_motor, int inertial1, int inertial2) {
    auto inert1 = std::shared_ptr<IMU>(new IMU(inertial1));
    auto inert2 = std::shared_ptr<IMU>(new IMU(inertial1));

    return okapi::ChassisControllerBuilder()
    .withMotors(left_motor, right_motor)
    .withDimensions(AbstractMotor::gearset::blue, {{4_in, 15_in}, imev5GreenTPR})
    .withSensors(inert1, inert2)
    .withGains(
        {0.001, 0, 0.0001}, // Distance controller gains
        {0.001, 0, 0.0001}, // Turn controller gains
        {0.001, 0, 0.0001}  // Angle controller gains (helps drive straight)
    )
    .build();
}



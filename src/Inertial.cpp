#include "okapi/impl/chassis/controller/chassisControllerBuilder.hpp"
#include "okapi/api/chassis/controller/chassisControllerPid.hpp"
#include "okapi/impl/device/rotarysensor/IMU.hpp"
#include "okapi/api/filter/emaFilter.hpp"
#include "okapi/impl/device/motor/motorGroup.hpp"
#include "okapi/impl/util/timeUtilFactory.hpp"
#include "okapi/api/filter/filteredControllerInput.hpp"
#include "okapi/api/filter/emaFilter.hpp"
#include "ports.hpp"
#include <cstdint>
#include <iostream>
#include <memory>

using namespace okapi;

std::shared_ptr<ChassisController> build_PID (const okapi::MotorGroup left_motor, const okapi::MotorGroup right_motor, int8_t inertial1, int8_t inertial2) {
    std::shared_ptr<IMU> inert1 = std::shared_ptr<IMU>(new IMU(inertial1, okapi::IMUAxes::y));
    std::shared_ptr<IMU> inert2 = std::shared_ptr<IMU>(new IMU(inertial2, okapi::IMUAxes::x));
    
    
    inert1->calibrate(); inert2->calibrate();    
    return okapi::ChassisControllerBuilder()
        .withMotors(left_motor, right_motor)
        .withDimensions(AbstractMotor::gearset::blue, {{3_in, 12.0_in}, imev5BlueTPR})
        .withSensors(inert2, inert1)
        // .withGains(
        // {0.002, 0.01, 0.000}, // Distance controller gains
		// 	{0.000, 0.0, 0.000}, // Turn controller gains
		// 	{0.002, 0.01, 0.000} // Angle controller gains (helps drive straight)
        // )
        .build();

    
    // okapi::TimeUtil timeUtie = okapi::TimeUtilFactory::createDefault();
    // std::unique_ptr<okapi::IterativePosPIDController> itPosPid = std::make_unique<okapi::IterativePosPIDController(0.001, 0, 0.0001, 0, timeUtie)>();
    // okapi::ChassisControllerPID(timeUtie, chaz->getModel(), itPosPid, itPosPid, itPosPid); // set chassis scale and abstract motor
    // okapi::FilteredControllerInput<okapi::IMU> 
//     okapi::FilteredControllerInput(ControllerInput<okapi::IMU>,
// std::unique_ptr<okapi::EmaFilter>);

// std::unique_ptr<ControllerInput<okapi::IMU>> yas = std::make_unique(ControllerInput<okapi::IMU>);
}


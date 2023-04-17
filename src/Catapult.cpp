#include <cmath>
#include <cstdint>
#include <iostream>
#include "pros/rtos.hpp"
#include "pros/motors.hpp"
#include "pros/adi.hpp"
#include "pros/llemu.hpp"

#include "Catapult.hpp"
#include "constants.hpp"

Catapult::Catapult(int8_t motor_port, std::uint8_t port)
    : m_motor{motor_port, pros::E_MOTOR_GEAR_RED, true}
    , m_limit_switch{port}
{
}

void Catapult::spin_motor(int voltage_option) {
    const int timeout_ms = 5000; // set timeout to 5 seconds
    const auto start_time = pros::millis();

    while (m_limit_switch.get_value() == 0) {
        m_motor.move_voltage(constants::CATAPULT_VOLTAGE[voltage_option]);

        if (pros::millis() - start_time > timeout_ms) {
            pros::lcd::print(0, "Failed to reach limit switch within timeout\n");
            m_motor.move_voltage(0); // stop the motor
            break;
        }
    }
    m_motor.move_voltage(0); // stop the motor
}

void Catapult::spin_motor_no_limit(double shift_amount) {
    m_motor.set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);
    m_motor.move_relative(shift_amount, 200);
    m_motor.move_voltage(0); // stop the motor
}

void Catapult::set_voltage(double voltage) {
    m_motor.move_voltage(voltage);
}

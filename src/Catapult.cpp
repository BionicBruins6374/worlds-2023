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
    m_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

// void Catapult::spin_motor(int voltage_option) {
//     const int timeout = 3000; // set timeout to 3 seconds
//     bool limit_switch_pressed = false;
//     uint32_t start_time = pros::millis();
//     while (true) {
//         if (m_limit_switch.get_value() == 1) {
//             if (limit_switch_pressed) {
//                 break;
//             } else {
//                 limit_switch_pressed = true;
//             }
//         } else {
//             limit_switch_pressed = false;
//             m_motor.move_voltage(constants::CATAPULT_VOLTAGE[voltage_option]);
//         }

//         if (pros::millis() - start_time > timeout) {
//             std::printf("Spin motor timeout reached");
//             break;
//         }
//     }
//     m_motor.move_voltage(0);
// }

// change this so it only spins cata one way and call it twice in Robot.cpp
void Catapult::spin_motor(int voltage_option) {
    const int timeout = 3000; // set timeout to 3 seconds
    uint32_t start_time = pros::millis();
    // spin it till its not the ideal value, 

    while (!(m_limit_switch.get_value() == switch_ideal_value)) {
        m_motor.move_voltage(constants::CATAPULT_VOLTAGE[voltage_option]);
        if (pros::millis() - start_time > timeout) {
            std::printf("Spin motor timeout reached");
            break;
        }
        pros::Task::delay(50);

    }

    if (switch_ideal_value == 1) { switch_ideal_value = 0;}
    else { switch_ideal_value = 1; }
    m_motor.move_voltage(0);
    
}

void Catapult::spin_motor_no_limit(double shift_amount) {
    m_motor.set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);
    m_motor.move_relative(shift_amount, 200);
    m_motor.move_voltage(0); // stop the motor
}

void Catapult::set_voltage(double voltage) {
    m_motor.move_voltage(voltage);
}
#include <cmath>
#include <cstdint>
#include <iostream>
#include "pros/rtos.hpp"
#include "pros/adi.hpp"


#include "Catapult.hpp"

#include "constants.hpp"

Catapult::Catapult(int8_t motor_port, std::uint8_t port )
	: m_motor{ motor_port, pros::E_MOTOR_GEAR_RED, true }
    , m_limit_switch { port } {}

// spins gear clockwise until it touches the limit switch again
// will be called to move the catapult into loading position and to launch it
void Catapult::spin_motor(int voltage_option) {
    while (m_limit_switch.get_value() == 0) {// check this
        m_motor.move_voltage(constants::CATAPULT_VOLTAGE[voltage_option]);
    } 
}


void Catapult::spin_motor_no_limit(double shift_amount) {
    std::printf("spin motor called");
    m_motor.set_encoder_units(pros::motor_encoder_units_e_t::E_MOTOR_ENCODER_ROTATIONS);
    // std::printf(m_motor.get_position());
    m_motor.move_relative(shift_amount, 200);
    // m_motor.move_voltage(0);
}
void Catapult::set_voltage(double voltage) {
    std::printf("set voltage called");
    m_motor.move_voltage(voltage);
}

// get initial pot value
// while new pot value != pot value + x amnt (1000)
// m_motor.move_voltage()


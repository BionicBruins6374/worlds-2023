#include <cmath>
#include <cstdint>
#include <iostream>
#include "pros/rtos.hpp"
#include "pros/adi.hpp"


#include "Catapult.hpp"

#include "constants.hpp"

Catapult::Catapult(int8_t motor_port, std::uint8_t port )
	: m_motor{ motor_port, true }
    , potentiometer { port } {}

// spins gear clockwise until it touches the limit switch again
// will be called to move the catapult into loading position and to launch it
void Catapult::spin_motor(int voltage_option=0, int shift_amount=500) {
    int potentiometer_limit = potentiometer.get_value() + shift_amount;
    while ( potentiometer.get_value() < potentiometer_limit ) {
        m_motor.move_voltage(constants::CATAPULT_VOLTAGE[voltage_option]);
    }
    m_motor.move_voltage(0); 
}

// get initial pot value
// while new pot value != pot value + x amnt (1000)
// m_motor.move_voltage()



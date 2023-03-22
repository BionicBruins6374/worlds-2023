#include <cmath>
#include <cstdint>
#include <iostream>
#include "pros/rtos.hpp"
#include "pros/adi.hpp"


#include "Catapult.hpp"

#include "constants.hpp"

Catapult::Catapult(int8_t motor_port, std::uint8_t port )
	: m_motor{ motor_port, true }
    , m_limit_switch { port } {}

// spins gear clockwise until it touches the limit switch again
// will be called to move the catapult into loading position and to launch it
void Catapult::spin_motor(int voltage_option=0) {
    while (m_limit_switch.get_value() == 0) {// check this
        m_motor.move_voltage(-1 * constants::CATAPULT_VOLTAGE[voltage_option]);
    } 

}



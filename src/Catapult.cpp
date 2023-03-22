#include <cmath>
#include <cstdint>
#include <iostream>
#include "pros/rtos.hpp"
#include "pros/adi.hpp"


#include "Catapult.hpp"

#include "constants.hpp"

// void Catapult::shoot(int voltage_option) {
// // you spin the catapult motor until the limit switch is pressed
// std::int32_t lim_switch_pressed = 0;
// while (true) {
//     lim_switch_pressed = m_limit_switch.get_value();
//     m_motor.move_voltage(constants::CATAPULT_VOLTAGE[voltage_option]);
//     if (lim_switch_pressed ==1 ) {

//     }


// }

void Catapult::spin_motor(int voltage_option=0) {
    // spin gear clockwise until it touches the limit switch again
    // spin some more
    while (m_limit_switch.get_value() == 0) {// check this
        m_motor.move_voltage(-1 * constants::CATAPULT_VOLTAGE[voltage_option]);
    } 
    


}


// then when its launched
// make it move the gear until its back in the loading position by using the limit switch again to tell when it's in the position 
// the motor will only
//  move in one way 


// start off extended back 
// when press shoot: launch forward


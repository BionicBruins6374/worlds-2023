#include <cmath>
#include <cstdint>
#include "pros/adi.hpp"

#include "Expansion.hpp"

Expansion::Expansion(uint8_t const piston_port_left, uint8_t const piston_port_right): 
	m_piston_left{ piston_port_left }, m_piston_right{ piston_port_right } {}


void Expansion::trigger() {
	m_piston_left.set_value(true);
	m_piston_right.set_value(true);
}

void Expansion::trigger(bool state) {
	m_piston_left.set_value(state);
	m_piston_right.set_value(state);
}

void Expansion::trigger2() {
	piston_state = !piston_state;
	trigger(piston_state);
}

void Expansion::press_trigger() {
	m_count += 1;	
	if (m_count == 4) {
		trigger(); 
	}
}
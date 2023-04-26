#pragma once

#include <cstdint>

// namespace for port connections to V5 devices
namespace ports {

// constexpr uint8_t PISTON_INDEXER = 'A';
constexpr uint8_t EXPANSION_PISTON_LEFT = 'G';
constexpr uint8_t EXPANSION_PISTON_RIGHT = 'H';

constexpr int8_t OPTICAL_SENSOR = 20;
constexpr int8_t OPTICAL_SENSOR_BACK = 21;


constexpr int8_t LEFT_BACK_MOTOR = 7;

constexpr int8_t LEFT_MIDDLE_MOTOR = 6;
constexpr int8_t LEFT_FRONT_MOTOR = 5;

constexpr int8_t RIGHT_BACK_MOTOR = 2;
constexpr int8_t RIGHT_MIDDLE_MOTOR = 3;
constexpr int8_t RIGHT_FRONT_MOTOR = 4; // under motor is front

constexpr int8_t INTAKE_LEFT = 10;
constexpr int8_t INTAKE_RIGHT =  15;

constexpr int8_t ROLLER = 13;

constexpr int8_t CATAPULT_MOTOR = 8;
constexpr uint8_t LIMIT_SWITCH = 'D'; 

constexpr int8_t INERTIAL_1 = 1; // right
constexpr int8_t INERTIAL_2 = 9; // left

}  // namespace ports 
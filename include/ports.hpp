#pragma once

#include <cstdint>

// namespace for port connections to V5 devices
namespace ports {
constexpr int8_t FLYWHEEL = 12;

constexpr uint8_t PISTON_INDEXER = 'A';
constexpr uint8_t EXPANSION_PISTON_LEFT = 'B';
constexpr uint8_t EXPANSION_PISTON_RIGHT = 'C';

constexpr int8_t OPTICAL_SENSOR = 20;

constexpr int8_t LEFT_BACK_MOTOR = 2;
constexpr int8_t RIGHT_BACK_MOTOR = 1;
constexpr int8_t LEFT_FRONT_MOTOR = 10;
constexpr int8_t RIGHT_FRONT_MOTOR = 9;
constexpr int8_t LEFT_MIDDLE_MOTOR = 12;
constexpr int8_t RIGHT_MIDDLE_MOTOR = 3;

constexpr int8_t INTAKE_LEFT = 13;
constexpr int8_t INTAKE_RIGHT = 5;

constexpr int8_t ROLLER = 13;

constexpr int8_t CATAPULT_MOTOR = 4; // TODO: CHANGE THIS
constexpr uint8_t POTENTIOMETER = 'D';
}  // namespace ports

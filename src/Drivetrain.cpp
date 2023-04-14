#include <cmath>
#include "Drivetrain.hpp"
#include "constants.hpp"

Drivetrain::Drivetrain(int8_t const left_back_motor_port, int8_t const right_back_motor_port, int8_t const left_front_motor_port, int8_t const right_front_motor_port, int8_t const right_middle_motor_port, int8_t const left_middle_motor_port)
    : m_left_back_motor{ left_back_motor_port, pros::E_MOTOR_GEAR_BLUE, true }
    , m_right_back_motor{ right_back_motor_port, pros::E_MOTOR_GEAR_BLUE }
    , m_left_front_motor{ left_front_motor_port, pros::E_MOTOR_GEAR_BLUE, true }
    , m_right_front_motor{ right_front_motor_port, pros::E_MOTOR_GEAR_BLUE }
    , m_left_middle_motor{ left_middle_motor_port, pros::E_MOTOR_GEAR_BLUE, true }
    , m_right_middle_motor{ right_middle_motor_port, pros::E_MOTOR_GEAR_BLUE }
	, m_drive_turn_sensitivity{constants::drive_turn_sensitivity}
{
}

static float scale(float const raw)
{
    return std::pow(raw / constants::CONTROLLER_ANALOG_MAX, 3.0f) * constants::DRIVE_MAX_VOLTAGE * constants::DRIVE_DAMPENING;
}

void Drivetrain::update(int32_t forward_backward_axis_int, int32_t left_right_axis_int)
{
    switch (m_reference_frame) {
        case DrivetrainReferenceFrame::IntakeAtFront:
            break;
        case DrivetrainReferenceFrame::FlywheelAtFront:
            forward_backward_axis_int *= -1;
            left_right_axis_int *= 1;
            break;
    }

    auto forward_backward_axis = static_cast<float>(forward_backward_axis_int);
    auto left_right_axis = static_cast<float>(left_right_axis_int);
	left_right_axis = scale(left_right_axis);
	left_right_axis *= m_drive_turn_sensitivity;


    forward_backward_axis = scale(forward_backward_axis);

    auto const turn_differential = left_right_axis * constants::drive_turn_sensitivity;

    auto const left_voltage = static_cast<int32_t>(forward_backward_axis - turn_differential);
    auto const right_voltage = static_cast<int32_t>(forward_backward_axis + turn_differential);

    m_left_back_motor.move_voltage(left_voltage);
    m_left_front_motor.move_voltage(left_voltage);
    m_left_middle_motor.move_voltage(right_voltage);

    m_right_back_motor.move_voltage(right_voltage);
    m_right_front_motor.move_voltage(right_voltage);
    m_right_middle_motor.move_voltage(left_voltage);
}

void Drivetrain::next_reference_frame()
{
    switch (m_reference_frame) {
        case DrivetrainReferenceFrame::IntakeAtFront:
            m_reference_frame = DrivetrainReferenceFrame::FlywheelAtFront;
            break;
        case DrivetrainReferenceFrame::FlywheelAtFront:
            m_reference_frame = DrivetrainReferenceFrame::IntakeAtFront;
            break;
    }
}

#include "okapi/impl/chassis/controller/chassisControllerBuilder.hpp"
#include "okapi/api/chassis/controller/chassisControllerPid.hpp"

#include "okapi/impl/device/motor/motorGroup.hpp"
#include <cstdint>


class Optical {
    private:
        pros::Optical optical_front;
	    pros::Optical optical_back;
    public:
        double get_optical_front();
        double get_optical_side();
        Optical(std::uint8_t front_port, std::uint8_t back_fort);
};   
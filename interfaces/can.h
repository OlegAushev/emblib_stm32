#pragma once


#include <array>
#include <cstdint>


using can_payload = std::array<uint8_t, 8>;
using can_id = uint32_t;


struct can_frame {
    can_id id;
    unsigned int len;
    can_payload payload;
};


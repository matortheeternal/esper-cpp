#ifndef ESPER_ELEMENT_STATE_H_
#define ESPER_ELEMENT_STATE_H_

#include <cstdint>
#include "Flags.h"

namespace esper {
    class ElementState : public Flags<uint8_t> {
    public:
        static constexpr uint8_t modified = 0x01;
        static constexpr uint8_t filterShow = 0x02;
    };
}

#endif
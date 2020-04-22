#ifndef ESPER_FLAGS_H_
#define ESPER_FLAGS_H_

namespace esper {
    template<typename T>
    class Flags {
    public:
        void set(T flags) {
            value |= flags;
        }

        bool has(T flags) {
            return value & flags;
        }

        void clear(T flags) {
            value &= ~flags;
        }

        void toggle(T flags) {
            value ^= flags;
        }

        T value = 0;
    };
}

#endif
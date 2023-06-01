#pragma once


#include <cstdint>
#include <cstddef>
#include <cassert>


namespace emb {

template <class T>
class monostate {
private:
    static inline bool _initialized = false;
protected:
    monostate() {
        assert(_initialized);
    }

    ~monostate() = default;

    static void set_initialized() {
        assert(!_initialized);
        _initialized = true;
    }
public:
    static bool initialized() { return _initialized; }
};

} // namespace emb


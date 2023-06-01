#pragma once


#include <emblib_stm32/core.h>


namespace emb {

namespace chrono {

namespace impl {

template <int64_t Divider>
class duration {
public:
    static const int64_t divider = Divider;
private:
    int64_t _ticks;
public:
    duration() : _ticks(0) {}
    explicit duration(int64_t tick_count) : _ticks(tick_count) {}
    duration(const duration& other) { this->_ticks = other._ticks; }
    duration& operator=(const duration& other) {
        if (this != &other) {
            this->_ticks = other._ticks;
        }
        return *this;
    }

    int64_t count() const { return _ticks; }

    duration& operator++() {
        ++_ticks;
        return *this;
    }

    duration& operator--() {
        --_ticks;
        return *this;
    }

    duration operator++(int) {
        duration tmp(*this);
        ++_ticks;
        return tmp;
    }

    duration operator--(int) {
        duration tmp(*this);
        --_ticks;
        return tmp;
    }
};


template <int64_t Divider>
duration<Divider> operator+(const duration<Divider>& lhs, const duration<Divider>& rhs) {
    return duration<Divider>(lhs.count() + rhs.count());
}


template <int64_t Divider>
duration<Divider> operator-(const duration<Divider>& lhs, const duration<Divider>& rhs) {
    return duration<Divider>(lhs.count() - rhs.count());
}

template <int64_t Divider>
bool operator>(const duration<Divider>& lhs, const duration<Divider>& rhs) { return lhs.count() > rhs.count(); }
template <int64_t Divider>
bool operator>=(const duration<Divider>& lhs, const duration<Divider>& rhs) { return lhs.count() >= rhs.count(); }
template <int64_t Divider>
bool operator<(const duration<Divider>& lhs, const duration<Divider>& rhs) { return lhs.count() < rhs.count(); }
template <int64_t Divider>
bool operator<=(const duration<Divider>& lhs, const duration<Divider>& rhs) { return lhs.count() <= rhs.count(); }
template <int64_t Divider>
bool operator==(const duration<Divider>& lhs, const duration<Divider>& rhs) { return lhs.count() == rhs.count(); }
template <int64_t Divider>
bool operator!=(const duration<Divider>& lhs, const duration<Divider>& rhs) { return lhs.count() != rhs.count(); }

} // namespace impl


template<typename ToDuration, int64_t Divider>
ToDuration duration_cast(const impl::duration<Divider> duration) {
    return impl::duration<ToDuration::divider>(duration.count() * Divider / ToDuration::divider);
}


typedef impl::duration<1> nanoseconds;
typedef impl::duration<1000> microseconds;
typedef impl::duration<1000000> milliseconds;
typedef impl::duration<1000000000> seconds;

} // namespace chrono

} // namespace emb


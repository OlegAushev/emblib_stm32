#pragma once


#include <cstdint>
#include <cstddef>
#include <cassert>


namespace emb {

class noncopyable {
public:
    noncopyable() = default;
    noncopyable(const noncopyable& other) = delete;
    noncopyable& operator=(const noncopyable& other) = delete;
    virtual ~noncopyable() = default;
};

} // namespace emb


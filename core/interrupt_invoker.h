#pragma once


#include <cstdint>
#include <cstddef>
#include <cassert>


namespace emb {

template <class T>
class interrupt_invoker {
private:
    static inline T* _instance = nullptr;
    static inline bool _initialized = false;
protected:
    interrupt_invoker(T* self) {
        assert(!_initialized);
        _instance = self;
        _initialized = true;
    }
public:
    static T* instance() {
        assert(_initialized);
        return _instance;
    }

    static bool initialized() { return _initialized; }

    virtual ~interrupt_invoker() {
        _initialized = false;
        _instance = nullptr;
    }
};


template <class T, int Size>
class interrupt_invoker_array
{
private:
    static inline T* _instance[Size];
    static inline bool _initialized[Size];
    static inline bool _constructed = false;
protected:
    interrupt_invoker_array(T* self, int instance_num) {
        assert(instance_num < Size);
        assert(!_initialized[instance_num]);
        if (!_constructed) {
            for (int i = 0; i < Size; ++i) {
                _instance[i] = nullptr;
                _initialized[i] = false;
            }
            _constructed = true;
        }

        _instance[instance_num] = self;
        _initialized[instance_num] = true;
    }
public:
    static T* instance(int instance_num) {
        assert(_constructed);
        assert(instance_num < Size);
        assert(_initialized[instance_num]);
        return _instance[instance_num];
    }

    static bool initialized(int instance_num) {
        assert(instance_num < Size);
        if (!_constructed) return false;
        return _initialized[instance_num];
    }
};

} // namespace emb


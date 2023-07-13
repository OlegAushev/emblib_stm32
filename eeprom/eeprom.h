#pragma once


#include "../core.h"
#include <chrono>
#include <cstring>


namespace emb {

namespace eeprom {

enum class Error {
    none,
    read_failed,
    write_failed,
    read_timeout,
    write_timeout,
    invalid_address,
    invalid_data_size,
    data_corrupted,
    no_device,
};

class DriverInterface {
public:
    virtual Error read(int page, int offset, uint8_t* buf, int len, std::chrono::milliseconds timeout) = 0;
    virtual Error write(int page, int offset, const uint8_t* buf, int len, std::chrono::milliseconds timeout) = 0;
    virtual int page_bytes() const = 0;
    virtual int page_count() const = 0;
};


class Storage {
private:
    DriverInterface& _driver;
    uint32_t (*_calc_crc32)(const uint8_t*, int);

    const int available_page_bytes;
    const int available_page_count;

    struct {
        uint32_t read;
        uint32_t write;
        uint32_t crc_mismatch;

        uint32_t primary_data_corrupted;
        uint32_t secondary_data_corrupted;
        uint32_t fatal;
    } _errors;
public:
    Storage(DriverInterface& driver_, uint32_t (*calc_crc32_func_)(const uint8_t*, int));
    Error read(int page, uint8_t* buf, int len, std::chrono::milliseconds timeout);
    Error write(int page, const uint8_t* buf, int len, std::chrono::milliseconds timeout);

    template <typename T>
    Error read(int page, T& data, std::chrono::milliseconds timeout) {
        uint8_t data_bytes[sizeof(T)];
        Error error = read(page, data_bytes, sizeof(T), timeout);
        memcpy(&data, data_bytes, sizeof(T));
        return error;
    }

    template <typename T>
    Error write(int page, const T& data, std::chrono::milliseconds timeout) {
        uint8_t data_bytes[sizeof(T)];
        memcpy(data_bytes, &data, sizeof(T));
        return write(page, data_bytes, sizeof(T), timeout);
    }
};

} // namespace eeprom

} // namespace emb


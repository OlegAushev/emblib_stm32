#include <emblib_stm32/core.h>


namespace emb {

__attribute__((weak)) void fatal_error_cb(const char* hint, int code)
{
    /* DO NOTHING */
}

} // namespace emb


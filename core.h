#pragma once


#include <cstdint>
#include <cstddef>
#include <cassert>

#include "core/interrupt_invoker.h"
#include "core/monostate.h"
#include "core/noncopyable.h"


#define EMB_UNIQ_ID_IMPL(arg) a_local_var_##arg
#define EMB_UNIQ_ID(arg) EMB_UNIQ_ID_IMPL(arg)


#define EMB_STRINGIZE_IMPL(x) #x
#define EMB_STRINGIZE(x) EMB_STRINGIZE_IMPL(x)


namespace emb {

inline void empty_function()
{
    /* DO NOTHING */
}


[[ noreturn ]] inline void invalid_function()
{
    while (true) {}
}


void fatal_error_cb(const char* hint, int code);


[[ noreturn ]] inline void fatal_error(const char* hint, int code = 0)
{	
    fatal_error_cb(hint, code);
    while (true) {}
}

} // namespace emb



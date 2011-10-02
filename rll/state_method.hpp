#pragma once

#include <rll/detail/lambda_method.hpp>
#include "detail/state_method_base.hpp"

namespace rll {

#ifdef DOXYGEN

/// @brief Learning method with eligibility traces for estimating state value function.
class state_method : public detail::lambda_method<detail::state_method_base> 
{
public:
    state_method(state_environment* env, const config& config) 
        : lambda_method<detail::state_method_base>(env, config)
    {
    }
};

#else

typedef detail::lambda_method<detail::state_method_base> state_method;

#endif

}

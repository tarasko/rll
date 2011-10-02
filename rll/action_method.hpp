#pragma once

#include <rll/detail/lambda_method.hpp>
#include <rll/detail/action_method_base.hpp>

namespace rll {

#ifdef DOXYGEN

/// @brief Learning method with eligibility traces for estimating state-action value function.
class action_method : public detail::lambda_method<detail::action_method_base>
{
public:
    action_method(action_environment* env, const config& config) 
        : lambda_method<detail::action_method_base>(env, config)
    {
    }
};

#else

typedef detail::lambda_method<detail::action_method_base> action_method;

#endif

}

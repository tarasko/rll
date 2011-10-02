#pragma once

#include "method_base.hpp"
#include "../policy/iface.hpp"

namespace rll { namespace detail {

/// @brief Base class for methods which operate on state-action pairs
class action_method_base : public method_base 
{
public:
    action_method_base(action_environment* env, const config& config);

protected:
    /// @brief Process episode as actions-states method.
    virtual void run_episode_impl();

private:
    typedef policy::iface::variants value_action_map;

    /// Used internally by run_episode_impl
    /// Makeing this as member helps to avoid allocations for next 
    /// possible state on each step.
    value_action_map variants_; 
};

}}

#pragma once

#include <rll/detail/environment_base.hpp>
#include <rll/detail/action_method_base.hpp>
#include <rll/detail/lambda_method.hpp>

#include <rll/state_with_reserved_action.hpp>

namespace rll {

/// @brief Environment for state-action value function.
/// @copydetails detail::environment_base
class action_environment : public detail::environment_base
{
public:
    /// @brief State type suitable for this environment.
    typedef state_with_reserved_action state_type;
    /// @brief Learning method for estimating value function.
    typedef detail::lambda_method<detail::action_method_base> method_type;

    /// @name Pure virtual`s that must be implemented
    //@{
#ifdef DOXYGEN
    /// @brief Method will call this when new episode begins.
    virtual void init_episode() = 0;

    /// @brief Must return current active agent index.
    virtual size_t active_agent() const = 0;
#endif

    /// @brief Return current state.
    virtual state_type current_state() const = 0;

    /// @brief Get possible actions for active agent for current environment state.
    virtual std::vector<rll_type> get_possible_actions() const = 0;

    /// @brief Active agent should take current action and recieve reward.
    ///
    /// @return True if method should continue with next step, false if we got to terminal state.
    virtual bool do_action_assign_rewards(rll_type action) = 0;
    //@}
};

}

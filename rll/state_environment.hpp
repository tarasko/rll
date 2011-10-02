#pragma once

#include <rll/detail/environment_base.hpp>
#include "state.hpp"
#include "state_method.hpp"

namespace rll {

/// @brief Environment for state value function.
/// @copydetails detail::environment_base
class state_environment : public detail::environment_base
{
public:
    /// @brief State type suitable for this environment.
    typedef state state_type;
    /// @brief Learning method for estimating value function.
    typedef state_method method_type;

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

    /// @brief Get possible next states for active agent for current environment state.
    virtual std::vector<state_type> get_possible_next_states() const = 0;

    /// @brief Set one of state returned from get_possible_next_states as current, assign rewards to agents.
    ///
    /// To assign rewards to agents, call agent::add_reward.
    /// This method also may change active agent.
    ///
    /// @return True if method should continue with next step, false if we got to terminal state.
    virtual bool set_next_state_assign_rewards(const state_type& state) = 0;
    //@}
};

}

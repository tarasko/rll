#pragma once

#include "../rll_fwd.hpp"
#include "../state.hpp"
#include "../config.hpp"

namespace rll { namespace detail {

class environment_base;

/// @brief Base class for RL methods.
class method_base 
{
public:
    method_base(environment_base* env, const config& config);
    virtual ~method_base();

    /// @brief Run training loop.
    /// @param episodes - Number of episodes to train
    void run(unsigned int episodes);

    /// @brief Return current episode starting from 0.
    unsigned int episode() const;

    /// @brief Return current step in episode starting from 0.
    unsigned int step() const;

protected:
    /// @brief Run single episode.
    virtual void run_episode_impl() = 0;  

    /// @brief Update value function for specific agent with new reward.
    ///
    /// @param active_agent - current active agent
    /// @param active_agent_idx - active agent index
    /// @param policy_selection_value - value function prediction for action selected by policy
    /// @param greedy_selection_value - value function prediction for greedy action
    /// @param reward - reward that agent got by selecting new state
    virtual void update_value_function_impl(
        const agent_sp& active_agent
      , int active_agent_idx
      , double policy_selection_value
      , double greedy_selection_value
      , double reward
      ) = 0;

    config config_;          //!< Config information
    environment_base* env_;  //!< Environment

    unsigned int episode_;   //!< Current episode
    unsigned int step_;      //!< Current step in episode
};

inline method_base::~method_base()
{
}

inline unsigned int method_base::episode() const
{
    return episode_;
}

inline unsigned int method_base::step() const
{
    return step_;
}

}}

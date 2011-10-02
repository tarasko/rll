#include <rll/detail/method_base.hpp>
#include <rll/detail/environment_base.hpp>

#include <rll/agent.hpp>

#include <cassert>
#include <functional>
#include <algorithm>

namespace rll { namespace detail {

method_base::method_base(environment_base* env, const config& config)
    : config_(config)
    , env_(env)
    , episode_(0)
    , step_(0)
{
    assert(env);
}

void method_base::run(unsigned int episodes)
{
    env_->method_ = this;

    for (episode_ = 0; episode_ < episodes; ++episode_) try
    {
        step_ = 0;

        // Reset previous state for all agents
        std::for_each(
            env_->agents().begin()
          , env_->agents().end()
          , [](agent_sp& agent) -> void
            {
                agent->set_prev_state(vector_rllt_csp());
            }
          );

        run_episode_impl();
    }
    catch(...)
    {
        env_->method_ = 0;
        throw;
    }

    env_->method_ = 0;
}

}}

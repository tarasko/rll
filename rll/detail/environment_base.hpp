#pragma once

#include "../rll_fwd.hpp"
#include "method_base.hpp"

namespace rll { namespace detail {

/// @brief Environment base class.
/// 
/// Application must inherit one of state_environment or action_environment and override virtuals.
/// During construction you have to create agents and push them to agents vector.
class environment_base
{
    friend class method_base;

public:
    /// @name Agent accessors
    //@{
    std::vector<agent_sp>& agents();
    const std::vector<agent_sp>& agents() const;
    //@}

    /// @copybrief method_base::episode
	unsigned int episode() const ;

    /// @copybrief method_base::step
	unsigned int step() const;

#ifndef DOXYGEN
    /// @name Pure virtual that must be overrided
    //@{
    virtual void init_episode() = 0;
    virtual size_t active_agent() const = 0;
    //@}
#endif

private:
    std::vector<agent_sp> agents_;      //!< Agents vector
    const detail::method_base* method_; //!< Backref to method that works on environment
};

inline std::vector<agent_sp>& environment_base::agents()
{
    return agents_;
}

inline const std::vector<agent_sp>& environment_base::agents() const
{
    return agents_;
}

inline unsigned int environment_base::episode() const
{
    return method_->episode();
}

inline unsigned int environment_base::step() const
{
    return method_->step();
}

}}

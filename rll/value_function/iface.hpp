#pragma once

#include "../rll_fwd.hpp"
#include "iface.hpp"

#include <utility>
#include <vector>

namespace rll { namespace value_function {

/// @brief Interface for value function.
/// 
/// Value function approximate cummulative expected reward. This interface define
/// how to get state(state-action) value, and how to replace current values for set 
/// of states with new values.
template<typename RllType>
class iface_tpl
{
public:
    typedef std::vector<RllType> state_rep;
    typedef std::shared_ptr<const state_rep> state_rep_csp;

    /// @brief Vector of states and state new values
    typedef std::vector<std::pair<state_rep_csp, double> > update_list;

    virtual ~iface_tpl() {}

    /// @brief Return value for serialized representation of state.
    virtual double get_value(const state_rep_csp& st) = 0;

    /// @brief Update value function according update list.
    ///
    /// Replace state values according to update list.
    virtual void update(const update_list& lst) = 0;
};

}}

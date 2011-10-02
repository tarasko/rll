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
class iface
{
public:
    /// @brief Vector of states and state new values
    typedef std::vector<std::pair<vector_rllt_csp, double> > update_list;

    virtual ~iface() {}

    /// @brief Return value for serialized representation of state.
    virtual double get_value(const vector_rllt_csp& st) = 0;

    /// @brief Update value function according update list.
    ///
    /// Replace state values according to update list.
    virtual void update(const update_list& lst) = 0;
};

}}

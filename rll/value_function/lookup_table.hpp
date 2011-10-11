#pragma once

#include "iface.hpp"

#include "../detail/utils.hpp"

#include <unordered_map>

namespace rll { namespace value_function {

/// @brief Implement value function based on lookup table.
///
/// Available only for integer version of rll.
class lookup_table : public iface_int
{
public:
    /// @brief Construct lookup table, use init as initial value for states.
    lookup_table(double init = 0.0);

    /// @copybrief iface_tpl::get_value
    virtual double get_value(const state_rep_csp& st);

    /// @copybrief iface_tpl::update
    virtual void update(const update_list& lst);

private:

    typedef std::unordered_map<
        state_rep_csp
      , double
      , detail::eval_vector_int_csp_hash
      , detail::is_equal_vector_int_csp
      > value_map;
    
    value_map values_;  //!< Map from data vector to value.
    double init_;       //!< Initial value for new states.
};

inline lookup_table::lookup_table(double init) 
    : init_(init) 
{
}

}}

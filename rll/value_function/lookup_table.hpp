#pragma once

#if !defined(RLL_INT)
#error "Lookup table is only available in integer version of RLL"
#endif

#include "iface.hpp"

#include "../detail/utils.hpp"

#include <unordered_map>

namespace rll { namespace value_function {

/// @brief Implement value function based on lookup table.
///
/// Available only for integer version of rll.
class lookup_table : public iface 
{
public:
    /// @brief Construct lookup table, use init as initial value for states.
    lookup_table(double init = 0.0);

    /// @copybrief iface::get_value
    virtual double get_value(const vector_rllt_csp& st);

    /// @copybrief iface::update
    virtual void update(const update_list& lst);

private:

    typedef std::unordered_map<
        vector_rllt_csp
      , double
      , detail::eval_vector_rllt_csp_hash
      , detail::is_equal_vector_rllt_csp
      > value_map;
    
    value_map values_;  //!< Map from data vector to value.
    double init_;       //!< Initial value for new states.
};

inline lookup_table::lookup_table(double init) 
    : init_(init) 
{
}

}}

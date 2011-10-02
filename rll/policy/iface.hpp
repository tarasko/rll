#pragma once

#include "../rll_fwd.hpp"

#include <random>

namespace rll { namespace policy {

/// @brief Policy interface.
/// 
/// The general definition of policy is a mapping from each state, S, and action, A, 
/// to the probability of taking action when in state S.
/// However this interface doesn`t provide methods to evaluate probalities, instead
/// it must answer what action must be choosen from possible actions in 
/// current state. To make this decision each action must be provided together with 
/// estimated value.
class iface
{
public:
    /// @brief Estimated value -> state (or state-action)
    typedef std::pair<double, vector_rllt_sp> selection;
    /// @brief Possible states (or state-actions) with estimated values
    typedef std::vector<selection> variants;

    virtual ~iface();

    /// @brief Select action(or state) from possible variants.
    virtual const selection& select(const variants& sorted_variants) = 0;

protected:
    std::mt19937 gen_; //!< Random number generator
};

inline iface::~iface() 
{
}

}}

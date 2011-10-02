#pragma once

#include "greedy.hpp"

namespace rll { namespace policy {

/// @brief Epsilon greedy policy.
///
/// This policy allows to do exploration and explotation simultaniosly.
/// The frequency of choosing random action instead of that having maximal 
/// value (greedy action) is defined by epsilon parameter passed during 
/// construction.
class egreedy : public iface
{
public:
    /// @brief Construct epsilon-greedy policy.
    /// @param epsilon - frequency of choosing non-greedy action.
    egreedy(double epsilon = 0.05);

    /// @copybrief iface::select
    virtual const selection& select(const variants& sorted_variants);

private:
    greedy greedy_;
    double epsilon_;
};

}}

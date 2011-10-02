#pragma once

#include "iface.hpp"

namespace rll { namespace policy {

/// @brief Simple greedy policy.
///
/// Always select action that has maximal value.
/// If few variants have same maximal value then one them will be choosen randomly.
class greedy : public iface
{
    friend class egreedy;

public:
    /// @copybrief iface::select
    virtual const selection& select(const variants& sorted_variants);

private:
    const selection& select_with_hint(
        const variants& sorted_variants
      , variants::const_iterator lb_hint
      );
};

}}

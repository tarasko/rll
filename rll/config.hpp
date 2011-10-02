#pragma once

#include <rll/rll_fwd.hpp>

namespace rll {

/// @brief Configuration for learing method.
struct config 
{
    /// @brief Construct configuration with default values.
    config() 
        : alpha_(0.05)
        , lambda_(0.5)
        , gamma_(1.0)
        , accumulating_(false)
        , traces_epsilon_(0.001)
    {
    }

    double alpha_;       //!< Alpha - stepsize parameter for RL methods.
    double lambda_;      //!< Lambda used in eligibility traces.
    double gamma_;       //!< Gamma - discount rate for return calculating.
    bool accumulating_;  //!< Should use accumulating or replacing elegibility traces.

    /// @brief Epsilon value for eligibility traces.
    ///
    /// If trace value for state is less then epsilon it would be eliminated.
    double traces_epsilon_;
};

}

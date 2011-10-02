#pragma once

#include "iface.hpp"

struct fann;

namespace rll { namespace value_function {

/// @brief Implements value function based on neuronal network.
/// 
/// @bug Completelly not tested. We need some example that is well 
/// suited for neuronal network. May be card-pole balancing task?
class neuronal_network : public iface 
{
public:
    /// @brief Construct neuronal network.
    /// 
    /// @param hidden - number of neurons in hidden layer.
    /// @param min_val - minimal value for value function.
    /// @param max_val - maximal value for value function.
    neuronal_network(
        unsigned int hidden
      , double min_val = -1.0
      , double max_val = 1.0
      );
    ~neuronal_network();

    /// @copybrief iface::get_value
    virtual double get_value(const vector_rllt_csp& st);

    /// @copybrief iface::update
    virtual void update(const update_list& lst);

private:
    fann* create_nn(size_t input_size);

    /// @brief Use center and scale to make outputs for training set.
    double scale_in(double val);

    /// @brief Use center and scale to make val func from network output.
    double scale_out(double val);

    fann* fann_;
    unsigned int hidden_;
    double min_;
    double max_;
    double center_; //!< Defines the center beetwen min and max values
    double scale_;  //!< Defines the scale rate for output values

};

}}


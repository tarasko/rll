#pragma once

#include <rll/rll_fwd.hpp>

#include <algorithm>
#include <cassert>


namespace rll {

/// @brief Represent agent state with reserved slot for action.
///
/// @copydetails state
/// The difference from rll::state is that this class reserves additional slot 
/// for action value in serialized state representation. The reason is that 
/// value function interface doesn`t make difference between state and 
/// state-action it works only with serialized representation which in case 
/// of state-action must already contain additional signal with action value.
/// This action value assigns each time we get serialized representation. 
/// Check state_with_reserved_action::get_internal_rep method.
class state_with_reserved_action
{
public:
    /// @name Constructors.
    //@{
    /// @brief Construct empty state.
    ///
    /// Some stl construct require types to be DefaultConstructible. The direct use 
    /// of this constructor should be avoided.
    state_with_reserved_action();

    /// @brief Construct state with specified number of signals
    state_with_reserved_action(size_t signals_num);
    //@}

    /// @name State signal accessors.
    //@{
    const rll_type& operator[](size_t idx) const;
    rll_type& operator[](size_t idx);
    //@}
    
    /// @name Serialized representation accessors.
    //@{
    vector_rllt_csp get_internal_rep(rll_type action) const;
    vector_rllt_sp get_internal_rep(rll_type action);
    //@}

    /// @brief Return number of state signals.
    size_t signals_num() const;

    /// @brief Spawn new state by makeing a deep copy of current one.
    state_with_reserved_action clone() const;

private:
    friend bool operator==(
        const state_with_reserved_action& f
      , const state_with_reserved_action& s
      );

    state_with_reserved_action(const vector_rllt_sp& signals);

private:
    vector_rllt_sp signals_;  //!< Signals
};

inline state_with_reserved_action::state_with_reserved_action()
{
}

inline state_with_reserved_action::state_with_reserved_action(size_t signals_num)
    : signals_(std::make_shared<vector_rllt>(signals_num + 1))
{
}

inline const rll_type& state_with_reserved_action::operator[](size_t idx) const
{
    assert(idx < signals_->size() - 1);
    return signals_->operator[](idx);
}

inline rll_type& state_with_reserved_action::operator[](size_t idx)
{
    assert(idx < signals_->size() - 1);
    return signals_->operator[](idx);
}

/// @brief Return number of state signals
inline size_t state_with_reserved_action::signals_num() const
{
    return signals_->size() - 1;
}

inline vector_rllt_csp state_with_reserved_action::get_internal_rep(rll_type action) const
{
    signals_->back() = action;
    return signals_;
}

inline vector_rllt_sp state_with_reserved_action::get_internal_rep(rll_type action)
{
    signals_->back() = action;
    return signals_;
}

inline state_with_reserved_action state_with_reserved_action::clone() const
{
    vector_rllt_sp signals = std::make_shared<vector_rllt>(*signals_);
    return state_with_reserved_action(signals);
}

inline state_with_reserved_action::state_with_reserved_action(const vector_rllt_sp& signals)
    : signals_(signals)
{
}

inline bool operator==(const state_with_reserved_action& f, const state_with_reserved_action& s)
{
    return std::equal(f.signals_->begin(), f.signals_->end(), s.signals_->begin());
}

}

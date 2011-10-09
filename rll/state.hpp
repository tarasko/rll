#pragma once

#include <rll/rll_fwd.hpp>

#include <algorithm>

namespace rll {

/// @todo Ability to assign state using initializer list

/// @brief Represent agent state.
///
/// Agent state consist of fixed number of signal values. Application is supposed to 
/// define number of signals in state, and give some meaning to this signals. 
/// For example, 3x3 tic-tac-toe game could have 9 state signals each one represent
/// corresponding square on game field. If square is empty then signal will have value 0, 
/// if X - then 1, if O - then 2.
/// State contains a shared pointer to internal representation, so copying of state object 
/// will just increase reference counter. To make deep copy use clone method.
class state 
{
public:
    /// @name Constructors.
    //@{
    /// @brief Construct empty state.
    ///
    /// Some stl construct require types to be DefaultConstructible. The direct use 
    /// of this constructor should be avoided.
    state();

    /// @brief Construct state with specified number of signals
    state(size_t signals_num);

    /// @brief Construct state from internal state representation.
    /// Doesn`t perform deep copy
    state(const vector_rllt_sp& signals);
    //@}

    /// @name State signal accessors.
    //@{
    const rll_type& operator[](size_t idx) const;
    rll_type& operator[](size_t idx);
    //@}

    /// @brief Return number of state signals.
    size_t signals_num() const;
    
    /// @name Serialized representation accessors.
    //@{
    vector_rllt_csp get_internal_rep() const;
    vector_rllt_sp get_internal_rep();
    //@}

    /// @brief Spawn new state by makeing a deep copy of current one.
    state clone() const;

private:
    friend bool operator==(const state& f, const state& s);

private:
    vector_rllt_sp signals_;  //!< Signals
};

inline state::state()
{
}

inline state::state(size_t signals_num)
    : signals_(std::make_shared<vector_rllt>(signals_num))
{
}

inline state::state(const vector_rllt_sp& signals)
    : signals_(signals)
{
}

inline const rll_type& state::operator[](size_t idx) const
{
    return signals_->operator[](idx);
}

inline rll_type& state::operator[](size_t idx)
{
    return signals_->operator[](idx);
}

inline size_t state::signals_num() const
{
    return signals_->size();
}

inline vector_rllt_csp state::get_internal_rep() const
{
    return signals_;
}

inline vector_rllt_sp state::get_internal_rep() 
{
    return signals_;
}

inline state state::clone() const
{
    vector_rllt_sp signals = std::make_shared<vector_rllt>(*signals_);
    return state(signals);
}

inline bool operator==(const state& f, const state& s)
{
    return std::equal(f.signals_->begin(), f.signals_->end(), s.signals_->begin());
}


}

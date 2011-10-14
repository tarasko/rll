#pragma once

#include <rll/value_function/iface.hpp>

#include <array>
#include <type_traits>
#include <unordered_map>

namespace rll { namespace value_function {

namespace detail {

template<int MaxValue>
class static_lt_impl
{
public:
    static_lt_impl(double init)
    {
        values_.fill(init);
    }

    double get_value(size_t idx)
    {
        return values_[idx];
    }

    /// @copybrief iface_tpl::update
    void update(size_t idx, double new_value)
    {
        values_[idx] = new_value;
    }

private:
    std::array<double, MaxValue + 1> values_;
};

class dynamic_lt_impl
{
public:
    dynamic_lt_impl(double init)
        : init_(init)
    {
    }

    double get_value(size_t idx)
    {
        auto i = values_.find(idx);
        return i != values_.end() ? i->second : init_;
    }

    /// @copybrief iface_tpl::update
    void update(size_t idx, double new_value)
    {
        values_[idx] = new_value;
    }

private:
    double init_;
    std::unordered_map<size_t, double> values_;
};

template<int Value1, int Value2>
struct more
{
    static const bool value = Value1 > Value2;
};

}

template<typename HashFunc, size_t MaxValue = 0>
class state_hash_lookup_table
  : public iface
  , public std::conditional<
        detail::more<MaxValue, 0>::value
      , detail::static_lt_impl<MaxValue>
      , detail::dynamic_lt_impl
      >::type
{
    typedef typename std::conditional<
        detail::more<MaxValue, 0>::value
      , detail::static_lt_impl<MaxValue>
      , detail::dynamic_lt_impl
      >::type base_type;

public:
    state_hash_lookup_table(double init = 0.0, HashFunc hash_func = HashFunc())
        : base_type(init)
        , hash_func_(hash_func)
    {
    }

    /// @copybrief iface_tpl::get_value
    virtual double get_value(const state_rep_csp& st)
    {
        return base_type::get_value(hash_func_(st));
    }

    /// @copybrief iface_tpl::update
    virtual void update(const update_list& lst)
    {
        for (auto i = lst.begin(); i != lst.end(); ++i) 
        {
            base_type::update(hash_func_(i->first), i->second);
        }
    }

private:
    HashFunc hash_func_;
};

}}

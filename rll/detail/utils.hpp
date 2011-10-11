#pragma once

#include "../rll_fwd.hpp"

#include <algorithm>

namespace rll { namespace detail {

// Stolen from Boost.Hash
template <class T>
void hash_combine(std::size_t& seed, const T& v)
{
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

template<typename T>
struct eval_vector_t_csp_hash
{
    typedef std::shared_ptr< const std::vector<T> > vector_t_csp;

    size_t operator()(const vector_t_csp& v) const
    {
        size_t seed = 0;
        std::for_each(v->begin(), v->end(), [&seed](T val) 
        {
            hash_combine(seed, val);
        });
        return seed;
    }
};

typedef eval_vector_t_csp_hash<rll_type> eval_vector_rllt_csp_hash;
typedef eval_vector_t_csp_hash<int> eval_vector_int_csp_hash;
typedef eval_vector_t_csp_hash<double> eval_vector_double_csp_hash;

template<typename T>
struct is_equal_vector_t_csp
{
    typedef std::shared_ptr< const std::vector<T> > vector_t_csp;

    bool operator()(const vector_t_csp& f, const vector_t_csp& s) const
    {
        return std::equal(f->begin(), f->end(), s->begin());
    }
};

typedef is_equal_vector_t_csp<rll_type> is_equal_vector_rllt_csp;
typedef is_equal_vector_t_csp<int> is_equal_vector_int_csp;
typedef is_equal_vector_t_csp<double> is_equal_vector_double_csp;

}}

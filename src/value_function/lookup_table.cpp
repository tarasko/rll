#include <rll/value_function/lookup_table.hpp>

#include <algorithm>

using namespace std;

namespace rll { namespace value_function {

double lookup_table::get_value(const vector_rllt_csp& st) 
{
    value_map::iterator i = values_.find(st);
    if (i != values_.end()) 
        return i->second;
    else 
        return init_;
}

void lookup_table::update(const update_list& lst) 
{
    std::for_each(lst.begin(), lst.end(), [&](update_list::const_reference r) -> void 
    {
        values_[r.first] = r.second;
    });
}

}}



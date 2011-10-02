#pragma once

#include <vector>
#include <memory>

#if defined(RLL_DOUBLE)
typedef double rll_type;
#define RLL_TYPE_FOR_PRINTF "%8f"
#elif defined(RLL_INT)
typedef int rll_type;
#define RLL_TYPE_FOR_PRINTF "%d"
#else
#error "Either RLL_INT or RLL_DOUBLE must be defined"
#endif

namespace rll {

typedef std::vector<double> vector_dbl;
typedef std::vector<rll_type> vector_rllt;
typedef std::shared_ptr<vector_rllt> vector_rllt_sp;
typedef std::shared_ptr<const vector_rllt> vector_rllt_csp;

struct config;
class agent;
class state;
class state_with_reserved_action;

class state_environment;
class action_environment;

namespace policy {
class iface;
class greedy;
class egreedy;
}

namespace value_function {
class iface;
class lookup_table;
class neuronal_network;
}

typedef std::shared_ptr<agent> agent_sp;

}

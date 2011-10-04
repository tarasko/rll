#pragma once

/// @mainpage
/// @paragraph abstract (Abstract)
/// RLL is stands for Reinforcement Learning Library. It provides framework for
/// easy creation of reinforcement learning environments and estimating agents
/// value functions according policy.
///
/// @paragraph versions (Library versions)
/// There are two versions of library: rll.int and rll.double. The difference is in
/// type used to represent state signals. Integer state signals allow strict
/// matching between states and thus allow to use lookup table as value function.
/// For double we have to use non strict linear approximators or neuronal networks.
/// You have to define either @b RLL_INT or @b RLL_DOUBLE macro to work with specific
/// version of library.
///
/// @paragraph environment_types (Environment types)
/// The library supports 2 types of environments: rll::state_environment and
/// rll::action_environment. The first is used with agents that estimate state value
/// function. And second - with agent that estimates state-action value function.
/// Library user is supposed to inherit one of this classes and to implement few abstract
/// virtual methods to define exact environment behavior. Each environment type support
/// two convenient typedefs @b state_type and @b method_type. State type is
/// a set of environment signals that represent environment state. Method type is special
/// class that is used to bring the whole system to life, simulate agent actions and update
/// agents value functions.
///
/// @paragraph features (Features)
/// Library features:
/// - Estimates state and state-action value functions.
/// - Integer and double state signals.
/// - Multiple agents in environment.
/// - Policy per agent.
/// - Value function per agent. Agents can use the same value function or different ones.
/// - (on/off)policy value function evaluation. Defined per agent.
/// - Use lambda method with eligibility traces to evaluate agents value functions.
/// - Support episodic and continuing tasks
/// - Implemented using modern C++11, doesn`t depend on any other library.
/// - Easily extensible. Create your own value functions or policies. You need only to implement
/// rll::value_function::iface or rll::policy::iface.
///
/// @paragraph notes (Notes)
/// Important notes:
/// - Library uses some C++11 features, so not all compilers are supported. Currently
/// it supports GCC 4.5.2 or higher and MSVC 10 or higher.
/// - The only supported and well tested value function provided by library is lookup table.
/// The library also provided experimental implementation of value function using
/// neuronal network. It uses @link #http://leenissen.dk/fann/wp/ fann @endlink - well
/// known open source library for building neuronal networks. However there is no real
/// working example with it.
///
/// @paragraph how_to_build (How to build)
/// To build library and examples you need first to generate build system withing cmake.
/// First create directory for build system somewhere in filesystem and cd there.
/// @code
/// mkdir rll_build
/// cd rll_build
/// @endcode
/// Now create build system. You probably may want to create MSVC 10 solution:
/// @code
/// cmake -G "Visual Studio 10" <path to rll>
/// @endcode
/// Or gnu make files:
/// @code
/// cmake -G "Unix Makefiles" <path to rll>
/// @endcode
/// Now open solution and build it or run make for unix makefiles. @n

#include <vector>
#include <memory>

#if defined(RLL_DOUBLE)
typedef double rll_type;
#elif defined(RLL_INT)
typedef int rll_type;
#else
#error "Either RLL_INT or RLL_DOUBLE must be defined"
#endif

#ifdef DOXYGEN
/// @brief Define type of state signal used to represent some state aspect.
///
/// The library come in two versions: with state signal as int and as double.
typedef int_or_double rll_type;
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

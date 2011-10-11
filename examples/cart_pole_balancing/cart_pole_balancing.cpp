#include <rll/rll.hpp>
#include <rll/value_function/state_hash_lookup_table.hpp>

#include <array>

#include <math.h>

using namespace rll;
using namespace std;

// Force that applied to cart on each time step
const double FORCE = 10.0;
// Gravity acceleration g.
const double GRAVITY = 9.8;
// Cart mass
const double MASSCART = 1.0;
// Pole mass
const double MASSPOLE = 0.1;
const double TOTAL_MASS = MASSCART + MASSPOLE;
// actually half the pole's length
const double LENGTH = 0.5;
const double POLEMASS_LENGTH = MASSPOLE * LENGTH;
// seconds between state updates.
const double TAU = 0.02;
const double FOURTHIRDS = 1.3333333333333;

// Distance from center and environment edge.
const double EDGE_POSITION = 2.4;
// Maximal angle in radians before terminal reward and reset.
const double ANGLE_EDGE = 0.2094384;

// State consist of four signals
// Define names for state signals.
enum 
{
    CART_POSITION = 0,         // in meters
    CART_VELOCITY = 1,
    POLE_ANGLE = 2,            // in radians
    POLE_ANGULAR_VELOCITY = 3,
    ACTION = 4
};

static size_t get_box(const value_function::iface::state_rep_csp& st)
{
    size_t box = 0;

    const double one_degree = 0.0174532;	/* 2pi/360 */
    const double six_degrees = 0.1047192;
    const double fifty_degrees = 0.87266;

    const value_function::iface::state_rep& state = *st;

    if (state[CART_POSITION] < -0.8) 
        box = 0;
    else if (state[CART_POSITION] < 0.8) 
        box = 1;
    else
        box = 2;

    if (state[CART_VELOCITY] < -0.5);
    else if (state[CART_VELOCITY] < 0.5)
        box += 3;
    else
        box += 6;

    if (state[POLE_ANGLE] < -six_degrees);
    else if (state[POLE_ANGLE] < -one_degree)
        box += 9;
    else if (state[POLE_ANGLE] < 0)
        box += 18;
    else if (state[POLE_ANGLE] < one_degree)
        box += 27;
    else if (state[POLE_ANGLE] < six_degrees)
        box += 36;
    else
        box += 45;

    if (state[POLE_ANGULAR_VELOCITY] < -fifty_degrees);
    else if (state[POLE_ANGULAR_VELOCITY] < fifty_degrees)
        box += 54;
    else
        box += 108;

    if (state[ACTION] > 0)
        box += 216;

    return box;
}

typedef value_function::state_hash_lookup_table<decltype(&get_box), 432> value_function_type;

class cart_pole_balancing : public action_environment
{
public:
    cart_pole_balancing()
        : state_(4)
        , actions_(2)
        , p_(0.001)
        , vf_(0.0, &get_box)
        , nn_vf_(10)
    {        
        actions_[0] = -FORCE;
        actions_[1] = FORCE;

        agents().push_back(make_shared<agent>(&vf_, &p_, agent::OFFPOLICY));
    }

private:
    virtual void init_episode()
    {
        // Starting state is (0 0 0 0)
        state_[CART_POSITION] = 0;
        state_[CART_VELOCITY] = 0;
        state_[POLE_ANGLE] = 0;
        state_[POLE_ANGULAR_VELOCITY] = 0;
    }

    virtual size_t active_agent() const 
    {
        return 0;
    }

    virtual state_type current_state() const
    {
        return state_;
    }

    virtual std::vector<rll_type> get_possible_actions() const
    {
        return actions_;
    }

    virtual bool do_action_assign_rewards(rll_type force)
    {
        if (step() == 100000) 
        {
            printf("Pole balanced successfully for at least %u steps\n", step());
            return false;
        }

        double costheta = cos(state_[POLE_ANGLE]);
        double sintheta = sin(state_[POLE_ANGLE]);

        double temp = (force + POLEMASS_LENGTH * state_[POLE_ANGULAR_VELOCITY] * state_[POLE_ANGULAR_VELOCITY] * sintheta)
		             / TOTAL_MASS;

        // Evaluate angular pole acceleration
        double thetaacc = (GRAVITY * sintheta - costheta* temp)
	           / (LENGTH * (FOURTHIRDS - MASSPOLE * costheta * costheta
                                                  / TOTAL_MASS));

        // Evaluate linear cart acceleration
        double xacc  = temp - POLEMASS_LENGTH * thetaacc* costheta / TOTAL_MASS;

        // Update the four state variables, using Euler's method.
        state_[CART_POSITION] += TAU * state_[CART_VELOCITY];
        state_[CART_VELOCITY] += TAU * xacc;
        state_[POLE_ANGLE] += TAU * state_[POLE_ANGULAR_VELOCITY];
        state_[POLE_ANGULAR_VELOCITY] += TAU * thetaacc;

        // Assign rewards
        if (state_[CART_POSITION] < -EDGE_POSITION ||
            state_[CART_POSITION] > EDGE_POSITION  ||
            state_[POLE_ANGLE] < -ANGLE_EDGE ||
            state_[POLE_ANGLE] > ANGLE_EDGE) 
        {
            agents()[0]->add_reward(-1.0);
	        printf("Trial %u was %u steps.\n", episode(), step());
            return false;
        }

        return true;
    }

private:    
    vector_rllt actions_;  // Possible actions    
    state_type state_;     // Current state
    policy::egreedy p_;
    policy::greedy pg_;
    value_function_type vf_;
    value_function::neuronal_network nn_vf_;
};

int main(int argc, char* argv[])
{
    config cfg;
    cfg.gamma_ = 0.9;
    cfg.lambda_ = 1.0;
    cfg.alpha_ = 0.1;
    cfg.accumulating_= false;

    cart_pole_balancing cpb;
    simulate(&cpb, cfg, 100000);

    return 0;
}

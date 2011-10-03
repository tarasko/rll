#include <rll/rll.hpp>

#include <vector>
#include <fstream>
#include <iostream>

using namespace rll;
using namespace std;

class tic_tac_toe : public action_environment 
{
    static const int WINING_POSITIONS[8][3];

public:
    tic_tac_toe();

private:
	virtual void init_episode();
    virtual size_t active_agent() const;
    virtual state_type current_state() const;
    virtual vector<rll_type> get_possible_actions() const;
    virtual bool do_action_assign_rewards(rll_type action);

    void print_state(rll_type action) const;

private:
    size_t active_agent_idx_;
    state_type state_;
    value_function::lookup_table vf_;
    policy::egreedy egpolicy_;
    policy::greedy gpolicy_;
};

const int tic_tac_toe::WINING_POSITIONS[8][3] = {
    {0, 1, 2},
    {3, 4, 5},
    {6, 7, 8},
    {0, 3, 6},
    {1, 4, 7},
    {2, 5, 8},
    {0, 4, 8},
    {2, 4, 6}
};

tic_tac_toe::tic_tac_toe()
    : state_(9)
    , vf_()
{
    // Create value function and method
    agent_sp XPlayer = make_shared<agent>(&vf_, &egpolicy_, agent::OFFPOLICY);
    agent_sp OPlayer = make_shared<agent>(&vf_, &gpolicy_, agent::ONPOLICY);
    agents().push_back(XPlayer);
    agents().push_back(OPlayer);
}


void tic_tac_toe::init_episode() 
{
    active_agent_idx_ = 0;
    for (int i=0; i<9; ++i) 
        state_[i] = 0;
}

size_t tic_tac_toe::active_agent() const
{
    return active_agent_idx_;
}

tic_tac_toe::state_type tic_tac_toe::current_state() const
{
    return state_;
}

std::vector<rll_type> tic_tac_toe::get_possible_actions() const
{
    std::vector<rll_type> result;
    result.reserve(9);

    for(int i = 0; i<9; ++i)
    {
        if (state_[i] == 0) 
            result.push_back(i);
    }

    return result;
}

bool tic_tac_toe::do_action_assign_rewards(rll_type action)
{
    print_state(action);
    int my_sign = active_agent_idx_ == 0 ? 1 : 2;

    state_[action] = my_sign;

    bool has_empty_squares = false;

    // Examine game field
    for (int i=0; i<8; ++i) 
    {
        bool are_all_captured = true;

        for (int k=0; k<3; ++k)
        {
            are_all_captured = 
                are_all_captured && 
                state_[WINING_POSITIONS[i][k]] == my_sign;

            has_empty_squares = has_empty_squares || state_[WINING_POSITIONS[k][i]] == 0;
        }

        if (are_all_captured)
        {
            agents()[active_agent_idx_]->add_reward(1.0);
            agents()[active_agent_idx_ ^ 1]->add_reward(-1.0);
            return false;
        }
    }

    // Ok now check for draw
    if (!has_empty_squares) 
        return false;

    // Switch active agent
    active_agent_idx_ ^= 1;

    return true;
}

void tic_tac_toe::print_state(rll_type action) const
{
    if (episode() % 100) 
        return;

    cout << "Episode: " << episode()
        << " Step: " <<  step() 
        << " Value: " 
        << agents()[active_agent_idx_]->vf().get_value(state_.clone().get_internal_rep(action))
        << endl;

    for (int x=0; x<3; ++x) 
    {
        for (int y=0; y<3; ++y) 
        {
            // Fill squares
            int sign = state_[3*x + y];
            if (1 == sign) {
                cout << "X";
            } else if (2 == sign) {
                cout << "O";
            } else if (3*x + y == action) {
                cout << "M";
            } else {
                cout << " ";
            }
            cout << " ";
        }
        cout << endl;
    }
}


int main() 
{
    config cfg;
    cfg.gamma_ = 1.0;
    cfg.accumulating_ = false;

    tic_tac_toe game;
    tic_tac_toe::method_type m(&game, cfg);

    m.run(1000000);
}

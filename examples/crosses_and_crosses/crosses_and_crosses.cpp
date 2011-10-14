#include <rll/rll.hpp>

#include <vector>
#include <fstream>
#include <iostream>

using namespace rll;
using namespace std;

static size_t get_box(const value_function::iface::state_rep_csp& st)
{
    size_t state_hash = 0;
    for (size_t i = 0; i < st->size() - 1; ++i)
    {
        state_hash = state_hash << 1;
        state_hash += (*st)[i];
    }

    size_t result = state_hash + (1 << (st->size() - 1)) * st->back();

    return result;
}

typedef value_function::state_hash_lookup_table<decltype(&get_box), 167772> vf_type;

class game : public action_environment
{
public:
    game(size_t size);

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
    vf_type vf_;
    policy::egreedy egpolicy_;
    policy::greedy gpolicy_;
};

game::game(size_t size)
    : state_(size)
    , vf_(0.0, &get_box)
    , egpolicy_(0.05)
{
    // Create value function and method
    agent_sp XPlayer = make_shared<agent>(&vf_, &gpolicy_, agent::ONPOLICY);
    agent_sp OPlayer = make_shared<agent>(&vf_, &gpolicy_, agent::ONPOLICY);
    agents().push_back(XPlayer);
    agents().push_back(OPlayer);
}


void game::init_episode()
{
    active_agent_idx_ = 0;
    for (size_t i=0; i<state_.signals_num(); ++i)
        state_[i] = 0;
}

size_t game::active_agent() const
{
    return active_agent_idx_;
}

game::state_type game::current_state() const
{
    return state_;
}

std::vector<rll_type> game::get_possible_actions() const
{
    std::vector<rll_type> result;
    result.reserve(state_.signals_num());

    for(size_t i = 0; i<state_.signals_num(); ++i)
    {
        if (state_[i] == 0)
            result.push_back(i);
    }

    return result;
}

bool game::do_action_assign_rewards(rll_type action)
{
    print_state(action);

    state_[action] = 1;

    size_t captured_seq_size = 0;

    // Examine game field
    for (size_t i = 0; i<state_.signals_num() && captured_seq_size < 3; ++i)
    {
        if (state_[i] == 1)
            ++captured_seq_size;
        else
            captured_seq_size = 0;
    }

    if (captured_seq_size == 3)
    {
        agents()[active_agent_idx_]->add_reward(1.0);
        agents()[active_agent_idx_ ^ 1]->add_reward(-1.0);
        return false;
    }

    // Switch active agent
    active_agent_idx_ ^= 1;

    return true;
}

void game::print_state(rll_type action) const
{
    if (episode() % 5000)
        return;

    if (step() == 0)
        cout << "Episode: " << episode() << endl;

    printf("%u - %f\t:", step(), agents()[active_agent_idx_]->vf().get_value(state_.clone().get_internal_rep(action)));

    for (size_t x = 0; x < state_.signals_num(); ++x)
    {
        if (state_[x])
            cout << 'X';
        else if (x == action)
            cout << 'M';
        else
            cout << '_';
    }
    cout << endl;
}


int main(int argc, char* argv[])
{
    config cfg;
    cfg.gamma_ = 0.99;
    cfg.accumulating_ = false;

    size_t field_size = 12;
    if (argc == 2)
        field_size = atoi(argv[1]);

    game game(field_size);
    simulate(&game, cfg, 1000000);
}

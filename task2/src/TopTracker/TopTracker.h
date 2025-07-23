#include <deque>
#include <chrono>

#include "PlayersAction.h"

class TopTracker
{
public:
    TopTracker(std::chrono::seconds timeout, int actions_count);

    void add_action(const int player_id, const Action& action);
    std::deque<PlayerAction> get_actions();

private:
    std::deque<PlayerAction> players_actions;
    std::chrono::seconds timeout;
    int actions_count;


    void cleanup_expired_actions();

};
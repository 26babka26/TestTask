#include "TopTracker.h"

#include <ranges>
#include <algorithm>
#include <functional>

TopTracker::TopTracker(std::chrono::seconds timeout, int actions_count) : timeout(timeout), actions_count(actions_count)
{
}


void TopTracker::add_action(const int player_id, const Action& action)
{
    const auto now = std::chrono::system_clock::now();
    this->players_actions.push_back({ player_id, action, now });

    if (this->players_actions.size() > static_cast<size_t>(this->actions_count))
        this->players_actions.pop_front();
}

std::deque<PlayerAction> TopTracker::get_actions()
{
    this->cleanup_expired_actions();
    return this->players_actions;
}

void TopTracker::cleanup_expired_actions()
{
    const auto now = std::chrono::system_clock::now();
    const auto expired_time = now - this->timeout;

    const auto expired_it = std::ranges::lower_bound(this->players_actions.begin(), this->players_actions.end(), expired_time, std::less{}, &PlayerAction::time);
    this->players_actions.erase(this->players_actions.begin(), expired_it);
}
#include <chrono>

using TimePoint = std::chrono::system_clock::time_point;

enum Action
{
    Run = 0,
    Shoot,
    Jump,
    Last
};

struct PlayerAction
{
    int player_id;
    Action action;
    TimePoint time;
};
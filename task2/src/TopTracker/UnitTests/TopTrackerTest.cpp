#include <thread>
#include <chrono>

#include "TopTracker.h"
#include "gtest/gtest.h"

class TopTrackerTest : public ::testing::Test {
public:
    TopTrackerTest() {
        tracker = std::make_unique<TopTracker>(std::chrono::seconds(5), 3);
    }

    std::unique_ptr<TopTracker> tracker;
};

TEST_F(TopTrackerTest, AddActions) {
    tracker->add_action(1, Action::Jump);
    tracker->add_action(2, Action::Shoot);
    tracker->add_action(3, Action::Run);

    auto actions = tracker->get_actions();
    EXPECT_EQ(actions.size(), 3);

    auto it = actions.begin();
    EXPECT_EQ(it->player_id, 1);
    EXPECT_EQ(it->action, Action::Jump);
    it = std::next(it, 1);
    EXPECT_EQ(it->player_id, 2);
    EXPECT_EQ(it->action, Action::Shoot);
    it = std::next(it, 1);
    EXPECT_EQ(it->player_id, 3);
    EXPECT_EQ(it->action, Action::Run);

}

TEST_F(TopTrackerTest, CountLimit) {
    tracker->add_action(1, Action::Shoot);
    tracker->add_action(2, Action::Jump);
    tracker->add_action(3, Action::Run);
    tracker->add_action(4, Action::Shoot);

    auto actions = tracker->get_actions();
    EXPECT_EQ(actions.size(), 3);
    EXPECT_FALSE(actions.begin()->player_id == 1);
}

TEST_F(TopTrackerTest, ExpiredActions) {
    tracker->add_action(1, Action::Jump);

    std::this_thread::sleep_for(std::chrono::seconds(5));
    tracker->add_action(2, Action::Shoot);

    auto actions = tracker->get_actions();
    EXPECT_EQ(actions.size(), 1);
    EXPECT_EQ(actions.begin()->player_id, 2);
}
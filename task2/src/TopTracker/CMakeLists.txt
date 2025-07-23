add_library(TopTracker STATIC 
    TopTracker.cpp
    TopTracker.h
)

add_library(PlayersAction INTERFACE 
    PlayersAction.h
)

target_link_libraries(TopTracker PUBLIC PlayersAction)

set_compile_options(TopTracker)

include(GoogleTest)
include(CompileOptions)

add_executable(TopTrackerTest UnitTests/TopTrackerTest.cpp)
set_compile_options(TopTrackerTest)
target_link_libraries(TopTrackerTest PRIVATE TopTracker gtest gtest_main)
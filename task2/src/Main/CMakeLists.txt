set(target_name Main)

add_executable(${target_name} main.cpp)

include(CompileOptions)
set_compile_options(${target_name})

target_sources(
  ${target_name}
  PRIVATE
    main.cpp
)

target_link_libraries(
    ${target_name}
  PRIVATE
    TopTracker
)
project(rpg_game)

set(SRC_FILES "src/main.cpp" "src/game.cpp")

set(INCLUDE_FILES "src/game.hpp")

add_executable (rpg_game ${SRC_FILES} ${INCLUDE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE engine)

add_dependencies(${PROJECT_NAME} CopyResources)

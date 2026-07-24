project(rpg_game)

set(SRC_FILES 
	"src/main.cpp" 
	"src/game.cpp"
	"src/scenes/island_scene.cpp"
	"src/scenes/default_scene.cpp"
)

set(INCLUDE_FILES 
	"src/game.hpp" 
	"src/scenes/island_scene.hpp"
	"src/scenes/default_scene.hpp"
)

add_executable (rpg_game ${SRC_FILES} ${INCLUDE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE engine)

add_dependencies(${PROJECT_NAME} CopyResources)

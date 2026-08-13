project(rpg_game)

set(SRC_FILES 
	"src/main.cpp" 
	"src/game.cpp"
	"src/scenes/island_scene.cpp"
	"src/scenes/default_scene.cpp"
)

set(INCLUDE_FILES 
	"src/game.hpp" 
	"src/gconstants.hpp"
	"src/scenes/island_scene.hpp"
	"src/scenes/default_scene.hpp"
	"src/entity/entity_templates.hpp"
)

add_executable (rpg_game ${SRC_FILES} ${INCLUDE_FILES})

target_include_directories(${PROJECT_NAME} 
	PUBLIC 
		src
)


target_link_libraries(${PROJECT_NAME} PRIVATE engine)

add_dependencies(${PROJECT_NAME} CopyResources)

project(rpg_game)

set(SRC_FILES 
	"src/main.cpp" 
	"src/game.cpp"
	"src/scenes/island_scene.cpp"
	"src/scenes/default_scene.cpp"
	"src/entity/systems/movement_system.cpp"
	"src/entity/systems/input_system.cpp"
)

set(INCLUDE_FILES 
	"src/game.hpp" 
	"src/gconstants.hpp"
	"src/scenes/island_scene.hpp"
	"src/scenes/default_scene.hpp"
	"src/entity/components/movement_component.hpp"
	"src/entity/components/input_component.hpp"
	"src/entity/components/direction_component.hpp"
	"src/entity/components/tags.hpp"
	"src/entity/components/components.hpp"
	"src/entity/systems/movement_system.hpp"
	"src/entity/systems/input_system.hpp"
	"src/entity/entities/player_entity.hpp"
	"src/entity/entities/trigger_entity.hpp"
)

add_executable (rpg_game ${SRC_FILES} ${INCLUDE_FILES})

target_include_directories(${PROJECT_NAME} 
	PUBLIC 
		"src"
		"src/entity"
		"src/entity/components"
		"src/entity/systems"
		"src/entity/entities"
)


target_link_libraries(${PROJECT_NAME} PRIVATE engine)

add_dependencies(${PROJECT_NAME} CopyResources)

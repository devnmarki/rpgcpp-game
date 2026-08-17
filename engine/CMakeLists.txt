project(engine)

set(SRC_FILES 
	"src/core/app.cpp"
	"src/core/window.cpp"
	"src/core/scene_manager.cpp"
	"src/core/input.cpp"
	"src/core/scene.cpp"
	"src/utils/time.cpp" 
	"src/graphics/texture.cpp"
	"src/graphics/renderer.cpp"
	"src/graphics/render_system.cpp"
	"src/graphics/sprite_sheet.cpp"
	"src/graphics/animation.cpp"
	"src/graphics/animation_group.cpp"
	"src/graphics/animation_system.cpp"
	"src/loader/animation_storage.cpp"
	"src/ecs/system.cpp" 
	"src/ecs/world.cpp"
)

set(INCLUDE_FILES 
	"src/core/engine.hpp" 
	"src/core/app.hpp"
	"src/core/window.hpp"
	"src/core/scene.hpp"
	"src/core/scene_manager.hpp"
	"src/core/input.hpp"
	"src/core/components/transform_component.hpp"
	"src/utils/utils.hpp"
	"src/graphics/texture.hpp"
	"src/graphics/renderer.hpp"
	"src/graphics/render_system.hpp"
	"src/graphics/sprite.hpp"
	"src/graphics/sprite_sheet.hpp"
	"src/graphics/animation.hpp"
	"src/graphics/animation_group.hpp"
	"src/graphics/animation_system.hpp"
	"src/graphics/components/sprite_renderer_component.hpp"
	"src/graphics/components/animator_component.hpp"
	"src/loader/asset_loader.hpp"
	"src/loader/animation_storage.hpp"
	"src/ecs/world.hpp"
	"src/ecs/entity.hpp"
	"src/ecs/system.hpp"
	"src/ecs/components.hpp"
)

add_library(${PROJECT_NAME} STATIC ${SRC_FILES} ${INCLUDE_FILES})

target_include_directories(${PROJECT_NAME} 
	PUBLIC 
		src
		"third_party/sdl3/include"
		"third_party/sdl3_image/include"
		"third_party/spdlog/include"
		"${CMAKE_SOURCE_DIR}/third_party/glm"
        "${CMAKE_SOURCE_DIR}/third_party/json/single_include"
        "${CMAKE_SOURCE_DIR}/third_party/entt/single_include"
)

target_link_libraries(${PROJECT_NAME} 
	PUBLIC 
		SDL3::SDL3-shared
		SDL3_image::SDL3_image-shared
		spdlog::spdlog
)

add_dependencies(${PROJECT_NAME} CopyResources)
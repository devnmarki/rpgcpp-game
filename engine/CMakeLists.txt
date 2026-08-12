project(engine)

set(SRC_FILES 
	"src/core/engine.cpp" 
	"src/core/app.cpp"
	"src/core/window.cpp"
	"src/core/scene_manager.cpp"
	"src/core/input.cpp"
	"src/utils/time.cpp" 
	"src/graphics/texture.cpp"
	"src/graphics/renderer.cpp"
	"src/loader/asset_loader.cpp"
 "src/core/scene.cpp")

set(INCLUDE_FILES 
	"src/core/engine.hpp" 
	"src/core/app.hpp"
	"src/core/window.hpp"
	"src/core/scene.hpp"
	"src/core/scene_manager.hpp"
	"src/core/input.hpp"
	"src/utils/utils.hpp"
	"src/graphics/texture.hpp"
	"src/graphics/renderer.hpp"
	"src/loader/asset_loader.hpp"
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
)

target_link_libraries(${PROJECT_NAME} 
	PUBLIC 
		SDL3::SDL3-shared
		SDL3_image::SDL3_image-shared
		spdlog::spdlog
)

add_dependencies(${PROJECT_NAME} CopyResources)
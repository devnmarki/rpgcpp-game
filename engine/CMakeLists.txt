project(engine)

set(SRC_FILES 
	"src/core/engine.cpp" 
	"src/core/app.cpp"
	"src/core/window.cpp"
 "src/utils/time.cpp")

set(INCLUDE_FILES 
	"src/core/engine.hpp" 
	"src/core/app.hpp"
	"src/core/window.hpp"
	"src/utils/utils.hpp"
)

add_library(${PROJECT_NAME} STATIC ${SRC_FILES} ${INCLUDE_FILES})

target_include_directories(${PROJECT_NAME} 
	PUBLIC 
		src
		"third_party/sdl3/include"
		"third_party/sdl3_image/include"
#		"${CMAKE_SOURCE_DIR}/third_party/glm"
#       "${CMAKE_SOURCE_DIR}/third_party/json/single_include"
)

target_link_libraries(${PROJECT_NAME} 
	PUBLIC 
		SDL3::SDL3-shared
		SDL3_image::SDL3_image-shared
)

add_dependencies(${PROJECT_NAME} CopyResources)
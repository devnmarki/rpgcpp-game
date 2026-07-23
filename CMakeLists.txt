cmake_minimum_required (VERSION 3.10)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(GLOBAL_RES_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/res")
set(GLOBAL_RES_DEST   "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res")

file(MAKE_DIRECTORY "${GLOBAL_RES_DEST}")

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (rpg_game)

add_subdirectory(third_party/sdl3)

add_subdirectory (rpg_game)
add_subdirectory (engine)

add_custom_target(CopyResources
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${GLOBAL_RES_SOURCE}"
        "${GLOBAL_RES_DEST}"
    COMMENT "Syncing global resources to build directory..."
)

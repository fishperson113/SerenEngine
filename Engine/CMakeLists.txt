project(SerenEngine VERSION 0.1)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/SerenEngine/*.cpp CMAKE_CONFIGURE_DEPENDS)
add_library(${PROJECT_NAME} STATIC ${SRC_FILES})

target_compile_definitions(${PROJECT_NAME} PUBLIC DYNAMIC_LIB=0 DYNAMIC_BUILD=0)

# Include directories
target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/SerenEngine
    ${CMAKE_SOURCE_DIR}/Vendors/include
    ${CMAKE_SOURCE_DIR}/Vendors/glfw/include
    ${CMAKE_SOURCE_DIR}/Vendors/glm
    ${CMAKE_SOURCE_DIR}/Vendors/imgui
    ${CMAKE_SOURCE_DIR}/Vendors/stb_image
)

# Link directories
target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Vendors/bin)

# Link libraries
if (EMSCRIPTEN)
    message(STATUS "Building for WebAssembly")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_PTHREADS=0")
    target_link_libraries(${PROJECT_NAME} PUBLIC spdlog glfw glm imgui stb_image box2d)
else()
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_link_libraries(${PROJECT_NAME} PUBLIC spdlogd glfw glm imgui stb_image box2d) # Link bản Debug
    else()
        target_link_libraries(${PROJECT_NAME} PUBLIC spdlog glfw glm imgui stb_image box2d)  # Link bản Release
    endif()
endif()

# Precompiled headers
target_precompile_headers(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/SerenEngine/pch.h 
    ${CMAKE_SOURCE_DIR}/Vendors/include/glad/gl.h)
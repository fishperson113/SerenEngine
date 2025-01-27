project(SerenEngine VERSION 0.1)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/SerenEngine/*.cpp CMAKE_CONFIGURE_DEPENDS)
add_library(${PROJECT_NAME} STATIC ${SRC_FILES} "SerenEngine/pch.h" "SerenEngine/Core/Logger/Logger.h" "SerenEngine/Core/Logger/Logger.cpp" "SerenEngine/Window/Window.h" "SerenEngine/Window/GLFWPlatformWindow.cpp" "SerenEngine/Window/WindowPlatform.h" "SerenEngine/Window/WindowPlatform.cpp" "SerenEngine/Core/Event/EventContext.h" "SerenEngine/Core/Event/EventAction.h" "SerenEngine/Core/Event/EventDispatcher.h" "SerenEngine/Core/Event/EventDispatcher.cpp" "SerenEngine/Core/Input/Keycode.h")

target_compile_definitions(${PROJECT_NAME} PUBLIC DYNAMIC_LIB=0 DYNAMIC_BUILD=0)

target_include_directories(${PROJECT_NAME} PUBLIC 
		${CMAKE_CURRENT_SOURCE_DIR}/SerenEngine
		${CMAKE_SOURCE_DIR}/Vendors/include
		${CMAKE_SOURCE_DIR}/Vendors/glfw/include
)

target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Vendors/bin)
target_link_libraries(${PROJECT_NAME} PUBLIC spdlogd glfw)

target_precompile_headers(${PROJECT_NAME} PUBLIC 
		${CMAKE_CURRENT_SOURCE_DIR}/SerenEngine/pch.h 
		${CMAKE_SOURCE_DIR}/Vendors/include/glad/gl.h)
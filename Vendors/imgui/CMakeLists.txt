project(imgui VERSION 0.0.1)

file(GLOB_RECURSE SRC_FILES Source/*.cpp CMAKE_CONFIGURE_DEPENDS)
add_library(${PROJECT_NAME} STATIC ${SRC_FILES})

# Link glfw đúng phiên bản Debug/Release
if (WIN32)
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(${PROJECT_NAME} glfw3d) # Link bản Debug
  else()
    target_link_libraries(${PROJECT_NAME} glfw3)  # Link bản Release
  endif()

  target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Vendors/glfw/include)
  target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Vendors/libs)
endif (WIN32)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)

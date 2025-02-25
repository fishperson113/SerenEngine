# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("SerenEngine")

if (EMSCRIPTEN)
    # Bỏ qua việc build các file không tương thích với Emscripten
    set(IGNORE_FILES
        ${CMAKE_SOURCE_DIR}/Vendors/glfw/src/posix_time.c
        ${CMAKE_SOURCE_DIR}/Vendors/glfw/src/posix_module.c
        ${CMAKE_SOURCE_DIR}/Vendors/glfw/src/posix_thread.c
    )
endif()

# Gỡ bỏ những file không cần thiết khi build với Emscripten
if (EMSCRIPTEN)
    list(REMOVE_ITEM SRC_FILES ${IGNORE_FILES})
endif()


# Add UTF-8 flag for MSVC
if (MSVC)
  add_compile_options(/utf-8)
endif()

add_subdirectory(Engine)
add_subdirectory(Game)
add_subdirectory(Vendors/glfw)
add_subdirectory(Vendors/glm)
add_subdirectory(Vendors/imgui)
add_subdirectory(Vendors/stb_image)
add_subdirectory(Vendors/box2d)
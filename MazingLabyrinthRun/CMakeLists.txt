cmake_minimum_required(VERSION 3.15)
project(MazingLabyrinthRun
  LANGUAGES CXX
  VERSION 1.0
)

add_subdirectory(dependencies)

add_executable(MazingLabyrinthRun code/include/main.h code/src/main.cpp)
target_link_libraries(MazingLabyrinthRun PRIVATE ImGui-SFML::ImGui-SFML)

# Copy DLLs needed for runtime on Windows
if(WIN32)
  if (BUILD_SHARED_LIBS)
    add_custom_command(TARGET MazingLabyrinthRun POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
          $<TARGET_FILE:ImGui-SFML::ImGui-SFML>
          $<TARGET_FILE:sfml-graphics>
          $<TARGET_FILE:sfml-window>
          $<TARGET_FILE:sfml-system>
          $<TARGET_FILE_DIR:MazingLabyrinthRun>)
  endif()
endif()


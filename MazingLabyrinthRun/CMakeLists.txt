cmake_minimum_required(VERSION 3.15)
project(MazingLabyrinthRun
  LANGUAGES CXX
  VERSION 1.0
)

add_subdirectory(dependencies)

add_library(MazingLabyrinthRunLib 
				STATIC 
				code/include/mazingLabyrinthRun.h
                code/include/game.h 
                code/include/tile/iTile.h
				code/include/tile/wall.h
				code/include/tile/path.h
                code/include/tile/tileEnum.h
                code/include/tile/tileFactory.h
				code/src/mazingLabyrinthRun.cpp
                code/src/game.cpp
                code/src/tile/wall.cpp
				code/src/tile/path.cpp
                code/src/tile/tileFactory.cpp)

target_include_directories(MazingLabyrinthRunLib PRIVATE code/src PUBLIC code/include)
target_link_libraries(MazingLabyrinthRunLib PRIVATE ImGui-SFML::ImGui-SFML)

add_executable(MazingLabyrinthRun code/src/main.cpp)
target_link_libraries(MazingLabyrinthRun PUBLIC MazingLabyrinthRunLib)

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

add_subdirectory(code/test)

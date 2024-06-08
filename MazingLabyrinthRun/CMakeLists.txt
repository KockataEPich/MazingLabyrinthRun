option(CPP_BUILD "CPP_BUILD" ON)
option(CODE_GENERATION "CODE_GENERATION" ON)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /STACK:1000000000")

if(CODE_GENERATION)
  execute_process (
      COMMAND python code_generation/generate.py 2> nul RESULT_VARIABLE ret
  )

  if(NOT ret EQUAL "0")
    message( FATAL_ERROR "-- CODE GENERATION FAILED")
  endif()
else()
  message("-- No Code Generation")
endif()

if(NOT CPP_BUILD)
  message("-- No Full Build")
  return()
endif()

cmake_minimum_required(VERSION 3.15)
project(MazingLabyrinthRun
  LANGUAGES CXX
  VERSION 1.0
)

set(CMAKE_CXX_STANDARD 23) 
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

add_subdirectory(dependencies)

set(_src_root_path "${CMAKE_CURRENT_SOURCE_DIR}/code")

file(
    GLOB_RECURSE _source_list 
    LIST_DIRECTORIES false
    "${_src_root_path}/src/*.c*"
    "${_src_root_path}/include/*.h*"
)

add_library(MazingLabyrinthRunLib 
				STATIC 
				${_source_list})
				
target_include_directories(MazingLabyrinthRunLib PRIVATE code/src PUBLIC code/include PUBLIC build/_deps/sfml-src/include build/_deps/magic_enum-src/include)

foreach(_source IN ITEMS ${_source_list})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${_src_root_path}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()	


target_link_libraries(MazingLabyrinthRunLib PRIVATE ImGui-SFML::ImGui-SFML magic_enum)

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

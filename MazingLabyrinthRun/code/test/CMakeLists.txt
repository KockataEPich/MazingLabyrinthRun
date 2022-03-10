add_executable(MazinglabyrinthRunTest test.cpp)
target_link_libraries(MazinglabyrinthRunTest PRIVATE MazingLabyrinthRunLib 
											 PRIVATE Catch2::Catch2WithMain
											 PRIVATE ImGui-SFML::ImGui-SFML)
											 
# Copy DLLs needed for runtime on Windows
if(WIN32)
  if (BUILD_SHARED_LIBS)
    add_custom_command(TARGET MazinglabyrinthRunTest POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
          $<TARGET_FILE:ImGui-SFML::ImGui-SFML>
          $<TARGET_FILE:sfml-graphics>
          $<TARGET_FILE:sfml-window>
          $<TARGET_FILE:sfml-system>
          $<TARGET_FILE_DIR:MazinglabyrinthRunTest>)
  endif()
endif()
include(FetchContent)

FetchContent_Declare(
  sfml
  GIT_REPOSITORY "https://github.com/SFML/SFML"
  GIT_TAG 69ea0cd863aed1d4092b970b676924a716ff718b # 2.6.1
)

add_subdirectory(sfml)

FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui
  GIT_TAG 35b1148efb839381b84de9290d9caf0b66ad7d03
)

FetchContent_MakeAvailable(imgui)

FetchContent_Declare(
  imgui-sfml
  GIT_REPOSITORY https://github.com/eliasdaler/imgui-sfml
  GIT_TAG 82dc2033e51b8323857c3ae1cf1f458b3a933c35
)
add_subdirectory(imgui-sfml)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.0-preview3
)

add_subdirectory(catch2)

FetchContent_Declare(
  magic_enum
  GIT_REPOSITORY https://github.com/Neargye/magic_enum.git
  GIT_TAG        v0.7.3
)

add_subdirectory(magic_enum)
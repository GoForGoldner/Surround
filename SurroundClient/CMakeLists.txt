cmake_minimum_required(VERSION 3.5)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)

# Fetch SFML
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Fetch ENet
FetchContent_Declare(ENet
    GIT_REPOSITORY https://github.com/lsalzman/enet.git
    GIT_TAG master
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(ENet)

# Main application
add_executable(main 
    src/headers/model.h
    src/headers/view.h
    src/headers/menu.h
    
    src/headers/viewWindow.h
    src/headers/waitingRoom.h
    src/headers/game.h
    src/headers/controller.h
    src/headers/player.h
    src/headers/playerInfo.h
    src/headers/text.h
    src/sources/main.cpp
    src/sources/model.cpp
    src/sources/view.cpp
    src/sources/menu.cpp
    src/sources/waitingRoom.cpp
    src/sources/game.cpp
    src/sources/controller.cpp
    src/sources/player.cpp
    src/sources/playerInfo.cpp
    src/sources/text.cpp
)

file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})

# Add the `src/headers` directory to the include path
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/src/headers)
target_include_directories(main PRIVATE ${enet_SOURCE_DIR}/include)
target_include_directories(main PRIVATE ${enet_SOURCE_DIR}/source)

target_link_libraries(main PRIVATE sfml-graphics enet)
target_compile_features(main PRIVATE cxx_std_17)

# Enable testing
enable_testing()

# Add the tests directory
add_subdirectory(src/tests)

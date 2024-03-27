cmake_minimum_required(VERSION 3.25)
project(ProjektSemestrGra)
set(CMAKE_CXX_STANDARD 20)
include(FetchContent)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG 10.1.1
)
FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.0
)
FetchContent_MakeAvailable(fmt)
FetchContent_MakeAvailable(sfml)
add_executable(ProjektSemestrGra main.cpp
        Postac.cpp
        Blok.cpp
        Bullet.cpp
        Przeciwnik.cpp
        Teksty.cpp
        Hp.cpp
        LaserZOczu.cpp
        Kolce.cpp
)
target_link_libraries(
        ProjektSemestrGra
        fmt
        sfml-graphics
        sfml-window
        sfml-system
)
IF (WIN32)
    add_custom_command(TARGET ProjektSemestrGra POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:ProjektSemestrGra> $<TARGET_FILE_DIR:ProjektSemestrGra>
            COMMAND_EXPAND_LISTS
    )
ENDIF ()

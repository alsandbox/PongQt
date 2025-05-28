cmake_minimum_required(VERSION 3.31)
project(Pong)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Pong main.cpp
        Renderer.cpp
        Renderer.h
        ScoreRenderer.cpp
        ScoreRenderer.h
        PlayerRenderer.cpp
        PlayerRenderer.h
        BallRenderer.cpp
        BallRenderer.h
        PlayerItem.cpp
        PlayerItem.h
        BallMovement.cpp
        BallMovement.h
        IBoundable.cpp
        IBoundable.h
        LineRenderer.cpp
        LineRenderer.h
        ScoreManager.cpp
        ScoreManager.h)
target_link_libraries(Pong
        Qt::Core
        Qt::Gui
        Qt::Widgets
)


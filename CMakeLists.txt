cmake_minimum_required(VERSION 3.31)
project(Pong)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Pong main.cpp
        renderers/Renderer.cpp
        renderers/Renderer.h
        renderers/ScoreRenderer.cpp
        renderers/ScoreRenderer.h
        renderers/PlayerRenderer.cpp
        renderers/PlayerRenderer.h
        renderers/BallRenderer.cpp
        renderers/BallRenderer.h
        PlayerItem.cpp
        PlayerItem.h
        BallMovement.cpp
        BallMovement.h
        IBoundable.cpp
        IBoundable.h
        renderers/LineRenderer.cpp
        renderers/LineRenderer.h
        managers/ScoreManager.cpp
        managers/ScoreManager.h
        managers/GameManager.cpp
        managers/GameManager.h
        renderers/RendererFactory.cpp
        renderers/RendererFactory.h
        screens/GameOverScreen.cpp
        screens/GameOverScreen.h
        fonts/FontConfig.cpp
        fonts/FontConfig.h
        screens/ScreenBase.cpp
        screens/ScreenBase.h
        screens/GameStartScreen.cpp
        screens/GameStartScreen.h
)
target_link_libraries(Pong
        Qt::Core
        Qt::Gui
        Qt::Widgets
)


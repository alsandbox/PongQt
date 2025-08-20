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

qt_add_resources(RESOURCES
        icon/icon.qrc
        font/font.qrc
        style/style.qrc)

add_executable(Pong main.cpp
        ${RESOURCES}
        renderers/Renderer.cpp
        renderers/Renderer.h
        renderers/ScoreRenderer.cpp
        renderers/ScoreRenderer.h
        renderers/PlayerRenderer.cpp
        renderers/PlayerRenderer.h
        renderers/BallRenderer.cpp
        renderers/BallRenderer.h
        gameplay/PlayerItem.cpp
        gameplay/PlayerItem.h
        gameplay/BallMovement.cpp
        gameplay/BallMovement.h
        renderers/IBoundable.cpp
        renderers/IBoundable.h
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
        font/FontConfig.cpp
        font/FontConfig.h
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

add_custom_command(TARGET Pong POST_BUILD
        COMMAND "C:/Qt/6.9.1/mingw_64/bin/windeployqt.exe"
        "$<TARGET_FILE:Pong>"
)

set_target_properties(Pong PROPERTIES WIN32_EXECUTABLE TRUE)

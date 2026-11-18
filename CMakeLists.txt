cmake_minimum_required(VERSION 3.30)
project(untitled)

set(CMAKE_CXX_STANDARD 26)

add_executable(untitled main.cpp
        Enemy.cpp
        Engine/LightSource.cpp
        Engine/Component.cpp
        Engine/ImageFile.cpp
        PlayerStats.cpp
        Engine/SpriteSheet.cpp
        Engine/HeightMap.cpp
        Engine/Animator.cpp
        Engine/AnimationFrame.cpp
        Game.cpp
        PlayerAttack.cpp
        Engine/Window.cpp
        PlayerMovement.cpp
        Engine/Input.cpp
        Engine/Pixel.cpp
        Engine/Animation.cpp
        Engine/Vector.cpp
        Player.cpp
        Engine/Collider.cpp
        Engine/GameObject.cpp
        Engine/ImageRenderer.cpp
        Engine/Scene.cpp
        Engine/Screen.cpp
        LoadingZone.cpp)

install(TARGETS untitled DESTINATION bin)


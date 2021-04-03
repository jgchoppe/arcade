cmake_minimum_required(VERSION 3.15)
project(Space_arcade)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/Clock)
include_directories(src/Core)
include_directories(src/Games/Snake)
include_directories(src/Lib/Drawable)
include_directories(src/Lib/Drawable/Circle)
include_directories(src/Lib/Drawable/Color)
include_directories(src/Lib/Drawable/Position)
include_directories(src/Lib/Drawable/Rectangle)
include_directories(src/Lib/Drawable/Size)
include_directories(src/Lib/Drawable/Sprite)
include_directories(src/Lib/Drawable/Text)
include_directories(src/Lib/Drawable/Vector)
include_directories(src/Lib/Game)
include_directories(src/Lib/Graphic)
include_directories(src/Lib/Graphic/Libcaca)
include_directories(src/Lib/Graphic/SDL)
include_directories(src/Lib/Graphic/SFML)
include_directories(src/Loader)
include_directories(src/Menu)
include_directories(src/Utils)

add_executable(Space_arcade
        src/Clock/Clock.cpp
        src/Clock/Clock.hpp
        src/Core/Core.cpp
        src/Core/Core.hpp
        src/Games/SolarFox/SolarFox.cpp
        src/Games/SolarFox/SolarFox.hpp
        src/Games/Snake/Snake.cpp
        src/Games/Snake/Snake.hpp
        src/Games/SaveManager.cpp
        src/Games/SaveManager.hpp
        src/Lib/Drawable/Circle/Circle.hpp
        src/Lib/Drawable/Color/Color.hpp
        src/Lib/Drawable/Position/Position.hpp
        src/Lib/Drawable/Rectangle/Rect.hpp
        src/Lib/Drawable/Size/Size.hpp
        src/Lib/Drawable/Sprite/Sprite.hpp
        src/Lib/Drawable/Text/Text.hpp
        src/Lib/Drawable/Vector/Vector2f.hpp
        src/Lib/Game/IGame.cpp
        src/Lib/Game/IGame.hpp
        src/Lib/Graphic/IGraphic.hpp
        src/Loader/SoLoader.cpp
        src/Loader/SoLoader.hpp
        src/Menu/Menu.cpp
        src/Menu/Menu.hpp
        src/Lib/Graphic/SDL/SDL.cpp
        src/Lib/Graphic/SDL/SDL.hpp
        src/Lib/Graphic/Libcaca/Libcaca.cpp
        src/Lib/Graphic/Libcaca/Libcaca.hpp
        src/Lib/Graphic/SFML/SFML.cpp
        src/Lib/Graphic/SFML/SFML.hpp
        src/Utils/OpenFolder.hpp
        src/Utils/RingBufferString.cpp
        src/Utils/RingBufferString.hpp
        src/Utils/Using.hpp
        src/Main.cpp)

target_link_libraries(Space_arcade pthread sfml-audio sfml-system sfml-graphics sfml-window ldl)
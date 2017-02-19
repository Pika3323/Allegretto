cmake_minimum_required(VERSION 3.6)
project(life)

set(CMAKE_CXX_STANDARD 14)

INCLUDE_DIRECTORIES(libs/allegro/include)
LINK_DIRECTORIES(libs/allegro/lib)

set(SOURCE_FILES main.cpp Engine/Engine.cpp Engine/Engine.h Engine/Core.h Engine/Screen.h LifeScreen.cpp LifeScreen.h Engine/InputController.cpp Engine/InputController.h Engine/GameObject.h Engine/DebugOutput.h Engine/UILayer.cpp Engine/UILayer.h Engine/Colour.cpp Engine/Colour.h Engine/UIComponent.cpp Engine/UIComponent.h)
add_executable(life ${SOURCE_FILES})

file(GLOB LIBRARIES "libs/allegro/lib/liballegro_main-debug.dll.a" "libs/allegro/lib/liballegro_monolith-debug.dll.a" "libs/allegro/lib/liballegro.dll.a")
message("LIBRARIES = ${LIBRARIES}")

TARGET_LINK_LIBRARIES(life ${LIBRARIES})
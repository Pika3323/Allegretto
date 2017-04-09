cmake_minimum_required(VERSION 3.6)
project(rpn)

set(CMAKE_CXX_STANDARD 14)

INCLUDE_DIRECTORIES(libs/allegro/include)
LINK_DIRECTORIES(libs/allegro/lib)

set(SOURCE_FILES main.cpp Engine/Engine.cpp Engine/Engine.h Engine/Core.h Engine/Delegate.h Engine/Screen.h LifeScreen.cpp LifeScreen.h Engine/InputController.cpp Engine/InputController.h Engine/GameObject.h Engine/DebugOutput.h Engine/Colour.cpp Engine/Colour.h Engine/Vector2D.h Engine/Bound2D.h RpnScreen.cpp RpnScreen.h Stack.h RpnStack.cpp RpnStack.h Engine/View.cpp Engine/View.h Engine/Views/TextView.cpp Engine/Views/TextView.h Engine/Screen.cpp Engine/Font.cpp Engine/Font.h)
add_executable(rpn ${SOURCE_FILES})

file(GLOB LIBRARIES "libs/allegro/lib/liballegro_main-debug.dll.a" "libs/allegro/lib/liballegro_monolith-debug.dll.a" "libs/allegro/lib/liballegro.dll.a")
message("LIBRARIES = ${LIBRARIES}")

TARGET_LINK_LIBRARIES(rpn ${LIBRARIES})
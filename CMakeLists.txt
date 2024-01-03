cmake_minimum_required(VERSION 3.2)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(ps-vita-sdl-hello-world)
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(SDL2_DIR ${VITASDK}/arm-vita-eabi/lib/cmake/SDL2/)
find_package(SDL2 REQUIRED)

set(VITA_APP_NAME "SDL2 Hello World")
set(VITA_TITLEID  "VSDK00017")
set(VITA_VERSION  "01.00")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

include_directories(
  ../common
)

add_executable(${PROJECT_NAME}
  src/main.cpp
)

target_link_libraries(${PROJECT_NAME}
  SDL2
  SDL2_image
  png
  png16
  jpeg
  z
  SceGxm_stub
  SceCtrl_stub
  SceAudio_stub
  SceMotion_stub
  SceCommonDialog_stub
  SceIme_stub
  SceHid_stub
  SceTouch_stub
  SceDisplay_stub
  SceAudio_stub
  SceAudioIn_stub
)

vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME})
vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
  FILE sce_sys/icon0.png sce_sys/icon0.png
  FILE sce_sys/livearea/contents/bg.png sce_sys/livearea/contents/bg.png
  FILE sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
  FILE sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml
  FILE sprites/sprite.png sprites/sprite.png
)

add_custom_command(
    OUTPUT run_vita3k
    COMMAND ./Vita3K-x86_64.AppImage ./ps-vita-sdl-hello-world.vpk
    DEPENDS ps-vita-sdl-hello-world
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running Vita3K with ps-vita-sdl-hello-world.vpk"
    USES_TERMINAL
)

# Custom target that depends on the above custom command
add_custom_target(run
    DEPENDS run_vita3k
)

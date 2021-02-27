cmake_minimum_required(VERSION 3.17)
project(evdev_actions)

set(CMAKE_C_STANDARD 11)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake-modules")

add_executable(evdev_actions main.c)

find_package(Libinput REQUIRED)
if (NOT ${Libinput_FOUND})
	message(FATAL_ERROR "libinput not found")
endif ()
target_include_directories(evdev_actions PUBLIC ${Libinput_INCLUDE_DIRS})
target_link_libraries(evdev_actions ${Libinput_LIBRARIES})

find_package(udev REQUIRED)
if (NOT ${UDEV_FOUND})
	message(FATAL_ERROR "libudev not found")
endif ()
target_include_directories(evdev_actions PUBLIC ${UDEV_INCLUDE_DIRS})
target_link_libraries(evdev_actions ${UDEV_LIBRARIES})

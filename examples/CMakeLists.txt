CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(examples C)

INCLUDE_DIRECTORIES(../src ${CMAKE_CURRENT_BINARY_DIR}/../src) # second one is for generated config.h


ADD_EXECUTABLE(search ssd1306.c)
TARGET_LINK_LIBRARIES(search sdsp)

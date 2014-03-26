CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(examples C)

INCLUDE_DIRECTORIES(../src ${CMAKE_CURRENT_BINARY_DIR}/../src) # second one is for generated config.h


ADD_EXECUTABLE(ssd1306_test ssd1306_test.c)
TARGET_LINK_LIBRARIES(ssd1306_test sdsp)

ADD_EXECUTABLE(crius_test crius_test.c)
TARGET_LINK_LIBRARIES(crius_test sdsp)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(examples C)

INCLUDE_DIRECTORIES(../src ${CMAKE_CURRENT_BINARY_DIR}/../src) # second one is for generated config.h
INCLUDE(../devices.cmake)


IF (WITH_DISPLAY_CRIUS)
	ADD_EXECUTABLE(crius_test crius_test.c)
	TARGET_LINK_LIBRARIES(crius_test sdisp)
	
	ADD_EXECUTABLE(crius_clear crius_clear.c)
	TARGET_LINK_LIBRARIES(crius_clear sdisp)
	
	ADD_EXECUTABLE(crius_detect crius_detect.c)
	TARGET_LINK_LIBRARIES(crius_detect sdisp)
	
	ADD_EXECUTABLE(crius_buffer_test crius_buffer_test.c)
	TARGET_LINK_LIBRARIES(crius_buffer_test sdisp)
ENDIF()

IF (WITH_DISPLAY_SSD1306)
	ADD_EXECUTABLE(ssd1306_test ssd1306_test.c)
	TARGET_LINK_LIBRARIES(ssd1306_test sdisp)
ENDIF()

IF (WITH_DISPLAY_SSD1327)
	ADD_EXECUTABLE(ssd1327_test ssd1327_test.c)
	TARGET_LINK_LIBRARIES(ssd1327_test sdisp)
ENDIF()
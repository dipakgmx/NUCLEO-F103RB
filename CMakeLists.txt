project(STM32)

set(MCU_FAMILY STM32F1xx)
set(MCU_LINE STM32F103xB)
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/Linker/STM32F103RBTx_FLASH.ld)
SET(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.15)

add_definitions(-D${MCU_LINE})
add_definitions(-DUSE_FULL_ASSERT)
add_definitions(-D__weak=__attribute__\(\(weak\)\) -D__packed=__attribute__\(\(__packed__\)\))
#add_definitions(-DUSE_HAL_LIBRARY)


file(GLOB_RECURSE CMSIS_SYSTEM  Libraries/CMSIS/Device/ST/STM32F10x/src/system_stm32f1xx.c)
file(GLOB_RECURSE CMSIS_STARTUP Startup/startup_stm32f103xb.s)
#file(GLOB_RECURSE HAL_SOURCES Libraries/STM32F1xx_HAL_Driver/Application/*.c)

include_directories(Libraries/CMSIS/Device/ST/STM32F10x/Include)
include_directories(Libraries/CMSIS/Include)

#set(STM32F10x_INCLUDES  ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/CMSIS/Device/ST/STM32F10x/Include)
#set(CMSIS_INCLUDES      ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/CMSIS/Include)
#set(STM32F10x_INCLUDES  ${STM32F10x_INCLUDES}   PARENT_SCOPE)
#set(CMSIS_INCLUDES      ${CMSIS_INCLUDES}       PARENT_SCOPE)
#include_directories(${STM32F10x_INCLUDES})
#include_directories(${CMSIS_INCLUDES})

add_subdirectory(Application/Exercise_4_1)
add_subdirectory(Application/Exercise_4_3)
add_subdirectory(Application/Exercise_5_3)
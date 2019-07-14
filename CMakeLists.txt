set(PRJ_NAME Exercise_4_3)
set(MCU_FAMILY STM32F1xx)
set(MCU_LINE STM32F103xB)
set(MCU_LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/Linker/STM32F103RBTx_FLASH.ld)
SET(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.7)

project(${PRJ_NAME} C CXX ASM)

add_definitions(-D${MCU_LINE})
add_definitions(-DUSE_FULL_ASSERT)
add_definitions(-D__weak=__attribute__\(\(weak\)\) -D__packed=__attribute__\(\(__packed__\)\))
#add_definitions(-DUSE_HAL_LIBRARY)


file(GLOB_RECURSE USER_SOURCES "src/*.cpp")
file(GLOB_RECURSE CMSIS_SYSTEM  Libraries/CMSIS/Device/ST/STM32F10x/src/system_stm32f1xx.c)
file(GLOB_RECURSE CMSIS_STARTUP Startup/startup_stm32f103xb.s)
#file(GLOB_RECURSE HAL_SOURCES Libraries/STM32F1xx_HAL_Driver/src/*.c)

set(SOURCE_FILES ${USER_SOURCES} ${CMSIS_SYSTEM} ${CMSIS_STARTUP} ${MCU_LINKER_SCRIPT})

include_directories(Libraries/CMSIS/Device/ST/STM32F10x/Include)
include_directories(Libraries/CMSIS/Include)
#include_directories(Libraries/STM32F1xx_HAL_Driver/inc)

add_executable(${PROJECT_NAME}.elf ${SOURCE_FILES} ${MCU_LINKER_SCRIPT})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map")
set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE} Building ${BIN_FILE}")

add_custom_target(UPLOAD
        arm-none-eabi-gdb -iex "target remote tcp:127.0.0.1:3333"
        -iex "monitor program $<TARGET_FILE:${PROJECT_NAME}.elf>"
        -iex "monitor reset init"
        -iex "disconnect" -iex "quit")
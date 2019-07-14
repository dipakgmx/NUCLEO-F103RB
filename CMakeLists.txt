set(PRJ_NAME NUCLEO-F103RB)
set(MCU_FAMILY STM32F1xx)
set(MCU_LINE STM32F103xB)
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/Linker/STM32F103RBTx_FLASH.ld)
SET(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.7)


add_definitions(-D${MCU_LINE})
add_definitions(-DUSE_FULL_ASSERT)
add_definitions(-D__weak=__attribute__\(\(weak\)\) -D__packed=__attribute__\(\(__packed__\)\))
#add_definitions(-DUSE_HAL_LIBRARY)


file(GLOB_RECURSE CMSIS_SYSTEM  Libraries/CMSIS/Device/ST/STM32F10x/src/system_stm32f1xx.c)
file(GLOB_RECURSE CMSIS_STARTUP Startup/startup_stm32f103xb.s)
#file(GLOB_RECURSE HAL_SOURCES Libraries/STM32F1xx_HAL_Driver/src/*.c)

include_directories(Libraries/CMSIS/Device/ST/STM32F10x/Include)
include_directories(Libraries/CMSIS/Include)
#include_directories(Libraries/STM32F1xx_HAL_Driver/inc)

#Search for source files within "src" folder
file(GLOB APP_SOURCES "src/*/*.cpp" )

#Loop through source files
foreach( source_files ${APP_SOURCES} )
    get_filename_component( ProjectId ${source_files} PATH)

    #Extract project name from folders
    string(FIND         ${ProjectId} "Exercise" slLoc)
    string(LENGTH       ${ProjectId} endLoc)
    string(SUBSTRING    ${ProjectId} ${slLoc} ${endLoc} NameForPrj)

    #Set project name
    project(${NameForPrj} C CXX ASM)

    set(SOURCE_FILES ${source_files} ${CMSIS_SYSTEM} ${CMSIS_STARTUP} ${LINKER_SCRIPT})
    add_executable(${PROJECT_NAME}.elf ${SOURCE_FILES} ${LINKER_SCRIPT})

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map")
    set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
    set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

    add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
            COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
            COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
            COMMENT "Building ${HEX_FILE} Building ${BIN_FILE}")

endforeach( source_files ${APP_SOURCES} )

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
#file(GLOB_RECURSE HAL_SOURCES Libraries/STM32F1xx_HAL_Driver/Application/*.c)

include_directories(Libraries/CMSIS/Device/ST/STM32F10x/Include)
include_directories(Libraries/CMSIS/Include)
#include_directories(Libraries/STM32F1xx_HAL_Driver/inc)

#Search for source files within "Application" folder
file(GLOB APP_SOURCES "Application/*/src/" )

#Loop through source files
foreach( application_files ${APP_SOURCES} )
    get_filename_component( ProjectId ${application_files} PATH)

    #Extract project name from folders
    string(FIND         ${ProjectId} "Exercise" slLoc)
    string(FIND         ${ProjectId} "include"  endLoc)
    string(SUBSTRING    ${ProjectId} ${slLoc} 12 ProjectName) #Fix the 12...need to figure out how to extract the project length

    #Set project name
    project(${ProjectName} C CXX ASM)
    message(Building project ${ProjectName} )

    #Set application source files
    file(GLOB APPLICATION_SRC Application/${ProjectName}/src/*.cpp)

    #Set application include files
    include_directories(APPLICATION_INCLUDE ${ProjectName}/include/)

    set(SOURCE_FILES ${APPLICATION_SRC} ${CMSIS_SYSTEM} ${CMSIS_STARTUP} ${LINKER_SCRIPT})
    add_executable(${PROJECT_NAME}.elf ${SOURCE_FILES} ${LINKER_SCRIPT})

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map")
    set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
    set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

    add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
            COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
            COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
            COMMENT "Building ${HEX_FILE} Building ${BIN_FILE}")

endforeach( application_files ${APP_SOURCES} )

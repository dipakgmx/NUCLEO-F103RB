project(Exercise_5_3)
cmake_minimum_required(VERSION 3.15)

#Set application source files
set(APPLICATION_SRC ${CMAKE_SOURCE_DIR}/Application/Exercise_5_3/src/main.cpp
                    ${CMAKE_SOURCE_DIR}/Application/Exercise_5_3/src/USART.cpp)
#Set application include files
include_directories(APPLICATION_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/SOURCE_DIR}/Application/Exercise_5_3/include)

set(SOURCE_FILES ${APPLICATION_SRC} ${CMSIS_SYSTEM} ${CMSIS_STARTUP} ${LINKER_SCRIPT})
add_executable(${PROJECT_NAME}.elf ${SOURCE_FILES} ${LINKER_SCRIPT})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map")
set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex     $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary   $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE} Building ${BIN_FILE}")

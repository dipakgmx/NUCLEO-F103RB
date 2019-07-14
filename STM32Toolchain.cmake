set(MCU_LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/Linker/STM32F103RBTx_FLASH.ld)
set(MCU_ARCH cortex-m3)
set(MCU_FLOAT_ABI soft)
set(MCU_FPU fpv4-sp-d16)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)

# specify cross compilers and tools
SET(CMAKE_C_COMPILER_WORKS 1)
SET(CMAKE_C_COMPILER arm-none-eabi-gcc)
SET(CMAKE_CXX_COMPILER_WORKS 1)
SET(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER  arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)

SET(COMMON_FLAGS
        "-mcpu=cortex-m3 ${FPU_FLAGS} -mthumb -mthumb-interwork -ffunction-sections -fdata-sections \
    -g -fno-common -fmessage-length=0 -specs=nosys.specs -specs=nano.specs")

set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} -std=c++11")
set(CMAKE_C_FLAGS "${COMMON_FLAGS} -std=gnu99")
SET(CMAKE_EXE_LINKER_FLAGS_INIT "-Wl,-gc-sections -T${MCU_LINKER_SCRIPT}")
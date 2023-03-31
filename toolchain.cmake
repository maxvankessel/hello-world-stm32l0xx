set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(TOOLS /opt/gcc-arm-none-eabi-10.3-2021.10/bin)

# Specify the cross compiler
set(CMAKE_C_COMPILER ${TOOLS}/arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER ${TOOLS}/arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER ${TOOLS}/arm-none-eabi-gcc)

# Specify the toolchain file path
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_LIST_DIR}/toolchain.cmake)

# Specify the target processor
set(TARGET_PROCESSOR "cortex-m0plus")

# Compiler flags
set(CMAKE_C_FLAGS "-mcpu=${TARGET_PROCESSOR} -mthumb -mfloat-abi=soft -std=c11")
set(CMAKE_CXX_FLAGS "-mcpu=${TARGET_PROCESSOR} -mthumb -mfloat-abi=soft -std=c++11")
set(CMAKE_ASM_FLAGS "-mcpu=${TARGET_PROCESSOR} -mthumb -mfloat-abi=soft")

# Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-mcpu=${TARGET_PROCESSOR} -mthumb -mfloat-abi=soft -specs=nano.specs -specs=nosys.specs")

# Debug flags
set(CMAKE_C_FLAGS_DEBUG "-g -Og")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Og")

# Release flags
set(CMAKE_C_FLAGS_RELEASE "-O2")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

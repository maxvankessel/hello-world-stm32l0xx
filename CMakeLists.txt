cmake_minimum_required(VERSION 3.13)

set(CMAKE_TOOLCHAIN_FILE "toolchain.cmake")

# Set the project name
project(stm32l0xx-hello-world C ASM)

# Glob all sources with the * extension in directory
file(GLOB SOURCES
    Src/*.c
)

# These are template files, if you want to change these, copy to project and add to sources glob
set(SOURCES_CMSIS
    ${PROJECT_SOURCE_DIR}/Lib/CMSIS/Device/ST/STM32L0xx/Source/Templates/system_stm32l0xx.c
    ${PROJECT_SOURCE_DIR}/Lib/CMSIS/Device/ST/STM32L0xx/Source/Templates/gcc/startup_stm32l010xb.s
)

# To add specific HAL drivers active the following include
set(SOURCES_HAL_STM32
    ${PROJECT_SOURCE_DIR}/Lib/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_utils.c
)

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${SOURCES_CMSIS} ${SOURCES_HAL_STM32})

# Specify the include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/Inc
    ${PROJECT_SOURCE_DIR}/Lib/CMSIS/Core/Include
    ${PROJECT_SOURCE_DIR}/Lib/CMSIS/Device/ST/STM32L0xx/Include
    ${PROJECT_SOURCE_DIR}/Lib/STM32L0xx_HAL_Driver/Inc
)

# Set to correct CPU, TODO FIXME
target_compile_definitions(${PROJECT_NAME} PRIVATE STM32L010xB)

# Specify the linker script
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32L010RBTx_FLASH.ld)
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})
target_link_options(${PROJECT_NAME} PRIVATE -T ${LINKER_SCRIPT})

# Append output extension to file
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}.elf")

# Convert ELF to BIN and HEX
add_custom_command(TARGET "${PROJECT_NAME}" POST_BUILD
    COMMAND "${CMAKE_OBJCOPY}" ARGS -O binary "$<TARGET_FILE:${PROJECT_NAME}>" ${PROJECT_NAME}.bin
    COMMAND "${CMAKE_OBJCOPY}" ARGS -O ihex "$<TARGET_FILE:${PROJECT_NAME}>" ${PROJECT_NAME}.hex)

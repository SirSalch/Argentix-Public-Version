cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_COMPILER    riscv64-unknown-elf-gcc)
set(CMAKE_CXX_COMPILER  riscv64-unknown-elf-g++)
set(CMAKE_ASM_COMPILER  riscv64-unknown-elf-gcc)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

project(Project LANGUAGES C CXX ASM)

add_executable(firmware.elf
    ${CMAKE_CURRENT_SOURCE_DIR}/hardware/EEPROM_Linker.ld
    ${CMAKE_CURRENT_SOURCE_DIR}/hardware/Startup.s
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Main.cpp
)

target_include_directories(firmware.elf PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/argentix/standard_libraries
    ${CMAKE_CURRENT_SOURCE_DIR}/argentix
    ${CMAKE_CURRENT_SOURCE_DIR}/aris
)

target_compile_options(firmware.elf PRIVATE
    -fno-threadsafe-statics
    -fno-use-cxa-atexit
    -march=rv32i
    -mabi=ilp32
    -Os
    -nostdlib
    -fno-exceptions
    -fno-asynchronous-unwind-tables
    -fno-unwind-tables
)

# Добавляем те же флаги архитектуры на этап линковки
target_link_options(firmware.elf PRIVATE
    -march=rv32i
    -mabi=ilp32
    -nostdlib
    -T ${CMAKE_CURRENT_SOURCE_DIR}/hardware/EEPROM_Linker.ld
    -Wl,--no-warn-rwx-segments
)

# Отключаем автоматическое добавление стандартных библиотек
set_target_properties(firmware.elf PROPERTIES
    STANDARD_LIBRARIES ""
)

add_custom_command(TARGET firmware.elf POST_BUILD
    # Вывод логотипа
    COMMAND echo "[=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=]"
    COMMAND echo "   ╔═════╗    ╔═════════╗  ╔═════════╗  ╔═════════╗  ╔═╗     ╔═╗  ╔═════════╗  ╔═╗     ╔═╗  ╔═╗     ╔═╗  ╔═════════╗ "
    COMMAND echo "  ╔██████╚═╗  ██████████║  ██████████╝  ██████████╝  ██║     ██║  ██████████╝  ██║   ╔═██║  ██║   ╔═██╝  ██████████╝ "
    COMMAND echo " ██╚═════██║  ██╚═════██║  ██║          ██╚═══════╗  ██╚═════██║      ██║      ██║ ╔═████║  ██╚═══██╝    ██║         "
    COMMAND echo " ██████████║  ██████████╝  ██║          ██████████╝  ██████████║      ██║      ██╚═██╝ ██║  ██████╚═╗    ██║         "
    COMMAND echo " ██║     ██║  ██║          ██║          ██╚═══════╗  ██║     ██║      ██║      ████╝   ██║  ██║   ██╚═╗  ██╚═══════╗ "
    COMMAND echo " ██╝     ██╝  ██╝          ██╝          ██████████╝  ██╝     ██╝      ██╝      ██╝     ██╝  ██╝     ██╝  ██████████╝ "
    COMMAND echo " "
    COMMAND echo "[=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=]"

    # Вывод информации о размере
    COMMAND echo ""
    COMMAND echo "=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═="
    COMMAND riscv64-unknown-elf-size $<TARGET_FILE:firmware.elf>
    COMMAND echo "=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═=═="
    COMMAND echo ""

    COMMAND riscv64-unknown-elf-objdump -d -S -C $<TARGET_FILE:firmware.elf> > "${CMAKE_CURRENT_BINARY_DIR}/firmware_dump.s"

    # Генерация .bin и удаление .elf
    COMMAND riscv64-unknown-elf-objcopy -O binary $<TARGET_FILE:firmware.elf> firmware.bin
    COMMAND ${CMAKE_COMMAND} -E remove $<TARGET_FILE:firmware.elf>
    COMMENT "[Инфо] Успешная генерация бинарного файла"
)
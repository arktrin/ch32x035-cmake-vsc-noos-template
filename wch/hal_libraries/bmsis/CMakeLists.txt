target_sources(${TARGET_ELF} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/source/ch32x035_it.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/core_riscv.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/startup_ch32x035.S
    ${CMAKE_CURRENT_SOURCE_DIR}/source/system_ch32x035.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/debug.c
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ch32x035_conf.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ch32x035_it.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/core_riscv.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/system_ch32x035.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/debug.h
)

target_include_directories(${TARGET_ELF} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
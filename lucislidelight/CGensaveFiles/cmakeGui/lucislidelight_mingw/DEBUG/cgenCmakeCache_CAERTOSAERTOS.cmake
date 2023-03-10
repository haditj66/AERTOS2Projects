set(BUILD_TESTS TRUE)
add_compile_definitions(BUILD_TESTS__${BUILD_TESTS})
set(BUILD_UNIT_TESTS FALSE)
add_compile_definitions(BUILD_UNIT_TESTS__${BUILD_UNIT_TESTS})
set(PRINT_METHOD PRINT_SEMIHOSTING)
add_compile_definitions(PRINT_METHOD__${PRINT_METHOD})
set(INCLUDE_HAL TRUE)
add_compile_definitions(INCLUDE_HAL__${INCLUDE_HAL})
add_compile_definitions(CGEN_ALLOPTIONS="@BUILD_TESTS::TRUE @BUILD_UNIT_TESTS::FALSE @PRINT_METHOD::PRINT_SEMIHOSTING @INCLUDE_HAL::TRUE ")

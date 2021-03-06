
macro(disable_deprecated_register_warning TARGET)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        target_compile_options(${TARGET} PRIVATE "-Wno-deprecated-register")
    endif()
endmacro()

macro(disable_deprecated_declarations_warning TARGET SCOPE)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        target_compile_options(${TARGET} PRIVATE "-Wno-deprecated-declarations")
    endif()
endmacro()

macro(enable_override_warning TARGET SCOPE)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(${TARGET} PRIVATE "-Wsuggest-override")
    endif()
endmacro()

macro(enable_undef_warning TARGET SCOPE)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
        target_compile_options(${TARGET} ${SCOPE} "-Wundef")
    endif()
endmacro()

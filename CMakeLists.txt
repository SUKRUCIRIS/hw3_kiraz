
#
# Project setup
#

cmake_minimum_required(VERSION 3.10)

project(kiraz)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(IS_CC_GCC TRUE)

elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND "${CMAKE_CXX_SIMULATE_ID}" STREQUAL "MSVC")
    set(IS_CC_CLANG TRUE)
    set(IS_CC_CLANG_CL TRUE)

elseif(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    set(IS_CC_CLANG TRUE)
    set(IS_CC_CLANG_APPLE TRUE)

elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(IS_CC_CLANG TRUE)

elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(IS_CC_MSVC TRUE)

else()
    message(FATAL_ERROR "Unrecognized compiler ${CMAKE_CXX_COMPILER_ID}")

endif()

add_compile_options(
    -Werror=return-type
    -Werror=dangling-else
    -Werror=non-virtual-dtor
    -Werror=suggest-override
)

if (IS_CC_GCC)
    add_compile_options(
        -Werror=return-local-addr
    )

elseif(IS_CC_CLANG)
    add_compile_options(
        -Werror=return-stack-address
    )

endif()


#
# Flex/Bison boilerplate
#

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

if (WIN32)
    set (ADDITIONAL_FLEX_FLAGS "--wincompat")
    set (ADDITIONAL_BISON_FLAGS "--wincompat")
endif()

#
# Common Code
#

# Own files
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(kiraz STATIC
    fmt/chrono.h
    fmt/core.h
    fmt/format.cc
    fmt/std.h
    fmt/printf.h
    fmt/format-inl.h
    fmt/ostream.h
    fmt/ranges.h
    fmt/xchar.h
    fmt/color.h
    fmt/format.h
    fmt/compile.h
    fmt/args.h
    fmt/os.cc
    fmt/os.h

    kiraz/helpers/Result.h

    kiraz/token.h

    kiraz/token/Base.cc
    kiraz/token/Base.h
    kiraz/token/Integer.h
    kiraz/token/Keyword.h
    kiraz/token/Operator.h
    kiraz/token/String.h
    kiraz/token/Rejected.h

    kiraz/stmt.h

    kiraz/stmt/Base.h
    kiraz/stmt/Operator.h
    kiraz/stmt/Keyword.h
    kiraz/stmt/Literal.h
    kiraz/stmt/Base.cpp
)

# Generated files
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/gen/include/kiraz)
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}/gen/include
    ${CMAKE_CURRENT_BINARY_DIR}/gen/include/kiraz
)

#
# Homework 1
#

flex_target(HW1_LEXER
    ${CMAKE_CURRENT_SOURCE_DIR}/hw1.l
    ${CMAKE_CURRENT_BINARY_DIR}/gen/hw1-lexer.cpp
    DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/gen/include/kiraz/hw1-lexer.hpp
    COMPILE_FLAGS ${ADDITIONAL_FLEX_FLAGS}
)

add_executable(hw1 hw1.cc ${FLEX_HW1_LEXER_OUTPUTS})
target_link_libraries(hw1 PUBLIC kiraz ${FLEX_LIBRARIES})

#
# Homework 2
#

flex_target(HW2_LEXER
    ${CMAKE_CURRENT_SOURCE_DIR}/hw2.l
    ${CMAKE_CURRENT_BINARY_DIR}/gen/hw2-lexer.cpp
    DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/gen/include/kiraz/hw2-lexer.hpp
    COMPILE_FLAGS ${ADDITIONAL_FLEX_FLAGS}
)

bison_target(HW2_PARSER
    ${CMAKE_CURRENT_SOURCE_DIR}/hw2.y
    ${CMAKE_CURRENT_BINARY_DIR}/gen/hw2-parser.cpp
    DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/gen/include/kiraz/hw2-parser.hpp
    VERBOSE REPORT_FILE ${CMAKE_CURRENT_BINARY_DIR}/gen/include/kiraz/hw2-parser.output
    COMPILE_FLAGS ${ADDITIONAL_BISON_FLAGS} -Wcounterexamples
)

add_flex_bison_dependency(HW2_LEXER HW2_PARSER)

# https://lists.gnu.org/archive/html/help-bison/2021-01/msg00020.html
# https://gcc.gnu.org/bugzilla/show_bug.cgi?id=98753
if (IS_CC_GCC)
    set_property(SOURCE ${CMAKE_CURRENT_BINARY_DIR}/gen/hw2-parser.cpp
        APPEND PROPERTY COMPILE_FLAGS -Wno-free-nonheap-object
    )
endif()

add_executable(hw2 hw2.cc ${FLEX_HW2_LEXER_OUTPUTS} ${BISON_HW2_PARSER_OUTPUTS})
target_link_libraries(hw2 PUBLIC kiraz ${FLEX_LIBRARIES} ${BISON_LIBRARIES})


#
# Homework 3
#

flex_target(HW3_LEXER
    ${CMAKE_CURRENT_SOURCE_DIR}/hw3.l
    ${CMAKE_CURRENT_BINARY_DIR}/gen/hw3-lexer.cpp
    DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/gen/include/kiraz/hw3-lexer.hpp
    COMPILE_FLAGS ${ADDITIONAL_FLEX_FLAGS}
)

bison_target(HW3_PARSER
    ${CMAKE_CURRENT_SOURCE_DIR}/hw3.y
    ${CMAKE_CURRENT_BINARY_DIR}/gen/hw3-parser.cpp
    DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/gen/include/kiraz/hw3-parser.hpp
    VERBOSE REPORT_FILE ${CMAKE_CURRENT_BINARY_DIR}/gen/include/kiraz/hw3-parser.output
    COMPILE_FLAGS ${ADDITIONAL_BISON_FLAGS} -Wcounterexamples
)

add_flex_bison_dependency(HW3_LEXER HW3_PARSER)

# https://lists.gnu.org/archive/html/help-bison/2021-01/msg00020.html
# https://gcc.gnu.org/bugzilla/show_bug.cgi?id=98753
if (IS_CC_GCC)
    set_property(SOURCE ${CMAKE_CURRENT_BINARY_DIR}/gen/hw3-parser.cpp
        APPEND PROPERTY COMPILE_FLAGS -Wno-free-nonheap-object
    )
endif()

add_executable(hw3 hw3.cc ${FLEX_HW3_LEXER_OUTPUTS} ${BISON_HW3_PARSER_OUTPUTS})
target_link_libraries(hw3 PUBLIC kiraz ${FLEX_LIBRARIES} ${BISON_LIBRARIES})

#
# Tests
#

include(test.cmake)

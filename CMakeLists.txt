cmake_minimum_required(VERSION 3.16)

project(EvacuationC
    VERSION 0.1.0
    LANGUAGES C
    DESCRIPTION "Evacuation modeling"
    HOMEPAGE_URL https://github.com/bvchirkov/EvacuationC
)

set(CMAKE_PROJECT_INCLUDE_BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Policy.cmake)

include(FetchContent)
include(CTest)

option(build_tests "Build all of own tests" OFF)

set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

if (MSVC)
    set(CMAKE_C_FLAGS "/Wall")
    set(CMAKE_C_FLAGS_RELEASE "/O2")
else()
    set(CMAKE_C_FLAGS "-std=gnu11 -W -Wall -Wextra -Wparentheses -Wshadow -funsigned-char")
    set(CMAKE_C_FLAGS_DEBUG "-g -O0")
    #set(CMAKE_C_FLAGS_DEBUG     "${CMAKE_C_FLAGS_DEBUG} -fsanitize=address -fsanitize=pointer-subtract -fsanitize=shift")
    set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")
endif()

if (NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE Release)
endif()

set(PROJECT_LIB_STATIC ${PROJECT_NAME}_static)
set(PROJECT_LIB_SHARED ${PROJECT_NAME}_shared)
set(SOURCES_LIB
    src/bim_tools.c         src/bim_tools.h
    src/bim_graph.c         src/bim_graph.h
    src/bim_evac.c          src/bim_evac.h
    src/bim_polygon_tools.c src/bim_polygon_tools.h
    src/bim_configure.c     src/bim_configure.h
    src/bim_json_object.c   src/bim_json_object.h
    src/bim_uuid.h
    src/bim_output.c        src/bim_output.h
    src/bim_modeling.c      src/bim_modeling.h
)

add_library(${PROJECT_LIB_STATIC}
    STATIC
        ${SOURCES_LIB}
)

add_library(${PROJECT_LIB_SHARED}
    SHARED
        ${SOURCES_LIB}
)

FetchContent_Declare(
    c-logger
    GIT_REPOSITORY https://github.com/NikBel3476/c-logger.git
    GIT_TAG 0a2f68ad4a0585cefa58fcafd9ac1716b8c74674 # upstream/master
)

FetchContent_Declare(
    json-c
    GIT_REPOSITORY https://github.com/json-c/json-c.git
    GIT_TAG b4c371fa0cbc4dcbaccc359ce9e957a22988fb34 # json-c-0.17-20230812
)

FetchContent_MakeAvailable(c-logger json-c)

if (SKBUILD)
    if (CMAKE_COMPILER_IS_GNUCC)
        target_compile_options(logger_static PUBLIC "-fPIC")
    endif()
    add_subdirectory(EvacuationC)
else()
    add_executable(${PROJECT_NAME}
            src/main.c
            src/bim_cli.c src/bim_cli.h
    )

    target_link_libraries(${PROJECT_NAME}
            PRIVATE
            ${PROJECT_LIB_STATIC}
    )

    ### Test
    #if(build_tests AND ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
        enable_testing()
        add_subdirectory(tests)
    #endif()
endif()

target_include_directories(${PROJECT_LIB_STATIC}
    PUBLIC
        ./thirdparty/arraylist
)

target_include_directories(${PROJECT_LIB_SHARED}
    PUBLIC
        ./thirdparty/arraylist
)

target_link_libraries(${PROJECT_LIB_STATIC}
    PUBLIC
        logger_static
        arraylist
        json-c-static
)

target_link_libraries(${PROJECT_LIB_SHARED}
    PUBLIC
        logger
        arraylist
        json-c
)

add_subdirectory(thirdparty/arraylist)

set(tests
    test_bim_object.c
    test_bim_polygon_tools.c
    test_bim_evac.c
)

set(EvacuationC_sources
    ../src/bim_tools.c         ../src/bim_tools.h
    ../src/bim_graph.c         ../src/bim_graph.h
    ../src/bim_evac.c          ../src/bim_evac.h
    ../src/bim_polygon_tools.c ../src/bim_polygon_tools.h
    ../src/bim_configure.c     ../src/bim_configure.h
    ../src/bim_json_object.c   ../src/bim_json_object.h
    ../src/bim_cli.c           ../src/bim_cli.h
    ../src/bim_uuid.h
    ../src/bim_output.c        ../src/bim_output.h
)

add_library(${PROJECT_NAME}_lib
    STATIC
        ${EvacuationC_sources}
)

target_link_libraries(${PROJECT_NAME}_lib
    PUBLIC
        logger_static
        pthread
        arraylist
        json-c-static
        m
)

include_directories(
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/thirdparty/arraylist
        ${PROJECT_SOURCE_DIR}/tests
)

foreach(test IN LISTS tests)
    add_executable(${test} ${test})
    target_compile_definitions(${test}
        PRIVATE
            ROOT_PATH="${CMAKE_SOURCE_DIR}/res"
    )
    target_include_directories(${test}
        PUBLIC
            ${CMAKE_SOURCE_DIR}/src
            ${CMAKE_SOURCE_DIR}/thirdparty/arraylist
    )
    target_link_libraries(${test}
        PRIVATE
            ${PROJECT_NAME}_lib
    )
    add_test(
        NAME ${test}
        COMMAND ${test}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/tests
    )
endforeach()

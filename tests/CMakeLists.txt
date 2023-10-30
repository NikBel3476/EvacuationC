include(CTest)

set(tests
    test_bim_object
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        ROOT_PATH="${CMAKE_SOURCE_DIR}/res"
)

include_directories(
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/tests
)

foreach(test IN LISTS tests)
    add_executable(${test} ${test}.c)
    target_include_directories(${test}
        PRIVATE
            ${CMAKE_SOURCE_DIR}/src
    )
    target_link_libraries(${test} bim-tools)
    add_test(
        NAME ${test}
        COMMAND ${test}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/tests
    )
endforeach()

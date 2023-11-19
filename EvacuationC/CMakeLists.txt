find_package(PythonExtensions REQUIRED)
find_package(Cython REQUIRED)

add_cython_target(evacuation_c C PY3)
add_library(evacuation_c MODULE ${evacuation_c})
target_link_libraries(evacuation_c ${PROJECT_LIB_SHARED})
target_include_directories(evacuation_c PUBLIC "../src")

python_extension_module(evacuation_c)
install(TARGETS evacuation_c LIBRARY DESTINATION EvacuationC)

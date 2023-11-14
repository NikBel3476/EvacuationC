add_cython_target(evacuation_c C)
add_library(evacuation_c MODULE
        ${evacuation_c}
        ../src/bim_tools.c         ../src/bim_tools.h
        ../src/bim_graph.c         ../src/bim_graph.h
        ../src/bim_evac.c          ../src/bim_evac.h
        ../src/bim_polygon_tools.c ../src/bim_polygon_tools.h
        ../src/bim_configure.c     ../src/bim_configure.h
        ../src/bim_json_object.c   ../src/bim_json_object.h
        ../src/bim_uuid.h
        ../src/bim_output.c        ../src/bim_output.h
)
python_extension_module(evacuation_c)

install(TARGETS evacuation_c LIBRARY DESTINATION build_cython)

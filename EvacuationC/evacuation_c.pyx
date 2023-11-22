from EvacuationC cimport cevacuation_c


cdef double bim_tools_get_area_bim_py(const cevacuation_c.bim_t* bim):
    return cevacuation_c.bim_tools_get_area_bim(bim)

#cdef evacuation_c.modeling_result_t run_modeling(
#    const char* path_to_file,
#    const char* path_to_json,
#    const evacuation_c.bim_cfg_scenario_t* bim_cfg_scenario
#):

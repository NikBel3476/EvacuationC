from EvacuationC cimport cevacuation_c


#cdef double bim_tools_get_area_bim_py(const cevacuation_c.bim_t* bim):
#    return cevacuation_c.bim_tools_get_area_bim(bim)

#cdef cevacuation_c.modeling_result_t run_modeling(
#    const char* path_to_file,
#    const cevacuation_c.bim_cfg_scenario_t* bim_cfg_scenario
#):
#    return cevacuation_c.run_modeling(path_to_file, bim_cfg_scenario)

#def bim_tools_get_area_bim_py(cevacuation_c.bim_t bim):
#    return cevacuation_c.bim_tools_get_area_bim(bim)

#def run_modeling(
#    str path_to_file,
#    cevacuation_c.bim_cfg_scenario_t bim_cfg_scenario
#):
#    return cevacuation_c.run_modeling(path_to_file, bim_cfg_scenario)

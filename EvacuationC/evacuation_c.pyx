from EvacuationC cimport cevacuation_c


cdef bim_tools_get_area_bim_py(const cevacuation_c.bim_t* bim):
    return cevacuation_c.bim_tools_get_area_bim(bim)

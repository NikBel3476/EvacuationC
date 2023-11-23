cdef extern from "bim_tools.h":
    ctypedef struct bim_transit_t:
        pass

    ctypedef struct bim_zone_t:
        pass

    ctypedef struct bim_level_t:
        pass

    ctypedef struct bim_t:
        pass

    # Устанавливает в помещение заданное количество людей
    void bim_tools_set_people_to_zone (bim_zone_t* element, float num_of_people)

    # Подсчитывает количество людей в здании по расширенной структуре
    double bim_tools_get_numofpeople(const bim_t* bim)

    # Подсчитывает суммарную площадь элементов всего здания
    double bim_tools_get_area_bim(const bim_t* bim)

cdef extern from "bim_configure.h":
    ctypedef struct bim_cfg_scenario_t:
        pass

cdef extern from "bim_modeling.h":
    ctypedef struct modeling_result_t:
        double time_in_s
        double num_of_evacuated_people
        double num_of_people_in_safety_zone

    modeling_result_t run_modeling(const char* path_to_file, const char* bim_cfg_scenario_path)

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
    # ctypedef struct bim_cfg_transitions_width_t:
    #     enum
    #     transits_width_type    type;
    #     float                       doorwayin;
    #     float                       doorwayout;
    #     special_t *special;
    #     uint8_t                     num_of_special_blocks;
    #
    #
    # ctypedef struct bim_cfg_modeling_t:
    #     float step
    #     float speed_max
    #     float density_min
    #     float density_max
    #
    # ctypedef struct bim_cfg_file_name_t:
    #     char[256] x

    ctypedef struct bim_cfg_scenario_t:
        pass
        # bim_cfg_file_name_t *bim_jsons
        # bim_cfg_file_name_t logger_configure
        # unsigned char num_of_bim_jsons
        # bim_cfg_distribution_t distribution
        # bim_cfg_transitions_width_t transits
        # bim_cfg_modeling_t modeling

    const bim_cfg_scenario_t* bim_cfg_load(const char *filename)

cdef extern from "bim_modeling.h":
    ctypedef struct modeling_result_t:
        double time_in_s
        double num_of_evacuated_people
        double num_of_people_in_safety_zone

    modeling_result_t run_modeling(const char* path_to_file, const bim_cfg_scenario_t* bim_cfg_scenario)


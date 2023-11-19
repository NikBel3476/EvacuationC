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

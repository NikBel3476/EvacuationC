#ifndef EVACUATIONC_BIM_MODELING_H
#define EVACUATIONC_BIM_MODELING_H

#include <stdio.h>

#include "logger.h"
#include "bim_configure.h"
#include "bim_output.h"
#include "bim_tools.h"
#include "bim_evac.h"
#include "bim_graph.h"
#include "bim_json_object.h"

typedef struct {
    double time_in_s;
    double num_of_evacuated_people;
    double num_of_people_in_safety_zone;
} modeling_result_t;

modeling_result_t run_modeling(const char *path_to_file, const bim_cfg_scenario_t *bim_cfg_scenario);

#endif //EVACUATIONC_BIM_MODELING_H

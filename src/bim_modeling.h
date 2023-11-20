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

void run_modeling(const char *path_to_file, const char *path_to_json, const bim_cfg_scenario_t *bim_cfg_scenario);

#endif //EVACUATIONC_BIM_MODELING_H

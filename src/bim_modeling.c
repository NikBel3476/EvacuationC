#include "bim_modeling.h"

void applying_scenario_bim_params(bim_t* bim, const bim_cfg_scenario_t* cfg_scenario);

modeling_result_t run_modeling(
        const char *path_to_file,
        const bim_cfg_scenario_t *bim_cfg_scenario
) {
    printf("File path: %s\n", path_to_file);
    if (bim_cfg_scenario == NULL) {
        printf("CFG IS NULL!!!!");
    }
    printf("Logger path: %s\n", (char *)bim_cfg_scenario->logger_configure.x);
    // Настройки с-logger
    logger_configure(bim_cfg_scenario->logger_configure.x);

    char *filename = bim_basename(path_to_file);
    LOG_INFO("The file name of the used bim `%s.json`", filename);

    // Чтение файла и разворачивание его в структуру
    LOG_TRACE("Use module `bim_json_object`. Read the file of bim and create a programming structure");
    const bim_json_object_t * bim_json = bim_json_new(path_to_file);
    {
        LOG_TRACE("Name of building: %s", bim_json->name);

        LOG_TRACE("##Address info");
        LOG_TRACE("City: %s", bim_json->address->city);
        LOG_TRACE("Street: %s", bim_json->address->street_address);
        LOG_TRACE("Additional: %s", bim_json->address->add_info);
    }

    bim_t *bim = bim_tools_new(bim_json);
    {
        LOG_TRACE("##Levels info");
        LOG_TRACE("Num of levels: %i", bim->numoflevels);

        for (size_t i = 0; i < bim->numoflevels; ++i)
        {
            LOG_TRACE("##Level info");
            LOG_TRACE("Level name: %s", bim->levels[i].name);
            LOG_TRACE("Num of zones on the level: %i", bim->levels[i].numofzones);
            LOG_TRACE("Num of transits on the level: %i", bim->levels[i].numoftransits);
            LOG_TRACE("Level height over zero mark: %d", bim->levels[i].z_level);

            LOG_TRACE("##Zones info");
            for (size_t j = 0; j < bim->levels[i].numofzones; ++j)
            {
                LOG_TRACE("Id: %zu", bim->levels[i].zones[j].id);
                LOG_TRACE("Element name: %s | UUID: %s", bim->levels[i].zones[j].name, bim->levels[i].zones[j].uuid.x);
                LOG_TRACE("Num of outputs: %i", bim->levels[i].zones[j].numofoutputs);
                LOG_TRACE("Area: %f", bim->levels[i].zones[j].area);
            }

            LOG_TRACE("##Transits info");
            for (size_t j = 0; j < bim->levels[i].numoftransits; ++j)
            {
                LOG_TRACE("Id: %zu", bim->levels[i].transits[j].id);
                LOG_TRACE("Element name: %s | UUID: %s", bim->levels[i].transits[j].name, bim->levels[i].transits[j].uuid.x);
                LOG_TRACE("Num of outputs: %i", bim->levels[i].transits[j].numofoutputs);
                LOG_TRACE("Width: %f", bim->levels[i].transits[j].width);
            }
        }

        LOG_TRACE("Outside id: %u", ((bim_zone_t *)bim->zones->data[bim->zones->length-1])->id);
        LOG_TRACE("Outside uuid: %s", ((bim_zone_t *)bim->zones->data[bim->zones->length-1])->uuid.x);
    }

    applying_scenario_bim_params(bim, bim_cfg_scenario);

    // Files with results
    char *output_detail = bim_create_file_name(filename, OUTPUT_DETAIL_FILE, OUTPUT_SUFFIX);
    char *output_short  = bim_create_file_name(filename, OUTPUT_SHORT_FILE,  OUTPUT_SUFFIX);
    free(filename);

    FILE *fp_detail = fopen(output_detail, "w+");
    LOG_TRACE("Created file for detailed information about flows pedestrian: %s", output_detail);

    bim_output_head(bim, fp_detail);
    bim_output_body(bim, 0, fp_detail);

    bim_graph_t *graph = bim_graph_new(bim);
    bim_graph_print(graph);

    ArrayList *transits = bim->transits;
    ArrayList *zones    = bim->zones;
    evac_def_modeling_step(bim);
    evac_time_reset();

    double remainder = 0.0; // Количество человек, которое может остаться в зд. для остановки цикла
    while(true)
    {
        evac_moving_step(graph, zones, transits);
        evac_time_inc();
        bim_output_body(bim, evac_get_time_m(), fp_detail);

        double num_of_people = 0;
        for (size_t i = 0; i < zones->length; i++)
        {
            bim_zone_t *zone = zones->data[i];
            if (zone->is_visited)
            {
                num_of_people += zone->numofpeople;
            }
        }

        if (num_of_people <= remainder) break;
    }

    double time_in_s = evac_get_time_s();
    double num_of_evacuated_people = bim_tools_get_numofpeople(bim);
    double num_of_people_in_safety_zone = ((bim_zone_t*)zones->data[OUTSIDE_IDX(bim)])->numofpeople;
    LOG_INFO("Длительность эвакуации: %.2f с. (%.2f мин.)", time_in_s, evac_get_time_m());
    LOG_INFO("Количество человек: в здании - %.2f (в безопасной зоне - %.2f) чел.", num_of_evacuated_people, num_of_people_in_safety_zone);
    LOG_INFO("---------------------------------------");

    {
        FILE *fp_short = fopen(output_short, "w+");
        LOG_TRACE("Created file for shorted information about evacuation: %s", output_short);
        LOG_TRACE("[Total] Time - %.2f, Number of people in the build - %.2f, Number of people in the outside - %.2f", evac_get_time_m(), bim_tools_get_numofpeople(bim), ((bim_zone_t*)zones->data[OUTSIDE_IDX(bim)])->numofpeople);

        fprintf(fp_short, "%.2f,%.2f,%.2f", evac_get_time_m(), bim_tools_get_numofpeople(bim), ((bim_zone_t*)zones->data[OUTSIDE_IDX(bim)])->numofpeople);
        fflush(fp_short);
        fclose(fp_short);
//            free(output_short);
    }

    fclose(fp_detail);
//        free(output_detail);
    bim_graph_free(graph);
    bim_tools_free(bim);

    modeling_result_t modeling_result = {
        .time_in_s = time_in_s,
        .num_of_evacuated_people = num_of_evacuated_people,
        .num_of_people_in_safety_zone = num_of_people_in_safety_zone
    };

    return modeling_result;
}

void applying_scenario_bim_params(bim_t* bim, const bim_cfg_scenario_t* cfg_scenario)
{
    ArrayList *transits = bim->transits;
    for (size_t i = 0; i < transits->length; ++i)
    {
        bim_transit_t *transit = transits->data[i];

        if (cfg_scenario->transits.type == transits_width_users)
        {
            if (transit->sign == DOOR_WAY_INT) transit->width = cfg_scenario->transits.doorwayin;
            if (transit->sign == DOOR_WAY_OUT) transit->width = cfg_scenario->transits.doorwayout;
        }

        // A special set up the transit width of item of bim
        for (size_t s = 0; s < cfg_scenario->transits.num_of_special_blocks; s++)
        {
            const special_t special = cfg_scenario->transits.special[s];
            for (size_t u = 0; u < special.num_of_uuids; u++)
            {
                if (uuideq(transit->uuid.x, special.uuid[u].x))
                {
                    transit->width = special.value;
                }
            }
        }
    }

    ArrayList * zones = bim->zones;
    for (size_t i = 0; i < zones->length; ++i)
    {
        bim_zone_t *zone = zones->data[i];
        if (zone->sign == OUTSIDE) continue;

        if (cfg_scenario->distribution.type == distribution_uniform)
        {
            bim_tools_set_people_to_zone(zone, (zone->area * cfg_scenario->distribution.density));
        }

        // A special set up the density of item of bim
        for (size_t s = 0; s < cfg_scenario->distribution.num_of_special_blocks; s++)
        {
            const special_t special = cfg_scenario->distribution.special[s];
            for (size_t u = 0; u < special.num_of_uuids; u++)
            {
                if (uuideq(zone->uuid.x, special.uuid[u].x))
                {
                    bim_tools_set_people_to_zone(zone, (zone->area * special.value));
                }
            }
        }
    }

    evac_set_modeling_step(cfg_scenario->modeling.step);
    evac_set_speed_max(cfg_scenario->modeling.speed_max);
    evac_set_density_max(cfg_scenario->modeling.density_max);
    evac_set_density_min(cfg_scenario->modeling.density_min);
}

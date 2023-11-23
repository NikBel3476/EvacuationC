/* Copyright © 2021 bvchirkov
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "loggerconf.h"

#include "bim_cli.h"
#include "bim_configure.h"
#include "bim_modeling.h"

void run_modeling_by_cfg(const cli_params_t *cli_params);

int main (int argc, char** argv)
{
#ifdef _WIN32
    system("chcp 65001");
#endif
    const cli_params_t *cli_params = read_cl_args(argc, argv);
    run_modeling_by_cfg(cli_params);
    return 0;
}

void run_modeling_by_cfg(const cli_params_t *cli_params) {
    for (size_t bim_idx = 0; bim_idx < bim_cfg_scenario->num_of_bim_jsons; bim_idx++)
    {
        run_modeling(
            (char *)bim_cfg_scenario->bim_jsons[bim_idx].x,
            cli_params->scenario_file
        );
    }
}

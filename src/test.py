import os
from pathlib import Path
from EvacuationC import run_modeling


dir_path = os.path.dirname(os.path.realpath(__file__))

json_path = str(Path(dir_path, '../res/one_zone_one_exit.json').resolve())
cfg_scenario_path = str(Path(dir_path, '../scenario.json').resolve())
modeling_result = run_modeling(json_path, cfg_scenario_path)

print(modeling_result)

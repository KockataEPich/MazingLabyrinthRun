import json
import pre_process.validation as validation
import pre_process.fetch_data as fetch_data
import write.write_components as write_components
import write.write_systems as write_systems

import os
from shutil import rmtree

def clean_generated_folder_and_create_dirs(generation_folder):
    rmtree(generation_folder) 

    for component_type in validation.component_types:
        os.makedirs(os.path.join(generation_folder, "components", component_type + "_components"))

    for system_type in validation.system_types:
        os.makedirs(os.path.join(generation_folder, "systems", system_type + "_systems"))

def get_json_data(file_name):
    f = open(file_name)
    try:
        data = json.load(f)
    except:
        raise Exception("JSON LOADING IS NOT GOOD IN " + file_name)
    return data

def main():
    print("-- Code Generation Start")
    json_data_path = os.path.join("code_generation", "json_representations")

    component_data = get_json_data(os.path.join(json_data_path, "components.json"))
    system_data = get_json_data(os.path.join(json_data_path, "systems.json"))

    validation.validate_jsons(component_data, system_data)
    
    generation_folder = os.path.join("code", "include", "generated")
    clean_generated_folder_and_create_dirs(generation_folder)

    [component_dict, system_dict] = fetch_data.fetch_data(component_data, system_data, generation_folder)    

    write_components.write_components(component_dict.values(), generation_folder)
    write_systems.write_systems(system_dict.values(), generation_folder)

    print("-- Code Generation Finish")

if __name__ == "__main__":
    main()
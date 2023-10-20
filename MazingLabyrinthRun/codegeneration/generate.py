import json
import validation
import write_components
import write_systems
import fetch_data
import os

def get_json_data(file_name):
    f = open(file_name)
    try:
        data = json.load(f)
    except:
        raise Exception("JSON LOADING IS NOT GOOD")
    return data

def main():
    component_data, system_data = get_json_data("components.json"), get_json_data("systems.json")

    validation.validate_jsons(component_data, system_data)

    [component_dict, system_dict] = fetch_data.fetch_data(component_data, system_data)

    generation_folder = os.path.join(os.path.dirname(os.getcwd()), "code", "include", "generated")
    write_components.write_components(component_dict.values(), generation_folder)
    write_systems.write_systems(system_dict.values(), generation_folder)

if __name__ == "__main__":
    main()
import json
import validation
import write_components
import fetch_components

def main():
    f = open("components.json")
    try:
        data = json.load(f)
    except:
        raise Exception("JSON LOADING IS NOT GOOD")

    validation.validate_json(data)
    component_dict = fetch_components.fetch_components_from_data(data)
    write_components.write_components(component_dict.values())


if __name__ == "__main__":
    main()
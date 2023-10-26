accepted_component_keys = ["type", "needs_cpp", "includes", "members", "var_name"]
accepted_system_keys = ["type", "var_name", "components", "includes", "public_functions", "private_functions", "members", "initiator_components", "victim_components"]
accepted_member_keys = ["is_parameter", "is_reference", "name", "default_value", "moved"]

component_types = ["data", "basic"]
system_types = ["producer", "react", "impulse", "render"]

def check_exists(name, metadata, mandatory = False,):
    if metadata is None:
        if mandatory == False:
            return 
        else:
            raise Exception("Missing mandatory keyword: ", name, "")

def check_incompatible_keys(key1, key2, metadata):
    if metadata.get(key1) is not None and metadata.get(key2) is not None:
        raise Exception("Non compatible keys found")
    
def validate(name, metadata, accepted_values, mandatory = False,):
    check_exists(name, metadata, mandatory)
    if metadata not in accepted_values:
        raise Exception("Keyword \"", name, "\" can only have these values: ", accepted_values)


def get_unique_entries(data):
    entry_set = set()
    for entry in data:
        if entry in entry_set:
            raise Exception("Entry ", entry, "is not unique")
        entry_set.add(entry)
    return entry_set

def validate_no_unkown_values_in_member(component_metadata):
    for key in component_metadata.keys():
        if key not in accepted_component_keys:
            raise Exception("Not allowed key in component")
        
def validate_members(members):
    if members is None:
        return
    
    for member in members:
        member_name = next(iter(member))
        member_attributes = member[member_name]
        check_exists("name", member_attributes["name"])
        check_incompatible_keys("default_value", "is_reference", member_attributes)
        check_incompatible_keys("moved", "is_reference", member_attributes)

def validate_no_unkown_values(metadata, accepted_keys):
    for key in metadata.keys():
        if key not in accepted_keys:
            raise Exception("Not allowed key in component")
   
def validate_component_attributes(component, component_metadata):
    try:
        validate_no_unkown_values(component_metadata, accepted_component_keys)
        validate("component type", component_metadata.get("type"), component_types, True)
        check_exists("needs_cpp", component_metadata.get("needs_cpp"))
        validate_members(component_metadata.get("members"))
    except Exception as e:
        raise Exception("Component: " + component," has caused an error. Error: ", e)
  
def validate_impulse_system_specifics(system_metadata, component_list):
    check_exists("initiator components", system_metadata["initiator_components"])
    for component in system_metadata.get("initiator_components"):
            validate("components", component, component_list, True)

    check_exists("initiator components", system_metadata["victim_components"])
    for component in system_metadata.get("victim_components"):
            validate("components", component, component_list, True)

    check_incompatible_keys("components", "initiator_components", system_metadata)

def validate_system_attributes(system, system_metadata, component_list):
    try:
        validate_no_unkown_values(system_metadata, accepted_system_keys)
        validate("system type", system_metadata.get("type"), system_types, True)
        for component in system_metadata.get("components", []):
            validate("components", component, component_list, True)
        validate_members(system_metadata.get("members"))
        if system_metadata.get("type") == "impulse":
            validate_impulse_system_specifics(system_metadata, component_list)

    except Exception as e:
        raise Exception("System: " + system," has caused an error. Error: ", e)
    
def validate_jsons(component_data, system_data):
    print("> VALIDATING COMPONENT JSON")
    component_list = get_unique_entries(component_data)
    for component in component_list:
        validate_component_attributes(component, component_data[component])
    print("> VALIDATING COMPONENT JSON")
    
    print("> VALIDATING SYSTEM JSON")
    system_list = get_unique_entries(system_data)
    for system in system_list:
        validate_system_attributes(system, system_data[system], component_list)
    print("< VALIDATING COMPONENT JSON")


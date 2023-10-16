def check_exists(name, metadata, mandatory = False,):
    if metadata is None:
        if mandatory == False:
            return 
        else:
            raise Exception("Missing mandatory member: ", name, "")
    
def validate(name, metadata, accepted_values, mandatory = False,):
    check_exists(name, metadata, mandatory)
    if metadata not in accepted_values:
        raise Exception("Member \"", name, "\" can only have these values: ", accepted_values)


def get_unique_components(data):
    component_set = set()
    for component in data:
        if component in component_set:
            raise Exception("Component: ", component, "is not unique")
        component_set.add(component)
    return component_set

def validate_members(members):
    if members is None:
        return
    
    for member in members:
        member_name = next(iter(member))
        member_attributes = member[member_name]
        check_exists("parameter", member_attributes["parameter"])
    
def validate_component_attributes(component, component_metadata):
    try:
        validate("component type", component_metadata.get("type"), ["data", "composite", "event", "impulse"], True)
        check_exists("needs cpp", component_metadata.get("needs_cpp"))
        validate_members(component_metadata.get("members"))
    except Exception as e:
        raise Exception(component," has caused an error. Error: ", e)
  
#TODO validate name of component
def validate_component_json(data):
    ...
    component_list = get_unique_components(data)
    for component in component_list:
        validate_component_attributes(component, data[component])
        

def validate_json(data):
    print("> VALIDATING JSON")
    validate_component_json(data)
   # validate_system_json(data)
    print("< VALIDATING JSON")
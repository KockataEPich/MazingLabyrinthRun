from . import classes
def get_member_list(members):
    if len(members) == 0:
        return []
    
    result = []
    for member in members:
        member_name = next(iter(member))
        member_data = member.get(member_name)

        m = classes.Member()
        m.type = member_name
        m.name = member_data.get("name")
        m.is_parameter = member_data.get("is_parameter", False)
        m.default_value = member_data.get("default_value", "")
        m.moved = member_data.get("moved", False)
        m.is_reference = member_data.get("is_reference", False)
        result.append(m)
    return result

def fetch_components_from_data(data):
    print("> Fetching Components From Data")
    result = {}
    for component, metadata in data.items():
        c = classes.Component()
        c.name = component
        c.var_name = metadata.get("var_name", "")
        c.type = metadata.get("type")
        c.needs_cpp = metadata.get("needs_cpp", False)
        c.includes = metadata.get("includes", [])
        c.members = get_member_list(metadata.get("members", []))
        result[c.name] = c

    print("< Fetching Components From Data")
    return result


def fetch_systems_from_data(data, components):
    print("> Fetching Systems From Data")
    result = {}
    for system, metadata in data.items():
        s = classes.System()
        s.name = system
        s.var_name = metadata.get("var_name", "")
        s.type = metadata.get("type")
        s.includes = metadata.get("includes", [])
        s.members = get_member_list(metadata.get("members", []))
        s.public_functions = metadata.get("public_functions", [])
        s.private_functions = metadata.get("private_functions", [])

        if s.type == "impulse":
            for component in metadata.get("initiator_components"):
                s.initiator_components.append(components[component])
            for component in metadata.get("victim_components"):
                s.victim_components.append(components[component])
            s.components = s.initiator_components + s.victim_components
        
        else:
            for component in metadata.get("components"):
                s.components.append(components[component])

        result[s.name] = s
    print("< Fetching Systems From Data")
    return result

def fetch_data(component_data, system_data):
    components = fetch_components_from_data(component_data)
    systems = fetch_systems_from_data(system_data, components)
    return components, systems



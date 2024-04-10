from . import classes
import os
from copy import copy

def get_member_list(members, owner, owner_type):
    if len(members) == 0:
        return []
    
    result = []
    for member in members:
        member_name = next(iter(member))
        member_data = member.get(member_name)

        m = classes.Member()
        m.owner = owner
        m.owner_type = owner_type
        m.type = member_name
        m.name = member_data.get("name")
        m.is_parameter = member_data.get("is_parameter", False)
        m.default_value = member_data.get("default_value", "")
        m.moved = member_data.get("moved", False)
        m.is_reference = member_data.get("is_reference", False)
        result.append(m)
    return result

def fetch_components_from_data(data, generated_folder):
    result = {}
    for component, metadata in data.items():
        c = classes.Component()
        c.name = component
        c.var_name = metadata.get("var_name", c.name.lower())
        c.type = metadata.get("type")
        c.needs_cpp = metadata.get("needs_cpp", False)
        c.includes = metadata.get("includes", [])
        c.members = get_member_list(metadata.get("members", []), c.name, "Component")
        c.functions = metadata.get("functions", [])
        c.set_relative_path(True)
        c.header_path = "<" + os.path.basename(os.path.basename(os.path.normpath(generated_folder))) + "/components/" + c.relative_path + ">"
        result[c.name] = c

    return result


def fetch_systems_from_data(data, components, generated_folder):
    result = {}
    for system, metadata in data.items():
        s = classes.System()
        s.name = system
        s.var_name = metadata.get("var_name", "")
        s.type = metadata.get("type")
        s.includes = metadata.get("includes", [])
        s.members = get_member_list(metadata.get("members", []), s.name, "System")
        s.public_functions = metadata.get("public_functions", [])
        s.private_functions = metadata.get("private_functions", [])

        if s.type == "impulse":
            for component in metadata.get("initiator_components"):
                component_body = copy(components[component])
                component_body.var_name = "initiator_" + component_body.var_name
                s.initiator_components.append(component_body)

            for component in metadata.get("victim_components"):
                component_body = copy(components[component])
                component_body.var_name = "victim_" + component_body.var_name
                s.victim_components.append(component_body)

            s.components = s.initiator_components + s.victim_components
        
        else:
            for component in metadata.get("components"):
                s.components.append(components[component])

        s.header_path = "<" + os.path.basename(os.path.basename(os.path.normpath(generated_folder))) + "/systems/" + s.get_relative_path(True) + ".h>"
        result[s.name] = s
    return result

def fetch_data(component_data, system_data, generated_folder):
    components = fetch_components_from_data(component_data, generated_folder)
    systems = fetch_systems_from_data(system_data, components, generated_folder)
    return components, systems



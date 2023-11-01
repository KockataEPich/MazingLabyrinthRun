import os.path
from . import write_members
from .  import write_utils

def get_component_includes(system, generated_folder_name):
    generated_top_folder = os.path.basename(os.path.normpath(generated_folder_name))
    result = []
    for component in system.components:
        result.append("#include <" + generated_top_folder + "/components/" + component.get_relative_path(True) + ">")
    return result


def get_interactive_function_signature(type):
    if type == "producer":
        return "update()"
    elif type == "react":
        return "react(const Entity& entity)"
    elif type == "impulse":
        return "exchange_impulse(const Entity& initiator, const Entity& victim)"
    
    return "render()"

def get_handle_components(components, entity_name = ""):
    add_before = "" if entity_name == "" else entity_name + "_"
    result = []
    for component in components:
        if component.type != "basic":
            result.append("ComponentHandle<" + component.name + "Component> " + add_before + component.get_var_name())
    return result

def get_components_as_arguments_in_method(components, entity_name = "", symbol_before = "", is_cpp = False):
    entity_factor = "" if entity_name == "" else entity_name + "_"
    symbol_before = "" if is_cpp else symbol_before 
    result = []
    for component in components:
        if component.type != "basic":
            add_before = component.name + "Component& " if is_cpp else ""
            add_before += entity_factor

            print(add_before)
            result.append(symbol_before + add_before + component.get_var_name())
    return result

def default_body(system, is_cpp_function):
    begining = "for (auto& entity : m_registered_entities) {\n\t\t\t" if system.type == "producer" else ""
    handles_tabs = "\n\t\t\t" if system.type == "producer" else "\n\t\t"
    handles = (";" + handles_tabs).join(get_handle_components(system.components))
    separator = "\n\t\t\t\t" if system.type == "producer" else "\n\t\t\t"
    component_names = add_if_not_empty(separator, ("," + separator).join(get_components_as_arguments_in_method(system.components)))

    cpp_function_name = "for_every_entity" if system.type == "producer" else "react_on_entity"
    
    separator = "\n\t\t" if is_cpp_function else separator

    add_entity_type = "Entity " if is_cpp_function else ""    
    cpp_function = cpp_function_name + "(" + add_entity_type + "entity, " + separator + ("," + separator).join(get_components_as_arguments_in_method(system.components, "", "*", is_cpp_function)) + ");"

    unpack = "m_parent_world->unpack(entity," + component_names + ");"
    if system.type == "producer" and not is_cpp_function:
        cpp_function = "\t" + cpp_function + "\n\t\t}"
        unpack = "\t" + unpack
        
    if not is_cpp_function:
        return f'''{begining}{handles if not is_cpp_function else ""};
        {"" if len(handles) == 0 and not is_cpp_function else unpack}

        {cpp_function}'''

    return f'''{cpp_function}'''

def impulse_body(system, is_cpp_function):
    handles = ";\n\t\t".join(get_handle_components(system.initiator_components, "initiator"))
    has_initiator_components = len(handles) != 0
    
    component_names = add_if_not_empty("\n\t\t\t", ",\n\t\t\t".join(get_components_as_arguments_in_method(system.initiator_components, "initiator")))
    initiator_unpack = "\n\t\tm_parent_world->unpack(initiator," + component_names + ");" if has_initiator_components and not is_cpp_function else ""

    handles_victim = ";\n\t\t".join(get_handle_components(system.victim_components, "victim"))
    has_victim_components = len(handles_victim) != 0

    component_names_victim = add_if_not_empty("\n\t\t\t", ",\n\t\t\t".join(get_components_as_arguments_in_method(system.victim_components, "victim")))
    victim_unpack = "\n\t\tm_parent_world->unpack(victim," + component_names_victim + ");" if has_victim_components and not is_cpp_function else ""

    cpp_function = "" if is_cpp_function else "\t\t" 
    cpp_function += "clash_entities("
    
    if is_cpp_function:
        cpp_function += "Entity "

    cpp_function += "initiator,"
    
    separator_tabs = "\n\t\t" if is_cpp_function else "\n\t\t\t"
    if has_initiator_components:
        cpp_function += separator_tabs + ("," + separator_tabs).join(get_components_as_arguments_in_method(system.initiator_components, "initiator", "*", is_cpp_function)) + ","
        
    cpp_function += separator_tabs 
    if is_cpp_function:
        cpp_function += "Entity "
    cpp_function += "victim"

    if has_victim_components:
        cpp_function += "," + separator_tabs + ("," + separator_tabs).join(get_components_as_arguments_in_method(system.victim_components, "victim", "*", is_cpp_function)) 
    cpp_function += ");"

    if has_initiator_components and has_victim_components:
        handles_victim = "\n\n\t\t" + handles_victim
    
    if is_cpp_function:
        handles = ""
        handles_victim = ""

    if not is_cpp_function:
        return f'''{handles}{";" if has_initiator_components else ""}{initiator_unpack}{handles_victim}{";" if has_victim_components else ""}{victim_unpack}

{cpp_function}'''
    
    return f'''{cpp_function}'''

def get_interaction_function_body(system, is_cpp):
    return f'''{default_body(system, is_cpp) if system.type != "impulse" else impulse_body(system, is_cpp)}'''

def add_if_not_empty(add_infront, string):
    if len(string) != 0:
        return add_infront + string
    return string

def write_file_string(f, system, generated_folder): 
    includes = add_if_not_empty("\n\n", "\n".join(write_utils.get_include_lines(system.includes)))
    component_includes = add_if_not_empty("\n\n", "\n".join(get_component_includes(system, generated_folder)))
    input_params =  add_if_not_empty("\n\t\t", ",\n\t\t".join(write_members.get_members_with_types(system.members, False, False)))
    member_initializations = add_if_not_empty("\n\t\t", ",\n\t\t".join(write_members.get_initialization_members(system.members, False)))

    public_functions = add_if_not_empty("\n\t", "\n\t".join(write_utils.get_function_lines(system.public_functions)))
    interactive_function_name = get_interactive_function_signature(system.type)
    interactive_function = "{\n\t\t" + get_interaction_function_body(system, False) + "\n\t}"
    body_members = add_if_not_empty("\n\t", ";\n\t".join(write_members.get_members_with_types(system.members, True, False)))
    private_functions = add_if_not_empty("\n\t", "\n\t".join(write_utils.get_function_lines(system.private_functions)))

    f.write(f'''// ################## THIS FILE IS GENERATED ##################
#ifndef {system.get_var_name().upper()}_SYSTEM_HEADER
#define {system.get_var_name().upper()}_SYSTEM_HEADER

#include <world/world.h>
#include <component_base/component_handle.h>{component_includes}{includes}

class {system.name}System : public {system.type.capitalize()}System {{
public:
    {system.name}System({input_params}){":" if len(input_params) != 0 else ""}{member_initializations} {{
        {get_component_signatures(system)}
    }}
    {public_functions}

    void {interactive_function_name} override{";" if system.type == "render" else interactive_function}
        
private:{body_members}{";" if len(body_members) != 0 else ""}
    {"" if system.type == "render" else "void " + get_interaction_function_body(system, True)}{private_functions}
}};
#endif
''')

def get_file_name(system, generation_folder):
    return os.path.join(generation_folder, "systems", system.get_relative_path() + ".h")

def write_system_header(system, generation_folder):
    f = open(get_file_name(system, generation_folder), "a+")

    write_file_string(f, system, generation_folder)

    f.close()  

# TODO
def get_cpp_filename(system):
    return os.path.join("code", "src", "system", "systems", system.get_relative_path() + ".cpp")

def write_system_cpp(system):
    cpp_filename = get_cpp_filename(system)
    if os.path.exists(cpp_filename):
        return
    
    f = open(cpp_filename, "a+")
    f.write("#include <generated/systems/" + system.type + "_systems/" + system.get_var_name() + "_system.h>")
    f.write("\n")
   # write_cpp_function(f, system, True, 0)
    f.close()

def write_systems(systems, generation_folder):
    for system in systems:
        write_system_header(system, generation_folder)
        write_system_cpp(system)
        
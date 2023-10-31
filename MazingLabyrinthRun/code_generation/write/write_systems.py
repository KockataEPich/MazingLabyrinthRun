import os.path
from . import write_members
from .  import write_utils

def component_handle_string(component):
    return "ComponentHandle<" + component.name + "Component> " + component.get_var_name()

def component_argument_string_with_tail(component, add_to_back):
    return component.name + "Component& " + add_to_back + component.get_var_name()

def component_argument_string(component):
    return component_argument_string_with_tail(component, "")

def component_initiator_argument_string(component):
    return component_argument_string_with_tail(component, "initiator_")

def component_victim_argument_string(component):
    return component_argument_string_with_tail(component, "victim_")

def component_signature_string(component):
    return ".add_component<" + component.name + "Component>()"

def component_as_params_string(component, add_to_back = ""):
    return add_to_back + component.get_var_name()

def component_as_params_dereferenced_string(component):
    return component_as_params_string(component, "*")

def component_as_params_default_string(component):
    return component_as_params_string(component)

def get_file_name(system, generation_folder):
    return os.path.join(generation_folder, "systems", system.get_relative_path() + ".h")

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
    
def filter_basic_components(components):
    result = []
    for component in components:
        if not component.type == "basic":
           result.append(component)
    return result

def add_code_sequence_list(f, components, tabs, get_string_from_entry, separator = ",", end_of_sequence_closure = ""):
    for i in range(len(components)):
        to_write = write_utils.w_tabs(tabs, get_string_from_entry(components[i]))
        write_utils.write_with_condition(f, to_write, i != len(components) - 1, separator + "\n", end_of_sequence_closure + "\n")

def write_handles_and_unpack(f, components, tabs, entity_name = "entity"):
    filtered_comps = filter_basic_components(components)
    if len(filtered_comps) == 0:
        return
    
    add_code_sequence_list(f, filtered_comps, tabs, component_handle_string, ";", ";")

    f.write(write_utils.w_tabs(tabs, "m_parent_world->unpack(" + entity_name + ",\n"))
    add_code_sequence_list(f, filtered_comps, tabs + 1, component_as_params_default_string, ",", ");")

def write_header(f, system):
    f.write("// ################## THIS FILE IS GENERATED ##################\n")
    f.write("#ifndef " + system.upper() + "_SYSTEM_HEADER\n")
    f.write("#define " + system.upper() + "_SYSTEM_HEADER\n")
    f.write("\n")   

def write_includes(f, system):
    f.write("#include <world/world.h>\n")
    f.write("#include <component_base/component_handle.h>\n")

    for entry in system.includes:
        f.write("#include " + entry + "\n")

    f.write("\n")   

def write_class_initials(f, system):
    f.write("class " + system.name + "System : public " + system.type.capitalize() + "System {\n")
    f.write("public:\n")

def write_component_signatures(f, system):
    if system.type != "impulse":
        f.write(write_utils.w_tabs(2, "m_signature\n"))
        add_code_sequence_list(f, system.components, 3, component_signature_string, "", ";")
        return

    f.write(write_utils.w_tabs(2, "m_signature\n"))
    add_code_sequence_list(f, system.initiator_components, 3, component_signature_string, "", ";")

    f.write("\n")

    f.write(write_utils.w_tabs(2, "m_signature_of_victim\n"))
    add_code_sequence_list(f, system.victim_components, 3, component_signature_string, "", ";")

def write_construtor(f, system):
    if len(write_members.filter_parameters(system.members)) == 0:
        f.write( write_utils.w_tabs(1, system.name + "System() {\n"))
    else:
        f.write( write_utils.w_tabs(1, system.name + "System(\n"))
        write_members.write_non_default_constructor_with_members(f, system.members, False, True)

    write_component_signatures(f, system)
    f.write(write_utils.w_tabs(1, "}\n")) 
        
def write_public_functions(f, system):
    for function in system.public_functions:
        f.write(write_utils.w_tabs(1, function))
        f.write("\n")

def get_signature_components(components):
    result = []
    for component in components:
        result.append(".add_component<" + component.name + "Component>()")
    return result

def default_signatures(system):
    signatures = "\n\t\t\t".join(get_signature_components(system.components))
    return f'''m_signature
            {signatures};'''

def impulse_signatures(system):
    victim_signatures = "\n\t\t\t".join(get_signature_components(system.victim_components))
    initiator_signatures = "\n\t\t\t".join(get_signature_components(system.initiator_components))
    return f'''m_signature
            {initiator_signatures};

        m_signature_of_victim
            {victim_signatures};'''

def get_component_signatures(system):
    return f'''{default_signatures(system) if system.type != "impulse" else impulse_signatures(system)}'''

def write_interactive_function(f, system):
    if system.type == "render":
        f.write(write_utils.w_tabs(1, "void render() override;\n"))
        return
    
    if system.type == "producer":
        f.write(write_utils.w_tabs(1, "void update() override {\n"))
        f.write(write_utils.w_tabs(2, "for (auto& entity : m_registered_entities) {\n"))
        write_handles_and_unpack(f, system.components, 3)

        f.write("\n")

        f.write(write_utils.w_tabs(3, "for_every_entity(entity,\n"))
        add_code_sequence_list(f, filter_basic_components(system.components), 4, component_as_params_dereferenced_string, ",", ");")

        f.write(write_utils.w_tabs(2, "}\n"))
        f.write(write_utils.w_tabs(1, "}\n"))

    if system.type == "react":
        f.write(write_utils.w_tabs(1, "void react(const Entity& entity) override {\n"))
        write_handles_and_unpack(f, system.components, 2)

        f.write("\n")
        
        f.write(write_utils.w_tabs(2, "react_on_entity(entity,\n"))
        add_code_sequence_list(f, filter_basic_components(system.components), 3, component_as_params_dereferenced_string, ",", ");")

        f.write(write_utils.w_tabs(1, "}\n"))

    if system.type == "impulse":
       f.write(write_utils.w_tabs(1, "void exchange_impulse(const Entity& initiator, const Entity& victim) override {\n"))
       write_handles_and_unpack(f, system.initiator_components, 2, "initiator")
       f.write("\n")
       write_handles_and_unpack(f, system.victim_components, 2, "victim")

       f.write("\n")
       f.write("\n")

       f.write(write_utils.w_tabs(2, "do_impulse(initiator,\n"))
       add_code_sequence_list(f, filter_basic_components(system.initiator_components), 3, component_as_params_dereferenced_string, ",", ",") 

       filtered_comps = filter_basic_components(system.victim_components)
       if len(filtered_comps) == 0:
          f.write(write_utils.w_tabs(3, "victim);\n"))
       else:
          f.write(write_utils.w_tabs(3, "victim,\n"))
          add_code_sequence_list(f, filtered_comps, 3, component_as_params_dereferenced_string, ",", ");")
         
       f.write(write_utils.w_tabs(1, "}\n"))       

def write_private_header(f):
    f.write("private:\n")

def write_cpp_function(f, system, is_cpp, tabs):
    if system.type == "render" and not is_cpp:
        return

    to_add = system.name + "System::" if is_cpp else ""
    end = "){ bool TODO = true; }" if is_cpp else ");"

    if system.type == "render":
        f.write("void " + to_add + "render(" + end)

    if system.type == "producer":
        f.write(write_utils.w_tabs(tabs, "void " + to_add + "for_every_entity(\n"))
        f.write(write_utils.w_tabs(tabs + 1, "Entity entity,\n"))
        add_code_sequence_list(f, filter_basic_components(system.components), tabs + 1, component_argument_string, ",", end)
                
    if system.type == "react":
        f.write(write_utils.w_tabs(tabs, "void " + to_add + "react_on_entity(\n"))
        f.write(write_utils.w_tabs(tabs + 1, "Entity entity,\n"))
        add_code_sequence_list(f, filter_basic_components(system.components), tabs + 1, component_argument_string, ",", end)
    
    if system.type == "impulse":
        f.write(write_utils.w_tabs(tabs, "void " + to_add + "do_impulse(\n"))
        f.write(write_utils.w_tabs(tabs + 1, "Entity initiator,\n"))
        add_code_sequence_list(f, filter_basic_components(system.initiator_components), tabs + 1, component_initiator_argument_string, ",", ",")

        filtered_comps = filter_basic_components(system.victim_components)
        if len(filtered_comps) == 0:
           f.write(write_utils.w_tabs(tabs + 1, "Entity victim" + end + "\n"))
        else:
           f.write(write_utils.w_tabs(tabs + 1, "Entity victim,\n"))
           add_code_sequence_list(f, filtered_comps, tabs + 1, component_victim_argument_string, ",", end + "\n")

    f.write("\n")

def write_private_functions(f, system):
    for function in system.private_functions:
        f.write(write_utils.w_tabs(1, function +"\n"))
               
def write_end(f):
    f.write("};")
    f.write("\n")
    f.write("#endif")

def write_system_header(system, generation_folder):
    f = open(get_file_name(system, generation_folder), "a+")

    write_file_string(f, system, generation_folder)
    #write_header(f, system.get_var_name())
    #write_includes(f, system)
    #write_utils.write_component_includes(f, system.components, os.path.basename(os.path.normpath(generation_folder)))
    #write_class_initials(f, system)
    #write_construtor(f, system)
    #write_public_functions(f, system)
    #write_interactive_function(f, system)
    #write_private_header(f)
    #write_members.write_body_members(f, system.members, False)
    #f.write("\n")
    #write_cpp_function(f, system, False, 1)
    #write_private_functions(f, system)
    
    #write_end(f)

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
    write_cpp_function(f, system, True, 0)
    f.close()

def write_systems(systems, generation_folder):
    for system in systems:
        write_system_header(system, generation_folder)
        write_system_cpp(system)
        
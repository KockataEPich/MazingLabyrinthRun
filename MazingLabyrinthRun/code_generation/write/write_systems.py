import os.path
from . import write_members as wb
from .  import write_utils as wu

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


def transform_signature_string(component): return ".add_component<" + component.cpp_name() + ">()"
def get_signature_string(system): return wu.transform_sequence_and_get_string(system.components, transform_signature_string)
def get_initiator_signature_string(system): return wu.transform_sequence_and_get_string(system.initiator_components, transform_signature_string)
def get_victim_signature_string(system): return wu.transform_sequence_and_get_string(system.victim_components, transform_signature_string)

def system_constructor_declaration_string(system):
    return f'''{wu.get_idented_code_block(system, wb.get_parameter_members_string)}'''

def member_initialization_string(system):
    return f'''{wu.get_idented_code_block(system, wb.get_initialized_members_string)}'''

def get_system_constructor_body(system):
    if not system.is_impulse():
        return f'''m_signature
            {wu.get_idented_code_block(system, get_signature_string,)};'''
    
    return f'''m_signature
            {wu.get_idented_code_block(system, get_initiator_signature_string)};
            
        m_signature_of_victim
            {wu.get_idented_code_block(system, get_victim_signature_string)};'''

def cpp_func_params(system):
    if system.is_react(): return "const Entity entity"
    if system.is_impulse(): return "const Entity initiator_entity, const Entity victim_entity"
    return ""

def handle_variatons(component, var_name):
    if component.is_basic(): return ""
    return "ComponentHandle<" + component.name + "Component> " + var_name

def handle_var_name(component):
    if component.is_basic(): return ""
    return "ComponentHandle<" + component.name + "Component> " + component.get_var_name()

def handle_initiator(component): 
    if component.is_basic(): return ""
    return "ComponentHandle<" + component.name + "Component> " + "initiator_" + component.get_var_name()

def handle_victim(component): 
    if component.is_basic(): return ""
    return "ComponentHandle<" + component.name + "Component> " + "victim_" + component.get_var_name()

def default_handles(system): return wu.transform_sequence_and_get_string(system.components, handle_var_name, ";")
def initiator_handles(system): return wu.transform_sequence_and_get_string(system.initiator_components, handle_initiator, ";")
def victim_handles(system): return wu.transform_sequence_and_get_string(system.victim_components, handle_victim, ";")

def data_component_exists(components):
    for component in components:
        if component.is_data(): return True
    return False

def var_name_default_name(component): 
    if component.is_basic(): return ""
    return component.get_var_name()

def var_name_initator(component): 
    if component.is_basic(): return ""
    return "initiator_" + component.get_var_name()


def var_name_victim(component):
    if component.is_basic(): return ""
    return "victim_" + component.get_var_name()


def component_var_names_string(system): return wu.transform_sequence_and_get_string(system.components, var_name_default_name, ",")
def component_var_initiator_var_name_string(system): return wu.transform_sequence_and_get_string(system.initiator_components, var_name_initator, ",")
def component_var_victim_var_name_string(system): return wu.transform_sequence_and_get_string(system.victim_components, var_name_victim, ",")

def transform_to_dereferenced_pointer_component_handle(component): 
    if component.is_basic(): return ""
    return "*" + component.get_var_name()

def dereference_component_string(system): return wu.transform_sequence_and_get_string(system.components, transform_to_dereferenced_pointer_component_handle, ",")

def transform_to_dereferenced_pointer_component_initiator(component): 
    if component.is_basic(): return ""
    return "*initiator_" + component.get_var_name()

def dereference_component_initiator_string(system): return wu.transform_sequence_and_get_string(system.initiator_components, transform_to_dereferenced_pointer_component_initiator, ",")

def transform_to_dereferenced_pointer_component_victim(component): 
    if component.is_basic(): return ""
    return "*victim_" + component.get_var_name()

def dereference_component_string_victim(system): return wu.transform_sequence_and_get_string(system.victim_components, transform_to_dereferenced_pointer_component_victim, ",")

def interactive_functions_body(system):
    if system.is_render(): return ""

    if system.is_impulse():
        initiator_has_data = data_component_exists(system.initiator_components)
        victim_has_data = data_component_exists(system.victim_components)

        initiator_unpack = f'''{wu.set_tab_depth(2)}{wu.get_idented_code_block(system, initiator_handles)};
        m_parent_world->unpack(
            initiator_entity,
            {wu.set_tab_depth(3)}{wu.get_idented_code_block(system, component_var_initiator_var_name_string)}
        );'''
        
        victim_unpack = f'''{wu.set_tab_depth(2)}{wu.get_idented_code_block(system, victim_handles)};
        m_parent_world->unpack(
            victim_entity,
            {wu.set_tab_depth(3)}{wu.get_idented_code_block(system, component_var_victim_var_name_string)}
        );'''
        
        return f'''{wu.set_tab_depth(2)}{{{wu.optional_string(initiator_unpack, initiator_has_data)}{wu.optional_string(victim_unpack, victim_has_data, True)}

        {system.cpp_function_name()}(
            initiator_entity,
            {wu.set_tab_depth(3)}{wu.optional_string_basic(dereference_component_initiator_string(system), initiator_has_data)}{"," if initiator_has_data else ""}

            victim_entity{"," if victim_has_data else ""}{wu.optional_string(dereference_component_string_victim(system), victim_has_data)}
        );
    }}'''

    if system.is_producer():
        return f'''{{
        for (auto& entity : m_registered_entities) {{
            {wu.set_tab_depth(3)}{wu.get_idented_code_block(system, default_handles)};
            m_parent_world->unpack(
                entity,
                {wu.set_tab_depth(4)}{wu.get_idented_code_block(system, component_var_names_string)}
            );
        
            {system.cpp_function_name()}(
                entity,
                {wu.get_idented_code_block(system, dereference_component_string)}
            );
        }}
    }}'''

    if system.is_react():
        return f'''{{
        {wu.set_tab_depth(2)}{wu.get_idented_code_block(system, default_handles)};
        m_parent_world->unpack(
            entity,
            {wu.set_tab_depth(3)}{wu.get_idented_code_block(system, component_var_names_string)}
        );
        
        {system.cpp_function_name()}(
            entity,
            {wu.get_idented_code_block(system, dereference_component_string)}
        );
    }}'''


def transform_component_with_type(component): 
    #print(component.cpp_name())
    if component.is_basic(): return ""
    return component.cpp_name() + "& " + component.get_var_name()
def component_type_declarations(system): wu.transform_sequence_and_get_string(system.components, transform_component_with_type, "")

def initiator_transform_component_with_type(component): 
    #print(component.cpp_name())
    if component.is_basic(): return ""
    return component.cpp_name() + "& initiator_" + component.get_var_name()
def initiator_component_type_declarations(system): wu.transform_sequence_and_get_string(system.initiator_components, initiator_transform_component_with_type, ",")

def victim_transform_component_with_type(component): 
    #print(component.cpp_name())
    if component.is_basic(): return ""
    return component.cpp_name() + "& victim_" + component.get_var_name()
def victim_component_type_declarations(system): wu.transform_sequence_and_get_string(system.victim_components, victim_transform_component_with_type, ",")

def get_cpp_function_declaration(system):
    if not system.is_impulse():
        transformed = wu.transform_sequence(system.components, transform_component_with_type)
        print(transformed, flush=True)

        return f'''void {system.cpp_function_name()}(
        Entity entity,
        {wu.set_tab_depth(2)}{wu.get_string_list(transformed, ",")}
    );'''

    initiator_has_data = data_component_exists(system.initiator_components)
    victim_has_data = data_component_exists(system.victim_components)
    initiator_transformed = wu.transform_sequence(system.initiator_components, initiator_transform_component_with_type)
    victim_transformed = wu.transform_sequence(system.victim_components, victim_transform_component_with_type)
    return f'''void {system.cpp_function_name()}(
        Entity initiator,
        {wu.set_tab_depth(2)}{wu.optional_string_basic(wu.get_string_list(initiator_transformed, ","), initiator_has_data)}{"," if initiator_has_data else ""}
        Entity victim{"," if victim_has_data else ""}{wu.optional_string(wu.get_string_list(victim_transformed, ","))}
    );'''


def write_file_string(f, system): 
    has_params = wb.check_parameter_exists(system.members)
    private_functions = add_if_not_empty("\n\t", "\n\t".join(wu.get_function_lines(system.private_functions)))

    f.write(f'''// ################## THIS FILE IS GENERATED ##################
#ifndef {system.get_var_name().upper()}_SYSTEM_HEADER
#define {system.get_var_name().upper()}_SYSTEM_HEADER

#include <world/world.h>
#include <component_base/component_handle.h>

{wu.get_component_includes_string(system.components)}{wu.optional_string(wu.get_includes_string(system), its_own_logic_block=True)}

class {system.cpp_name()}: public {system.type.capitalize()}System {{
public:
    {system.cpp_name()}({wu.set_tab_depth(2)}{wu.optional_string(system_constructor_declaration_string(system))}){wu.optional_string_basic(":", has_params)}{wu.set_tab_depth(1)}{wu.optional_string(member_initialization_string(system), has_params)}{{
        {wu.set_tab_depth(3)}{get_system_constructor_body(system)}
    }}
    {wu.set_tab_depth(1)}
    {wu.optional_string(wu.get_string_list(system.public_functions))}

    void {system.interactive_function_name()}({cpp_func_params(system)}) override{wu.optional_string_basic(";", system.is_render())} {interactive_functions_body(system)}
        
private:{wu.set_tab_depth(1)}{wu.optional_string(wb.get_members_string(system))}
    {"" if system.type == "render" else get_cpp_function_declaration(system)}{wu.optional_string(wu.get_string_list(system.private_functions))}
}};
#endif
''')

def get_file_name(system, generation_folder):
    return os.path.join(generation_folder, "systems", system.get_relative_path() + ".h")

def write_system_header(system, generation_folder):
    f = open(get_file_name(system, generation_folder), "a+")

    write_file_string(f, system)

    f.close()  

# TODO
def get_cpp_filename(system):
    return os.path.join("code", "src", "system", "systems", system.get_relative_path() + ".cpp")

def write_system_cpp(system):
    cpp_filename = get_cpp_filename(system)
    if os.path.exists(cpp_filename):
        return
    
    f = open(cpp_filename, "a+")
    f.write("#include <generated/systems/" + system.get_relative_path() + "_system.h>")
    f.write("\n")
   # write_cpp_function(f, system, True, 0)
    f.close()

def write_systems(systems, generation_folder):
    for system in systems:
        write_system_header(system, generation_folder)
        wu.tab_depth = 0
        write_system_cpp(system)
        wu.tab_depth = 0

        
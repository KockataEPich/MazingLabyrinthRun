import os.path
from . import write_members as wm
from .  import write_utils as wu

def transform_signature_string(component): return component.cpp_name()

def transform_production_components(component): 
    if component.is_basic(): return ""
    return component.cpp_name()

def get_system_constructor_body(system):
    if len(system.components) == 0: return f''''''
    if not system.is_impulse():
        return f'''m_signature.add_components<
            {wu.process_sequence(system.components, transform_signature_string, ",")}>();'''
    
    return f'''m_signature.add_components<
            {wu.process_sequence(system.initiator_components, transform_signature_string, ",")}>();
            
        m_signature_of_victim.add_components<
            {wu.process_sequence(system.victim_components, transform_signature_string, ",")}>();'''

def cpp_func_params(system):
    if system.is_react(): return "const Entity entity"
    if system.is_impulse(): return "const Entity initiator_entity, const Entity victim_entity, const CollisionInfo& collision_info"
    return ""

def handle_component(component):
    if component.is_basic(): return ""
    return "ComponentHandle<" + component.name + "Component> " + component.var_name

def data_component_exists(components):
    for component in components:
        if component.is_data(): return True
    return False


def transform_to_var_name(component): 
    if component.is_basic(): return ""
    return component.var_name

def transform_dereferenced_variable(component): 
    if component.is_basic(): return ""
    return "*" + component.var_name


def interactive_functions_body(system):
    if system.is_render(): return ""

    if system.is_impulse():
        initiator_has_data = data_component_exists(system.initiator_components)
        victim_has_data = data_component_exists(system.victim_components)

        initiator_unpack = f'''auto [ 
            {wu.set_tab_depth(3)}{wu.process_sequence(system.initiator_components, transform_to_var_name, ",", False)}
        ] = m_game->components->unpack<
            {wu.process_sequence(system.initiator_components, transform_production_components, ",", False)}>(initiator_entity);'''
        
        victim_unpack = f'''auto [ 
            {wu.set_tab_depth(3)}{wu.process_sequence(system.victim_components, transform_to_var_name, ",", False)}
        ] = m_game->components->unpack<
            {wu.process_sequence(system.victim_components, transform_production_components, ",", False)}>(victim_entity);'''
        
        return f'''{wu.set_tab_depth(2)}{{{wu.optional_string(initiator_unpack, initiator_has_data)}{wu.optional_string(victim_unpack, victim_has_data, True)}

        {system.cpp_function_name()}(
            {{initiator_entity, m_game}},{wu.set_tab_depth(3)}{wu.optional_string(wu.process_sequence(system.initiator_components, transform_dereferenced_variable, ",", True))}

            {{victim_entity, m_game}},{wu.optional_string(wu.process_sequence(system.victim_components, transform_dereferenced_variable, ",", True))}

            collision_info
        );
    }}'''

    if system.is_producer():
        return f'''{{
        for (auto& entity : m_registered_entities) {{
            if (std::find(m_registered_entities.begin(), m_registered_entities.end(), entity) == std::end(m_registered_entities)) continue;
            auto [ 
                {wu.set_tab_depth(4)}{wu.process_sequence(system.components, transform_to_var_name, ",", False)}
            ] = m_game->components->unpack<
                {wu.process_sequence(system.components, transform_production_components, ",", False)}>(entity);
        
            {system.cpp_function_name()}(
                {{entity, m_game}},
                {wu.process_sequence(system.components, transform_dereferenced_variable, ",")}
            );
        }}
    }}'''

    if system.is_react():
        return f'''{{
        auto [ 
            {wu.set_tab_depth(3)}{wu.process_sequence(system.components, transform_to_var_name, ",", False)}
        ] = m_game->components->unpack<
            {wu.process_sequence(system.components, transform_production_components, ",", False)}>(entity);
        
        {system.cpp_function_name()}(
            {{entity, m_game}},
            {wu.process_sequence(system.components, transform_dereferenced_variable, ",")}
        );
    }}'''


def transform_component_with_type(component): 
    if component.is_basic(): return ""
    return component.cpp_name() + "& " + component.var_name

def get_cpp_function_declaration(system):
    if system.is_producer() or system.is_react():
        return f'''{system.cpp_function_name()}(
        EntityHandle entity,
        {wu.set_tab_depth(2)}{wu.process_sequence(system.components, transform_component_with_type, ",")}
    )'''
    
    if system.is_impulse():
        initiator_has_data = data_component_exists(system.initiator_components)
        return f'''{system.cpp_function_name()}(
        EntityHandle initiator,
        {wu.set_tab_depth(2)}{wu.optional_string_basic(wu.process_sequence(system.initiator_components, transform_component_with_type, ","), initiator_has_data)}{"," if initiator_has_data else ""}

        EntityHandle victim,{wu.optional_string(wu.process_sequence(system.victim_components, transform_component_with_type, ",", True))}

        const CollisionInfo& collision_info
    )'''

    if system.is_render():
        return f'''{system.cpp_function_name()}()'''
    
def write_file_string(f, system): 
    has_params = wm.check_parameter_exists(system.members)
    
    f.write(f'''// ################## THIS FILE IS GENERATED ##################
#ifndef {system.get_var_name().upper()}_SYSTEM_HEADER
#define {system.get_var_name().upper()}_SYSTEM_HEADER

#include <game.h>
#include <component_base/component_handle.h>
#include <entity_base/entity_handle.h>
#include <utils/collision_utils.h>

{wu.process_sequence(wu.component_header_path_string(system.components), wu.transform_to_include)}{wu.optional_string(wu.process_sequence(system.includes, wu.transform_to_include), its_own_logic_block=True)}

class {system.cpp_name()}: public {system.type.capitalize()}System {{
public:
    {system.cpp_name()}({wu.set_tab_depth(2)}{wu.optional_string(wu.process_sequence(system.members, wm.declare_member_in_constructor, ","))}){wu.optional_string_basic(":", has_params)}{wu.set_tab_depth(1)}{wu.optional_string(wu.process_sequence(system.members, wm.initialize_member_in_constructor, ","), has_params)}{{
        {wu.set_tab_depth(3)}{get_system_constructor_body(system)}
    }}{wu.set_tab_depth(1)}{wu.optional_string(wu.process_sequence(system.public_functions, lambda input: input), its_own_logic_block=True)}

    void {system.interactive_function_name()}({cpp_func_params(system)}) override{wu.optional_string_basic(";", system.is_render())} {interactive_functions_body(system)}
        
private:{wu.set_tab_depth(1)}{wu.optional_string(wu.process_sequence(system.members, wm.initialize_member_in_body, ";", True))}
    {"" if system.type == "render" else "void " + get_cpp_function_declaration(system) + ";"}{wu.optional_string(wu.process_sequence(system.private_functions,  lambda input: input))}
}};
#endif
''')

def get_file_name(system, generation_folder):
    return os.path.join(generation_folder, "systems", system.get_relative_path() + ".h")

def write_system_header(system, generation_folder):
    f = open(get_file_name(system, generation_folder), "a+")
    write_file_string(f, system)
    f.close()  

    wu.set_tab_depth(0)
# TODO
def get_cpp_filename(system):
    return os.path.join("code", "src", "system", "systems", system.get_relative_path() + ".cpp")

def write_system_cpp(system):
    cpp_filename = get_cpp_filename(system)
    if os.path.exists(cpp_filename): return
    f = open(cpp_filename, "a+")

    f.write(f'''#include {system.header_path}
void {system.cpp_name()}::{get_cpp_function_declaration(system)}{{
    // TODO implementation
}}''')

    f.close()

    wu.set_tab_depth(0)

def write_systems(systems, generation_folder):
    for system in systems:
        write_system_header(system, generation_folder)
        
        write_system_cpp(system)
        wu.tab_depth = 0

        
import os.path
from . import write_utils as wu
from . import write_members as wm

def get_file_name(component, generation_folder):
    return os.path.join(generation_folder, "components", component.relative_path)

def data_component_body(component):
    return f'''{wu.set_tab_depth(2)}{component.cpp_name()}(
        {wu.process_sequence(component.members, wm.declare_member_in_constructor, ",")}
    ) : 
        {wu.process_sequence(component.members, wm.initialize_member_in_constructor, ",")} {{}}

    {wu.set_tab_depth(1)}{wu.process_sequence(component.members, wm.initialize_member_in_body, ";", True)}

    {wu.optional_string(wu.process_sequence(component.functions, lambda input: input, ";", True), len(component.functions) != 0)}
'''

def write_file(f, component): 
    f.write(f'''// ################## THIS FILE IS GENERATED ##################
#ifndef {component.get_var_name().upper()}_COMPONENT_HEADER
#define {component.get_var_name().upper()}_COMPONENT_HEADER

#include <component_base/component.h> {wu.optional_string(wu.process_sequence(component.includes, wu.transform_to_include), its_own_logic_block=True)}

struct {component.cpp_name()} : public Component<{component.cpp_name()}> {{
    {component.cpp_name()}() = default; {wu.optional_string(data_component_body(component), component.is_data())}
}};
#endif   
''')
    
def write_header_component(component, generation_folder):
    f=open(get_file_name(component, generation_folder), "a+")
    write_file(f, component)
    f.close()  

def write_component_cpp(component):
    cpp_filename = os.path.join("code", "src", "component", "components", component.get_relative_path() + ".cpp")
    if os.path.exists(cpp_filename): return
    f = open(cpp_filename, "a+")

    f.write(f'''#include {component.header_path}''')
    
def write_components(components, generation_folder):
    for component in components:
        write_header_component(component, generation_folder)
        wu.set_tab_depth(0)
        if component.needs_cpp:
            write_component_cpp(component)
            wu.tab_depth = 0

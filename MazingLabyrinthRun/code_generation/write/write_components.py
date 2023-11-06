import os.path
from . import write_utils
from . import write_members

def get_file_name(component, generation_folder):
    return os.path.join(generation_folder, "components", component.get_relative_path())

def data_component_body(component):
    write_utils.tab_depth = 2
    non_default_constructor = write_utils.get_idented_code_block(component, write_members.get_parameter_members_string)
    member_initializations = write_utils.get_idented_code_block(component, write_members.get_initialized_members_string)
    
    write_utils.tab_depth = 1
    members = write_members.get_members_string(component)
    
    return f'''{component.cpp_name()}(
        {non_default_constructor}
    ) : 
        {member_initializations} {{}}

    {members}
'''

def write_file(f, component): 
    f.write(f'''// ################## THIS FILE IS GENERATED ##################
#ifndef {component.get_var_name().upper()}_COMPONENT_HEADER
#define {component.get_var_name().upper()}_COMPONENT_HEADER

#include <component_base/component.h> {write_utils.optional_string(write_utils.get_includes_string(component), its_own_logic_block=True)}

struct {component.cpp_name()} : public Component<{component.cpp_name()}> {{
    {component.cpp_name()}() = default; {write_utils.optional_string(data_component_body(component), component.is_data())}
}};
#endif   
''')
    
def write_component(component, generation_folder):
    f=open(get_file_name(component, generation_folder), "a+")
    write_file(f, component)
    f.close()  
    
def write_components(components, generation_folder):
    for component in components:
        write_component(component, generation_folder)
        write_utils.tab_depth = 0



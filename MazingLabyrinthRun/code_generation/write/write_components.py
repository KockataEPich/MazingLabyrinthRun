import os.path
from . import write_utils
from . import write_members

def get_file_name(component, generation_folder):
    return os.path.join(generation_folder, "components", component.get_relative_path())

def data_component_body(component):
    write_utils.tab_depth = 1
    non_default_constructor = write_utils.get_idented_code_block(write_utils.component_code_name(component), "(", component, write_members.get_parameter_members_string, ") :")
    member_initializations = write_utils.get_idented_code_block("", "", component, write_members.get_initialized_members_string, "{" + "}")
    members = write_members.get_members_string(component)

    return f'''
{non_default_constructor}{member_initializations}

{members}
'''

def write_file(f, component): 
    f.write(f'''// ################## THIS FILE IS GENERATED ##################
#ifndef {component.get_var_name().upper()}_COMPONENT_HEADER
#define {component.get_var_name().upper()}_COMPONENT_HEADER

#include <component_base/component.h> {write_utils.optional_string(component, write_utils.get_includes_string)}

struct {write_utils.component_code_name(component)} : public Component<{write_utils.component_code_name(component)}> {{
    {write_utils.component_code_name(component)}() = default; {write_utils.optional_string(component, data_component_body, component.is_data())}
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

        
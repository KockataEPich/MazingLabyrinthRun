import os.path
from . import write_utils
from . import write_members

def get_file_name(component, generation_folder):
    return os.path.join(generation_folder, "components", component.get_relative_path())

def data_component_addition(component_in_code, input_params, member_initializations, body_members):
    return f'''{component_in_code}({input_params if len(input_params) != 3 else ""}){":" if len(input_params) != 3 else ""}{member_initializations}{{}}

    {body_members}{";" if len(body_members) != 0 else ""} 
    '''

def write_file(f, component): 
    includes = "\n".join(write_utils.get_include_lines(component.includes))
    input_params = "\n\t\t" + ",\n\t\t".join(write_members.get_members_with_types(component.members, False, True))
    member_initializations = ",\n\t".join(write_members.get_initialization_members(component.members, True))
    body_members = ";\n\t".join(write_members.get_members_with_types(component.members, True, True))
    component_in_code = component.name + "Component"

    f.write(f'''// ################## THIS FILE IS GENERATED ##################
#ifndef {component.get_var_name().upper()}_COMPONENT_HEADER
#define {component.get_var_name().upper()}_COMPONENT_HEADER

#include <component_base/component.h>
{includes}

struct {component_in_code} : public Component<{component_in_code}> {{
    {component_in_code}() = default;
    {data_component_addition(component_in_code, input_params, member_initializations, body_members) if component.type == "data" else ""}
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

        
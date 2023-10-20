import os.path
from write_utils import write_with_condition
from write_utils import w_tabs
import write_members
def get_file_name(component, generation_folder):
    return os.path.join(generation_folder, "components", component.get_relative_path())


def write_header(f, component):
    f.write("// ################## THIS FILE IS GENERATED ##################\n")
    f.write("#ifndef " + component.upper() + "_COMPONENT_HEADER\n")
    f.write("#define " + component.upper() + "_COMPONENT_HEADER\n")
    f.write("\n")    

def write_includes(f, includes):
    f.write("#include <component_base/component.h>\n")
    for entry in includes:
        f.write("#include " + entry + "\n")

    f.write("\n")   

def write_component_body(f, component):
    component_in_code = component.name + "Component"
    f.write("struct " + component_in_code + " : public Component<" + component_in_code +"> {\n")

    f.write(w_tabs(1, component_in_code + "() = default;\n"))
    
    if len(component.members) > 0:
        f.write(w_tabs(1, "explicit " + component_in_code + "(\n"))
        write_members.write_non_default_constructor_with_members(f, component.members)
        write_members.write_body_members(f, component.members)

def write_end(f):
    f.write("};")
    f.write("\n")
    f.write("#endif")

def write_component(component, generation_folder):
    f=open(get_file_name(component, generation_folder), "a+")

    write_header(f, component.get_var_name())
    write_includes(f, component.includes)
    write_component_body(f, component)
    write_end(f)

    f.close()  
    
def write_components(components, generation_folder):
    print("> Writing Components To Disk")
    for component in components:
        write_component(component, generation_folder)
    print("< Writing Components To Disk")

        
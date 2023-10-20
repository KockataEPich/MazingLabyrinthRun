import os.path

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

def write_with_condition(f, to_write, condition, to_add_if_true, to_add_if_false):
    if condition:
        to_write  += to_add_if_true
    else:
        to_write  += to_add_if_false
    f.write(to_write)

def write_non_default_constructor(f, members):
    for i in range(len(members)):
        member = members[i]
        if not member.is_parameter:
            continue

        to_write = "\t\t" +  member.type + "&& " + member.name
        write_with_condition(f, to_write, i == len(members) - 1, ") : \n", ",\n")
        
    for i in range(len(members)):
        member = members[i]
        to_write = ""
        if not member.moved: 
            to_write = "\t\t" + "m_" + member.name + "{" + member.name + "}"
        else:
            to_write = "\t\t" + "m_" + member.name + "{std::move(" + member.name + ")}"
        write_with_condition(f, to_write, i == len(members) - 1, "{" + "};\n", ",\n")

    f.write("\n")    

def write_struct_members(f, members):
    for i in range(len(members)):
        member = members[i]
        to_write = "\t" + member.type + " m_" + member.name
        write_with_condition(f, to_write, member.default_value == "", ";\n", 
                             " = " + member.default_value + ";\n")

def write_component_body(f, component):
    component_in_code = component.name + "Component"
    f.write("struct " + component_in_code + " : public Component<" + component_in_code +"> {\n")

    f.write("\t" + component_in_code + "() = default;\n")
    
    if len(component.members) > 0:
        f.write("\t" + "explicit " + component_in_code + "(\n")
        write_non_default_constructor(f, component.members)
        write_struct_members(f, component.members)

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

        
import os.path

def get_file_name(system):
    return os.path.join(os.path.dirname(os.getcwd()), 
                        "code", "include", "generated", 
                        "systems", "producer_systems", system.name.lower() + "system.h")


def write_header(f, component):
    f.write("// ################## THIS FILE IS GENERATED ##################\n")
    f.write("#ifndef " + component.upper() + "_SYSTEM_HEADER\n")
    f.write("#define " + component.upper() + "_COMPONENT_HEADER\n")
    f.write("\n")   

def write_component_includes(f, system):
    for component : system
    
def write_end(f):
    f.write("};")
    f.write("\n")
    f.write("#endif")

def write_system(system):
    f=open(get_file_name(system), "a+")

    write_header(f, system.name)
    write_component_includes(f, system)
    write_includes(f,system)
    write_end(f)

    f.close()  
    
def write_systems(systems):
    for system in systems:
        write_system(system)

        
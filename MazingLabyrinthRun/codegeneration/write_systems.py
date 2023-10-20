import os.path

def get_file_name(system, generation_folder):
    return os.path.join(generation_folder, "systems", system.get_relative_path())


def write_header(f, system):
    f.write("// ################## THIS FILE IS GENERATED ##################\n")
    f.write("#ifndef " + system.upper() + "_SYSTEM_HEADER\n")
    f.write("#define " + system.upper() + "_SYSTEM_HEADER\n")
    f.write("\n")   

def write_component_includes(f, system, generated_folder_name):
    for component in system.components:
        f.write("#include <" + generated_folder_name + "/components/" + component.get_relative_path(True) + ">\n")

def write_includes(f, system):
    f.write("#include <world/world.h>\n")
    for entry in system.includes:
        f.write("#include " + entry + "\n")

    f.write("\n")   

def write_class_initials(f, system):
    f.write("class " + system.name + " : public " +system.type.capitalize() + "System {\n")
    f.write("public:\n")

def write_construtor(f, system):
    f.write("\t" + system.name + "(")
    #TODO
    if len(system.members) != 0:
        return
    f.write(") {\n")
        

def write_component_signatures(f, system):
    f.write("\t\t" +"m_signature\n")
    for component in system.components:
       f.write("\t\t\t" +".add_component<" + component.name + "Component>()\n") 
    
    f.write("\t;}\n") 

def write_private_function(f, system):
    f.write("private:\n")

    if system.type == "producer":
        f.write("\t void for_every_entry(\n")
        for i in range(len(system.components)):
            if i != len(system.components) - 1:
                f.write("\t\t" + system.components[i].name + "Component& " + system.components[i].get_var_name() + ",\n")
            else:
                f.write("\t\t" + system.components[i].name + "Component& " + system.components[i].get_var_name() + ");\n")
    
def write_interactive_function(f, system):
    if system.type == "producer":
        f.write("\t" + "void update() override {\n")
        f.write("\t\t" + "for (auto& entity : m_registered_entities) {\n")
        for component in system.components:
            f.write("\t\t\t" + "ComponentHandle<" + component.name + "Component> " + component.get_var_name() + ";\n")
        
        f.write("\n")
        f.write("\t\t\t" + "m_parent_world->unpack(entity,\n")
        for i in range(len(system.components)):
            if i != len(system.components) - 1:
                f.write("\t\t\t\t" + system.components[i].get_var_name() + ",\n")
            else:
                f.write("\t\t\t\t" + system.components[i].get_var_name() + ");\n")

        f.write("\n")
        f.write("\t\t\t" + "for_every_entry(\n")
        for i in range(len(system.components)):
            if i != len(system.components) - 1:
                f.write("\t\t\t\t" + "*" + system.components[i].get_var_name() + ",\n")
            else:
                f.write("\t\t\t\t" + "*" + system.components[i].get_var_name() + ");\n")

        f.write("\t\t" + "}\n")
        f.write("\t" + "}\n")

        write_private_function(f, system)

def write_end(f):
    f.write("};")
    f.write("\n")
    f.write("#endif")

def write_system(system, generation_folder):
    f=open(get_file_name(system, generation_folder), "a+")

    write_header(f, system.get_var_name())
    write_includes(f, system)
    write_component_includes(f, system, os.path.basename(os.path.normpath(generation_folder)))
    write_class_initials(f, system)
    write_construtor(f, system)
    write_component_signatures(f, system)
    write_interactive_function(f, system)
    
    # TODO write_members()

    
    write_end(f)

    f.close()  
    
def write_systems(systems, generation_folder):
    print("> Writing Systems To Disk")
    for system in systems:
        write_system(system, generation_folder)
    print("< Writing Systems To Disk")
        
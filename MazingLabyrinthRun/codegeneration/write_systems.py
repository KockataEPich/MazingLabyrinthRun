import os.path
import write_members
from write_utils import w_tabs
from write_utils import write_with_condition

def get_file_name(system, generation_folder):
    return os.path.join(generation_folder, "systems", system.get_relative_path())

def populate_function_with_component_vars(f, components, name = "", symbol_before = ""):
    if name != "":
        f.write(w_tabs(3, name + "(entity,\n"))

    for i in range(len(components)):
            if components[i].type == "basic":
                continue
            to_write =  w_tabs(4, symbol_before + components[i].get_var_name())
            if name == "":
                f.write(to_write + ",\n")
            else:
                write_with_condition(f, to_write, i != len(components) - 1, ",\n", ");\n")

def write_handles(f, components):
    any_written = 0
    for component in components:
            if component.type == "basic":
                continue
            f.write(w_tabs(3, "ComponentHandle<" + component.name + "Component> " + component.get_var_name() + ";\n"))
            any_written += 1
    return any_written
def write_handles_and_unpack(f, components, entity_name = "entity"):
    if write_handles(f, components) == 0:
        return

    f.write(w_tabs(3, "m_parent_world->unpack(" + entity_name + ",\n"))
    populate_function_with_component_vars(f, components)
    f.write(w_tabs(3, ");"))

def write_definiton_function_body(f, components, add_behind = "", signature = ""):
     if signature != "":
        f.write(w_tabs(1, signature + "(Entity entity,\n"))
     for i in range(len(components)):
            if components[i].type == "basic":
                continue
            to_write = w_tabs(2, components[i].name + "Component& " + add_behind + components[i].get_var_name())
            if signature == "":
                f.write(to_write + ",\n")
            else:
                write_with_condition(f, to_write, i != len(components) - 1, ",\n", ");\n")


def write_header(f, system):
    f.write("// ################## THIS FILE IS GENERATED ##################\n")
    f.write("#ifndef " + system.upper() + "_SYSTEM_HEADER\n")
    f.write("#define " + system.upper() + "_SYSTEM_HEADER\n")
    f.write("\n")   

def write_component_includes(f, system, generated_folder_name):
    for component in system.components:
        f.write("#include <" + generated_folder_name + "/components/" + component.get_relative_path(True) + ">\n")

    f.write("\n")   

def write_includes(f, system):
    f.write("#include <world/world.h>\n")
    for entry in system.includes:
        f.write("#include " + entry + "\n")

    f.write("\n")   

def write_class_initials(f, system):
    f.write("class " + system.name + " : public " + system.type.capitalize() + "System {\n")
    f.write("public:\n")

def write_construtor(f, system):
    f.write( w_tabs(1, system.name + "("))
    
    write_members.write_non_default_constructor_with_members(f, system.members)
    f.write(") {\n")

    write_component_signatures(f, system)
    f.write(w_tabs(1, "}\n")) 
        
def write_public_functions(f, system):
    ...

def write_component_signatures(f, system):
    if system.type != "impulse":
        f.write(w_tabs(2, "m_signature\n"))
        for component in system.components:
            f.write(w_tabs(3, ".add_component<" + component.name + "Component>()\n")) 
        f.write(";")
        return

    f.write(w_tabs(2, "m_signature\n"))
    for component in system.initiator_components:
        f.write(w_tabs(3, ".add_component<" + component.name + "Component>()\n")) 
    f.write(";")

    f.write("\n")
    f.write(w_tabs(2, "m_signature_of_victim\n"))
    for component in system.initiator_components:
        f.write(w_tabs(3, ".add_component<" + component.name + "Component>()\n")) 
    f.write(";")

def write_interactive_function(f, system):
    if system.type == "producer":
        f.write(w_tabs(1, "void update() override {\n"))
        f.write(w_tabs(2, "for (auto& entity : m_registered_entities) {\n"))
        write_handles_and_unpack(f, system.components)

        f.write("\n")
        populate_function_with_component_vars(f, system.components, "for_every_entry", "*")

        f.write(w_tabs(2, "}\n"))
        f.write(w_tabs(1, "}\n"))

    if system.type == "react":
        f.write(w_tabs(1, "void react(const Entity& entity) override {\n"))
        write_handles_and_unpack(f, system.components)

        f.write("\n")
        populate_function_with_component_vars(f, system.components, "for_entry", "*")

        f.write(w_tabs(1, "}\n"))

    if system.type == "impulse":
       f.write(w_tabs(1, "void exchange_impulse(const Entity& initiator, const Entity& victim) override {\n"))
       write_handles_and_unpack(f, system.initiator_components, "initiator")
       f.write("\n")
       write_handles_and_unpack(f, system.victim_components, "victim")

       f.write("\n")
       f.write("\n")

       f.write(w_tabs(3, "do_impulse(initiator,\n"))
       populate_function_with_component_vars(f, system.initiator_components, "", "*")
       
       f.write(w_tabs(4, "victim,\n"))
       populate_function_with_component_vars(f, system.victim_components, "", "*")
       f.write(w_tabs(3, ");\n"))
       f.write(w_tabs(1, "}\n"))       

def write_private_header(f):
    f.write("private:\n")

def write_private_functions(f, system):
    if system.type == "producer" or system.type == "react":
        write_definiton_function_body(f, system.components, "", "void for_every_entry")
    
    if system.type == "impulse":
        f.write(w_tabs(1, "void do_impulse(initiator,\n"))
        write_definiton_function_body(f, system.initiator_components, "initiator_", "")
       
        f.write(w_tabs(2, "victim,\n"))
        write_definiton_function_body(f, system.victim_components, "victim_", "")
        f.write(w_tabs(2, ");\n"))
        
def write_end(f):
    f.write("};")
    f.write("\n")
    f.write("#endif")

def write_system_header(system, generation_folder):
    f=open(get_file_name(system, generation_folder), "a+")

    write_header(f, system.get_var_name())
    write_includes(f, system)
    write_component_includes(f, system, os.path.basename(os.path.normpath(generation_folder)))
    write_class_initials(f, system)
    write_construtor(f, system)
    write_public_functions(f, system)
    write_interactive_function(f, system)
    write_private_header(f)
    write_members.write_body_members(f, system.members)
    write_private_functions(f, system)
    
    write_end(f)

    f.close()  

# TODO
def get_cpp_filename(system, generation_folder):
    return os.path.join(generation_folder, "systems", system.get_relative_path())
def write_system_cpp(system, generation_folder):
    ...

def write_systems(systems, generation_folder):
    print("> Writing Systems To Disk")
    for system in systems:
        write_system_header(system, generation_folder)
        write_system_cpp(system, generation_folder)
    print("< Writing Systems To Disk")
        
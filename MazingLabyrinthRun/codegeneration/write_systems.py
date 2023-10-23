import os.path
import write_members
from write_utils import w_tabs
from write_utils import write_with_condition

def component_handle_string(component):
    return "ComponentHandle<" + component.name + "Component> " + component.get_var_name()

def component_argument_string_with_tail(component, add_to_back):
    return component.name + "Component& " + add_to_back + component.get_var_name()

def component_argument_string(component):
    return component_argument_string_with_tail(component, "")

def component_initiator_argument_string(component):
    return component_argument_string_with_tail(component, "initiator_")

def component_victim_argument_string(component):
    return component_argument_string_with_tail(component, "victim_")

def component_signature_string(component):
    return ".add_component<" + component.name + "Component>()"

def component_as_params_string(component, add_to_back = ""):
    return add_to_back + component.get_var_name()

def component_as_params_dereferenced_string(component):
    return component_as_params_string(component, "*")

def component_as_params_default_string(component):
    return component_as_params_string(component)

def get_file_name(system, generation_folder):
    return os.path.join(generation_folder, "systems", system.get_relative_path())

def filter_basic_components(components):
    result = []
    for component in components:
        if not component.type == "basic":
           result.append(component)
    return result

def add_code_sequence_list(f, components, tabs, get_string_from_entry, separator = ",", end_of_sequence_closure = ""):
    for i in range(len(components)):
        to_write = w_tabs(tabs, get_string_from_entry(components[i]))
        write_with_condition(f, to_write, i != len(components) - 1, separator + "\n", end_of_sequence_closure + "\n")

def write_handles_and_unpack(f, components, tabs, entity_name = "entity"):
    filtered_comps = filter_basic_components(components)
    if len(filtered_comps) == 0:
        return
    
    add_code_sequence_list(f, filtered_comps, tabs, component_handle_string, ";", ";")

    f.write(w_tabs(tabs, "m_parent_world->unpack(" + entity_name + ",\n"))
    add_code_sequence_list(f, filtered_comps, tabs + 1, component_as_params_default_string, ",", ");")

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
    f.write("class " + system.name + "System : public " + system.type.capitalize() + "System {\n")
    f.write("public:\n")

def write_construtor(f, system):
    if len(write_members.filter_parameters(system.members)) == 0:
        f.write( w_tabs(1, system.name + "System() {\n"))
    else:
        f.write( w_tabs(1, system.name + "System(\n"))
        write_members.write_non_default_constructor_with_members(f, system.members, True)

    write_component_signatures(f, system)
    f.write(w_tabs(1, "}\n")) 
        
def write_public_functions(f, system):
    for function in system.public_functions:
        f.write(w_tabs(1, function))
        f.write("\n")


def write_component_signatures(f, system):
    if system.type != "impulse":
        f.write(w_tabs(2, "m_signature\n"))
        add_code_sequence_list(f, system.components, 3, component_signature_string, "", ";")
        return

    f.write(w_tabs(2, "m_signature\n"))
    add_code_sequence_list(f, system.initiator_components, 3, component_signature_string, "", ";") 

    f.write("\n")

    f.write(w_tabs(2, "m_signature_of_victim\n"))
    add_code_sequence_list(f, system.victim_components, 3, component_signature_string, "", ";")

def write_interactive_function(f, system):
    if system.type == "producer":
        f.write(w_tabs(1, "void update() override {\n"))
        f.write(w_tabs(2, "for (auto& entity : m_registered_entities) {\n"))
        write_handles_and_unpack(f, system.components, 3)

        f.write("\n")

        f.write(w_tabs(3, "for_every_entry(Entity entity,\n"))
        add_code_sequence_list(f, filter_basic_components(system.components), 4, component_as_params_dereferenced_string, ",", ");")

        f.write(w_tabs(2, "}\n"))
        f.write(w_tabs(1, "}\n"))

    if system.type == "react":
        f.write(w_tabs(1, "void react(const Entity& entity) override {\n"))
        write_handles_and_unpack(f, system.components, 2)

        f.write("\n")
        
        f.write(w_tabs(2, "react_on_entity(Entity entity,\n"))
        add_code_sequence_list(f, filter_basic_components(system.components), 3, component_as_params_dereferenced_string, ",", ");")

        f.write(w_tabs(1, "}\n"))

    if system.type == "impulse":
       f.write(w_tabs(1, "void exchange_impulse(const Entity& initiator, const Entity& victim) override {\n"))
       write_handles_and_unpack(f, system.initiator_components, 2, "initiator")
       f.write("\n")
       write_handles_and_unpack(f, system.victim_components, 2, "victim")

       f.write("\n")
       f.write("\n")

       f.write(w_tabs(2, "do_impulse(initiator,\n"))
       add_code_sequence_list(f, filter_basic_components(system.initiator_components), 3, component_as_params_dereferenced_string, ",", ",") 

       filtered_comps = filter_basic_components(system.victim_components)
       if len(filtered_comps) == 0:
          f.write(w_tabs(3, "victim);\n"))
       else:
          f.write(w_tabs(3, "victim,\n"))
          add_code_sequence_list(f, filtered_comps, 3, component_as_params_dereferenced_string, ",", ");")
         
       f.write(w_tabs(1, "}\n"))       

def write_private_header(f):
    f.write("private:\n")

def write_private_functions(f, system):
    if system.type == "producer":
        f.write(w_tabs(1, "void for_every_entity(Entity entity,\n"))
        add_code_sequence_list(f, system.components, 2, component_argument_string, ",", ");")
                
    if system.type == "react":
        f.write(w_tabs(1, "void react_on_entity(Entity entity,\n"))
        add_code_sequence_list(f, system.components, 2, component_argument_string, ",", ");")
    
    if system.type == "impulse":
        f.write(w_tabs(1, "void do_impulse(Entity initiator,\n"))
        add_code_sequence_list(f, filter_basic_components(system.initiator_components), 2, component_initiator_argument_string, ",", ",")

        filtered_comps = filter_basic_components(system.victim_components)
        if len(filtered_comps) == 0:
           f.write(w_tabs(2, "Entity victim);\n"))
        else:
           f.write(w_tabs(2, "Entity victim,\n"))
           add_code_sequence_list(f, filtered_comps, 2, component_victim_argument_string, ",", ");\n")

    f.write("\n")
 
    for function in system.private_functions:
        f.write(w_tabs(1, function +"\n"))
               
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
    f.write("\n")
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
        
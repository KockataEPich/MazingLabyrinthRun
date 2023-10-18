import json
import validation
import os.path

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

def get_member_name_and_body(members, i):
    return next(iter(members[i])), members[i].get(next(iter(members[i])))


def write_non_default_constructor(f, members):
    for i in range(len(members)):
        [name, body] = get_member_name_and_body(members, i)
        
        if body.get("parameter") is None or not body.get("parameter"):
            continue

        to_write = "\t\t" +  name + "&& " + body["name"]
        write_with_condition(f, to_write, i == len(members) - 1, ") : \n", ",\n")
        
    for i in range(len(members)):
        [name, body] = get_member_name_and_body(members, i)
        to_write = ""
        if body.get("moved") is None: 
            to_write = "\t\t" + "m_" + body["name"] + "{" + body["name"] + "}"
        else:
            to_write = "\t\t" + "m_" + body["name"] + "{std::move(" + body["name"] + ")}"
        write_with_condition(f, to_write, i == len(members) - 1, "{" + "};\n", "\n")

    f.write("\n")    
def write_struct_members(f, members):
    for i in range(len(members)):
        [name, body] = get_member_name_and_body(members, i)
        to_write = "\t" + name + " m_" + body["name"]
        write_with_condition(f, to_write, body.get("default_value") is None, ";\n", 
                             " = " + body.get("default_value", "") + ";\n")

def write_component_body(f,component, body_info):
    component_in_code = component + "Component"
    f.write("struct " + component_in_code + " : public Component<" + component_in_code +"> {\n")

    f.write("\t" + component_in_code + "() = default;\n")
    
    if len(body_info.get("members", [])) > 0:
        f.write("\t" + "explicit " + component_in_code + "(\n")
        write_non_default_constructor(f, body_info.get("members"))
        write_struct_members(f, body_info.get("members"))

def write_end(f):
    f.write("};")
    f.write("\n")
    f.write("#endif")

def write_components(data):
    for component in data:
        save_path = "C:\D\Repositories\MazingLabyrinthRun\MazingLabyrinthRun\codegeneration\generated"
        name_of_file = component.lower() + ".h"
        completeName = os.path.join(save_path, name_of_file)    

        f=open(completeName, "a+")
        write_header(f, component)
        write_includes(f, data[component]["includes"])
        write_component_body(f, component, data[component])
        write_end(f)
        f.close()  
        
def main():
    f = open("components.json")
    try:
        data = json.load(f)
    except:
        raise Exception("JSON LOADING IS NOT GOOD")

    validation.validate_json(data)
    write_components(data)


if __name__ == "__main__":
    main()
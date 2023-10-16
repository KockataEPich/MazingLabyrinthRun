import json
import validation

def write_header(f, component):
    f.write("#ifndef " + component.upper() + "_COMPONENT_HEADER\n")
    f.write("#define " + component.upper() + "_COMPONENT_HEADER\n")
    f.write("\n")    

def write_includes(f, includes):
    f.write("#include <component_base/component.h>\n")
    for entry in includes:
        f.write("#include " + entry + "\n")

    f.write("\n")    

def write_component_body(f,component, body_info):
    component_in_code = component + "Component"
    f.write("struct " + component_in_code + " : public Component<" + component_in_code +"> {\n")

    f.write("\t" + component_in_code + "() = default;\n")
    f.write("\t" + "explicit " + component_in_code + "(\n")

    members = body_info.get("members")
    for i in range(len(members)):
        member_name = next(iter(members[i]))
        member_body = members[i].get(member_name)
        if member_body.get("parameter") is None or not member_body.get("parameter"):
            continue
        
        if i == len(members) - 1:
            f.write("\t\t" + member_name + "&& " + member_body["name"] + ") : \n")
        else:
            f.write("\t\t" + member_name + "&& " + member_body["name"] +",\n")
        
    for i in range(len(members)):
        member_name = next(iter(members[i]))
        member_body = members[i].get(member_name)
  
        if i == len(members) - 1:
            f.write("\t\t" + "m_" + member_body["name"] + "{" + member_body["name"] + "}" + "{" + "};\n")
        else:
            f.write("\t\t" + "m_" + member_body["name"] + "{" + member_body["name"] + "},\n")   

    f.write("\n")    

    for i in range(len(members)):
        member_name = next(iter(members[i]))
        member_body = members[i].get(member_name)
  
        if member_body.get("default_value") is None:
            f.write("\t" + member_name + " m_" + member_body["name"] + ";\n")

        else:
            f.write("\t" + member_name + " m_" + member_body["name"] + " = " + member_body["default_value"] + ";\n")
        

def write_end(f):
    f.write("};")
    f.write("\n")
    f.write("#endif")

def write_components(data):
    for component in data:
        comp_file = component.lower() + ".h"
        f=open(comp_file, "a+")
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
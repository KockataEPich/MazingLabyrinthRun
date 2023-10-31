from . import write_utils

def filter_parameters(members):
    result = []
    for member in members:
        if member.is_parameter:
            result.append(member)
    return result

def get_member_representation(member, in_body, is_component):
    sign = ""
    if member.is_reference:
        sign = "& "
    elif in_body or member.type in ["int", "bool"]:
        sign = " "
    else:
        sign = "&& "
    
    return sign + "" if is_component else "m_"

def get_members_with_types(members, in_body, is_component):
    result = []
    for param in filter_parameters(members):
        result.append(param.type + get_member_representation(param, in_body, is_component) + param.name)
    return result

def get_initialization_members(members, is_component): 
    behind = "" if is_component else "m_"
    result = []
    for param in filter_parameters(members):
        result.append(behind + param.name + "{" + param.name + "}")
    return result


def write_non_default_constructor_with_members(f, members, owner_is_component, constructor_has_body = False):
    filtered_members = filter_parameters(members)
    end_string = "{" + "}" if not constructor_has_body else "{"

    if len(filtered_members) == 0:
        f.write("\t)" + end_string + "\n")
        return 
    
    filtered_members = filter_parameters(members)
    before_member = "" if owner_is_component else "m_";

    for i in range(len(filtered_members)):
        member = filtered_members[i]
        if not member.is_parameter:
            continue

        if member.is_reference:
            to_write = write_utils.w_tabs(2, member.type + "& " + member.name)
        else:
            to_write = write_utils.w_tabs(2, member.type + "&& " + member.name)
        write_utils.write_with_condition(f, to_write, i == len(filtered_members) - 1, ") : \n", ",\n")
        
    #TODO BUG
    for i in range(len(filtered_members)):
        member = filtered_members[i]
        if not member.is_parameter:
            continue
        to_write = ""
        if not member.moved: 
            to_write = write_utils.w_tabs(2, before_member + member.name + "{" + member.name + "}")
        else:
            to_write = write_utils.w_tabs(2, before_member + member.name + "{std::move(" + member.name + ")}")
        write_utils.write_with_condition(f, to_write, i == len(filtered_members) - 1, end_string + "\n", ",\n")

    f.write("\n")    


def write_body_members(f, members, owner_is_component):
    before_member = "" if owner_is_component else "m_"
    for i in range(len(members)):
        member = members[i]
        if member.is_reference:
            to_write = write_utils.w_tabs(1, member.type + "& " + before_member + member.name)
        else:
             to_write = write_utils.w_tabs(1, member.type + " " + before_member + member.name)
        write_utils.write_with_condition(f, to_write, member.default_value == "", ";\n", 
                             " = " + member.default_value + ";\n")
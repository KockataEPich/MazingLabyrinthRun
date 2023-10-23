from write_utils import write_with_condition
from write_utils import w_tabs

def filter_parameters(members):
    result = []
    for member in members:
        if member.is_parameter:
            result.append(member)
    return result

def write_non_default_constructor_with_members(f, members, constructor_has_body = False):
    filtered_members = filter_parameters(members)
    end_string = "{" + "};" if not constructor_has_body else "{"

    if len(filtered_members) == 0:
        f.write("\t)" + end_string + "\n")
        return 
    
    filtered_members = filter_parameters(members)
    
    for i in range(len(filtered_members)):
        member = filtered_members[i]
        if not member.is_parameter:
            continue

        if member.is_reference:
            to_write = w_tabs(2, member.type + "& " + member.name)
        else:
            to_write = w_tabs(2, member.type + "&& " + member.name)
        write_with_condition(f, to_write, i == len(filtered_members) - 1, ") : \n", ",\n")
        
    #TODO BUG
    for i in range(len(filtered_members)):
        member = filtered_members[i]
        if not member.is_parameter:
            continue
        to_write = ""
        if not member.moved: 
            to_write = w_tabs(2, "m_" + member.name + "{" + member.name + "}")
        else:
            to_write = w_tabs(2, "m_" + member.name + "{std::move(" + member.name + ")}")
        write_with_condition(f, to_write, i == len(filtered_members) - 1, end_string + "\n", ",\n")

    f.write("\n")    


def write_body_members(f, members):
    for i in range(len(members)):
        member = members[i]
        if member.is_reference:
            to_write = w_tabs(1, member.type + "& m_" + member.name)
        else:
             to_write = w_tabs(1, member.type + " m_" + member.name)
        write_with_condition(f, to_write, member.default_value == "", ";\n", 
                             " = " + member.default_value + ";\n")
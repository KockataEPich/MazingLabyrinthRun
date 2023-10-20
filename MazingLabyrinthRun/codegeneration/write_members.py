from write_utils import write_with_condition
from write_utils import w_tabs

def write_non_default_constructor_with_members(f, members):
    if len(members) == 0:
        return
    
    for i in range(len(members)):
        member = members[i]
        if not member.is_parameter:
            continue

        if member.is_reference:
            to_write = w_tabs(2, member.type + "& " + member.name)
        else:
            to_write = w_tabs(2, member.type + "&& " + member.name)
        write_with_condition(f, to_write, i == len(members) - 1, ") : \n", ",\n")
        
    for i in range(len(members)):
        member = members[i]
        to_write = ""
        if not member.moved: 
            to_write = w_tabs(2, "m_" + member.name + "{" + member.name + "}")
        else:
            to_write = w_tabs(2, "m_" + member.name + "{std::move(" + member.name + ")}")
        write_with_condition(f, to_write, i == len(members) - 1, "{" + "};\n", ",\n")

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
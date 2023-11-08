def check_parameter_exists(members):
    for member in members: 
        if member.is_parameter: return True
    
    return False

def get_parameter_member_extended_type(member, in_body):
    sign = ""
    if member.is_reference: sign = "&"
    elif in_body or member.type in ["int", "bool"]: sign = ""
    else: sign = "&&"
    return member.type + sign 

def declare_member_in_constructor(member): 
    if not member.is_parameter: return ""
    return get_parameter_member_extended_type(member, False) + " " + member.name


def initialize_member_in_constructor(member): 
    if not member.is_parameter: return ""
    before = "m_" if member.owner_is_system() else ""
    return before + member.name + "{" + member.name + "}"


def initialize_member_in_body(member): 
    before = "m_" if member.owner_is_system() else ""
    return get_parameter_member_extended_type(member, True) + " " + before + member.name


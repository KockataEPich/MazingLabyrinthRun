from tkinter import W
from . import write_utils

def check_parameter_exists(members):
    for member in members: 
        if member.is_parameter: return True
    
    return False

def filter_parameters(members):
    result = []
    for member in members:
        if member.is_parameter:
            result.append(member)
    return result

def get_parameter_member_extended_type(member, in_body):
    sign = ""
    if member.is_reference: sign = "&"
    elif in_body or member.type in ["int", "bool"]: sign = ""
    else: sign = "&&"
    return member.type + sign 








def declare_member_in_constructor(member): 
    if not member.is_parameter: return ""
    return get_parameter_member_extended_type(member, False) + " " + member.name
    
def get_parameter_members_string(entry): return write_utils.transform_sequence_and_get_string(entry.members, declare_member_in_constructor, ",")





def initialize_member_in_constructor(member): 
    if not member.is_parameter: return ""
    before = "m_" if member.owner_is_system() else ""
    return before + member.name + "{" + member.name + "}"

def get_initialized_members_string(entry): return write_utils.transform_sequence_and_get_string(entry.members, initialize_member_in_constructor, ",")




def initialize_member_in_body(member): 
    before = "m_" if member.owner_is_system() else ""
    return get_parameter_member_extended_type(member, True) + " " + before + member.name

def get_members_string(entry): return write_utils.transform_sequence_and_get_string(entry.members, initialize_member_in_body, ";", True)


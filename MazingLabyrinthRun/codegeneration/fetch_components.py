import component_class
def get_member_list(members):
    if len(members) == 0:
        return []
    
    result = []
    for member in members:
        member_name = next(iter(member))
        member_data = member.get(member_name)

        m = component_class.Member()
        m.type = member_name
        m.name = member_data.get("name")
        m.is_parameter = member_data.get("is_parameter", False)
        m.default_value = member_data.get("default_value", "")
        m.moved = member_data.get("moved", False)
        result.append(m)
    return result

def fetch_components_from_data(data):
    result = {}
    for component, metadata in data.items():
        c = component_class.Component()
        c.name = component
        c.type = metadata.get("type")
        c.needs_cpp = metadata.get("needs_cpp")
        c.includes = metadata.get("includes")
        c.members = get_member_list(metadata.get("members"))
        result[c.name] = c
    return result


tab_depth = 0

def set_tab_depth(new_depth): 
    global tab_depth
    tab_depth = new_depth
    return ""

def process_sequence(sequence, transform_function, separator = "", add_separator_at_end = False):
    result = []
    for entry in sequence:
        transformed = transform_function(entry)
        if transformed != "": result.append(transform_function(entry))
    
    if len(result) == 0: return ""
    return (separator + "\n" + ("\t" * tab_depth)).join(result) + (separator if add_separator_at_end else "")


def optional_string_basic(string, predicate):
    if not predicate: return ""
    return string

def optional_string(string, predicate = True, its_own_logic_block = False):
    if not predicate: return ""
    if len(string) == 0: return ""    
    return "\n" + "\t" * tab_depth + string if not its_own_logic_block else "\n\n" + "\t" * tab_depth + string
    
def transform_to_include(project_path): return "#include " + project_path

def component_header_path_string(components):
    result = []
    for component in components: result.append(component.header_path)
    return result









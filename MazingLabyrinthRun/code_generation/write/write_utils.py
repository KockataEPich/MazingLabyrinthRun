tab_depth = 0

def set_tab_depth(new_depth): 
    global tab_depth
    tab_depth = new_depth
    return ""

def get_idented_code_block(entry, get_body_of_idented_code_block_function):
    global tab_depth
    result = ""

    body_string = get_body_of_idented_code_block_function(entry)
    #print(body_string, flush=True)
    if len(body_string) == 0: return "" 
    else:
        result += body_string

    return result

def transform_sequence(sequence, transform_function):
    result = []
    for entry in sequence:
        transformed = transform_function(entry)
        if transformed != "": result.append(transform_function(entry))
    return result


def get_string_list(sequence, separator = "", add_separator_at_end = False):
    if len(sequence) == 0: return ""
    return (separator + "\n" + ("\t" * tab_depth)).join(sequence) + (separator if add_separator_at_end else "")

def transform_sequence_and_get_string(sequence, transform_function, separator = "", add_separator_at_end = False):
    return get_string_list(transform_sequence(sequence, transform_function), separator, add_separator_at_end)

def optional_string_basic(string, predicate):
    if not predicate:
        return ""
    return string

def optional_string(string, predicate = True, its_own_logic_block = False):
    if not predicate:
        return ""
    
    if len(string) > 0:
        return "\n" + "\t" * tab_depth + string if not its_own_logic_block else "\n\n" + "\t" * tab_depth + string
    
    return ""    




def component_code_name(component): return component.name + "Component"





def transform_include_function(include_string): return "#include " + include_string
def get_includes_string(entity) : return transform_sequence_and_get_string(entity.includes, transform_include_function)





def component_header_path_string(components):
    result = []
    for component in components: result.append(component.header_path)
    return result
def get_component_includes_string(components): return transform_sequence_and_get_string(component_header_path_string(components), transform_include_function)









def get_function_lines(functions):
    result = []
    for function in functions:
        result.append(function)
    return result

def write_with_condition(f, to_write, condition, to_add_if_true, to_add_if_false):
    f.write(to_write + (to_add_if_true if condition else to_add_if_false))

def w_tabs(num_of_tabs, string):
    tab_string = ""
    for i in range(num_of_tabs):
        tab_string += "\t"

    return tab_string + string



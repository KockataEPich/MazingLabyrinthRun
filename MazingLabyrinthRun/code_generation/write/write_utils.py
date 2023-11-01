tab_depth = 0

def write_with_condition(f, to_write, condition, to_add_if_true, to_add_if_false):
    f.write(to_write + (to_add_if_true if condition else to_add_if_false))

def w_tabs(num_of_tabs, string):
    tab_string = ""
    for i in range(num_of_tabs):
        tab_string += "\t"

    return tab_string + string

def get_idented_code_block(signature, beginning, entry, get_body_of_idented_code_block_function, end, special_character_in_end = ""):
    return "\t" * tab_depth + signature + get_enclosure_and_body_string(beginning, entry, get_body_of_idented_code_block_function, end, special_character_in_end)

def get_enclosure_and_body_string(beginning, entry, get_body_of_idented_code_block_function, end, special_character_in_end = ""):
    global tab_depth
    tab_depth += 1
    result = beginning + "\n" + get_body_of_idented_code_block_function(entry)
    tab_depth -= 1
    result += "\n" + "\t" * tab_depth + end + special_character_in_end

    return result

def transform_sequence(sequence, transform_function):
    result = []
    for entry in sequence:
        transformed = transform_function(entry)
        if transformed != "": result.append(transform_function(entry))
    return result


def get_string_list(sequence, separator = "", add_separator_at_end = False):
    if len(sequence) == 0: return ""
    tabs_string = "\t" * tab_depth    
    return tabs_string + (separator + "\n" + tabs_string).join(sequence) + (separator if add_separator_at_end else "")

def transform_sequence_and_get_string(sequence, transform_function, separator = "", add_separator_at_end = False):
    return get_string_list(transform_sequence(sequence, transform_function), separator, add_separator_at_end)





def component_code_name(component): return component.name + "Component"





def transform_include_function(include_string): return "#include " + include_string
def get_includes_string(entity) : return transform_sequence_and_get_string(entity.includes, transform_include_function)


def write_component_includes(f, components, generated_folder_name):
    for component in components:
        f.write("#include <" + generated_folder_name + "/components/" + component.get_relative_path(True) + ">\n")

    f.write("\n")
    
def get_function_lines(functions):
    result = []
    for function in functions:
        result.append(function)
    return result

def write_enclosure_of_sequence(f, enclosure, sequence, separator):
    ...
    
def write_line_sequence(f, sequence, separator):
    for entry in sequence:
        f.write_wrows(entry + separator + "\n")

def optional_string(entry, function, predicate = True):
    if not predicate:
        return ""
    
    result = function(entry)
    if len(result) > 0:
        return "\n" + result
    
    return ""    

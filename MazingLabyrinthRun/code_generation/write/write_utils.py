def write_with_condition(f, to_write, condition, to_add_if_true, to_add_if_false):
    f.write(to_write + (to_add_if_true if condition else to_add_if_false))

def w_tabs(num_of_tabs, string):
    tab_string = ""
    for i in range(num_of_tabs):
        tab_string += "\t"

    return tab_string + string

def get_include_lines(includes):
    result = []
    for include in includes:
        result.append("#include " + include)
    return result
    
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

    


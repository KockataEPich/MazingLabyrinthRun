def write_with_condition(f, to_write, condition, to_add_if_true, to_add_if_false):
    f.write(to_write + (to_add_if_true if condition else to_add_if_false))

def w_tabs(num_of_tabs, string):
    tab_string = ""
    for i in range(num_of_tabs):
        tab_string += "\t"

    return tab_string + string
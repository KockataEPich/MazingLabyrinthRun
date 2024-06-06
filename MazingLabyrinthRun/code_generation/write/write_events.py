import os.path
from . import write_utils as wu
from . import write_members as wm

def get_file_name(event, generation_folder):
    return os.path.join(generation_folder, "events", event.get_file_name())

def event_body(event):
    if len(event.members) == 0:
        return  f'''{event.cpp_name()}() = default;'''

    return f'''{wu.set_tab_depth(2)}{event.cpp_name()}(
        {wu.process_sequence(event.members, wm.declare_member_in_constructor, ",")}
    ) : 
        {wu.process_sequence(event.members, wm.initialize_member_in_constructor, ",")} {{}}

    {wu.set_tab_depth(1)}{wu.process_sequence(event.members, wm.initialize_member_in_body, ";", True)}
'''

def write_file(f, event): 
    f.write(f'''// ################## THIS FILE IS GENERATED ##################
#ifndef {event.get_var_name().upper()}_EVENT_HEADER
#define {event.get_var_name().upper()}_EVENT_HEADER

#include <event/event.h> {wu.optional_string(wu.process_sequence(event.includes, wu.transform_to_include), its_own_logic_block=True)}

struct {event.cpp_name()} : public Event {{
    {event_body(event)}
}};
#endif   
''')
    
def write_event_header(event, generation_folder):
    f=open(get_file_name(event, generation_folder), "a+")
    write_file(f, event)
    f.close()  

def write_events(events, generation_folder):
    for event in events:
        write_event_header(event, generation_folder)

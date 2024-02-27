import os.path
class Member:
    def __init__(self):
        self.owner = ""
        self.owner_type = ""
        self.type = ""
        self.name = ""
        self.is_parameter = False
        self.default_value = ""
        self.moved = False
        self.is_reference = False

    def __str__(self):
        return f"{self.name}"
    
    def owner_is_component(self): return self.owner_type == "Component"
    def owner_is_system(self): return self.owner_type == "System"
    

class Component:
    def __init__(self):
        self.name = ""
        self.var_name = ""
        self.type = ""
        self.header_path = ""
        self.relative_path = ""
        self.needs_cpp = False
        self.includes = []
        self.members = []
        self.functions = []
   
    def get_var_name(self):
        return self.name.lower() if self.var_name == "" else self.var_name
    
    def set_relative_path(self, linux_style = False):
        self.relative_path = os.path.join(self.type + "_components", self.get_var_name() + "_component.h")
        if linux_style:
            self.relative_path = self.relative_path.replace("\\","/")
        
    
    def is_basic(self): return self.type == "basic"
    def is_data(self): return self.type == "data"

    def cpp_name(self): return self.name + "Component"
        
class System:
    def __init__(self):
        self.name = ""
        self.var_name = ""
        self.type = ""
        self.header_path = ""
        self.public_functions = []
        self.private_functions = []
        self.components = []
        self.initiator_components = []
        self.victim_components = []
        self.includes = []
        self.members = []
        
   
    def get_var_name(self):
        if self.var_name == "":
            return self.name.lower()
        
        return self.var_name
    
    def get_relative_path(self, linux_style = False):
        end_path = os.path.join(self.type + "_systems", self.get_var_name() + "_system")
        if linux_style:
            return end_path.replace("\\","/")

        return end_path
    
    def cpp_name(self): return self.name + "System"
    def is_producer(self): return self.type == "producer"
    def is_react(self): return self.type == "react"
    def is_impulse(self): return self.type == "impulse"
    def is_render(self): return self.type == "render"
    
    def cpp_function_name(self):
        if self.is_producer(): return "for_every_entity" 
        if self.is_react(): return "react_on_entity" 
        if self.is_impulse(): return "clash_entities" 
        return "render" 
    
    def interactive_function_name(self):
        if self.is_producer(): return "update" 
        if self.is_react(): return "react" 
        if self.is_impulse(): return "exchange_impulse" 
        return "render" 
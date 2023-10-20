import os.path
class Member:
    def __init__(self):
        self.type = ""
        self.name = ""
        self.is_parameter = False
        self.default_value = ""
        self.moved = False
        self.is_reference = False

    def __str__(self):
        return f"{self.name}"
    

class Component:
    def __init__(self):
        self.name = ""
        self.var_name = ""
        self.type = ""
        self.needs_cpp = False
        self.includes = []
        self.members = []
   
    def get_var_name(self):
        return self.name.lower() if self.var_name == "" else self.var_name
    
    def get_relative_path(self, linux_style = False):
        end_path = os.path.join(self.type + "_components", self.get_var_name() + "_component.h")
        if linux_style:
            return end_path.replace("\\","/")
        
        return end_path
        
class System:
    def __init__(self):
        self.name = ""
        self.var_name = ""
        self.type = ""
        self.extra_functions = []
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
        end_path = os.path.join(self.type + "_systems", self.get_var_name() + "_system.h")
        if linux_style:
            return end_path.replace("\\\\","/")

        return end_path
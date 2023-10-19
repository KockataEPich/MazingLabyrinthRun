class Member:
    def __init__(self):
        self.type = ""
        self.name = ""
        self.is_parameter = False
        self.default_value = ""
        self.moved = False

    def __str__(self):
        return f"{self.name}"
    

class Component:
    def __init__(self):
        self.name = ""
        self.type = ""
        self.needs_cpp = False
        self.includes = []
        self.members = []
   
    def __str__(self):
        return f"{self.name}"
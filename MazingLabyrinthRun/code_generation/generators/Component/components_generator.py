import os
import utils.json.json_utils

def load_data(file_name):
    f = open(file_name)
    try:
        data = json.load(f)
    except:
        raise Exception("JSON LOADING IS NOT GOOD IN " + file_name)
    return data

class Generator:
    json_data_filename = ""

    def generate(self):
        self.prepare_directory_structure()
        data = load_data(json_data_filename)
        self.validate_data(data)
        processed_data = process_data(data)
        self.write_data(processed_data)

    def prepare_directory_structure():
        raise NotImplementedError
    
    def process_data(data):
        raise NotImplementedError
    
    def validate_data(data):
        raise NotImplementedError
    
    def write_data(processed_data):
        raise NotImplementedError


    
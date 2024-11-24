#!/usr/bin/python

from sys import argv
from os import chdir, mkdir

def snake_case2PascalCase(snake):
    i = 1
    camel = snake[0].upper()
    while i < len(snake):
        c = snake[i].lower()
        if c == "_":
            i += 1
            c = snake[i].upper()
        camel += c
        i += 1
    return camel

def is_file_exist(hpp):
    try:
        open(hpp, "r").close()
        return True
    except:
        return False

def get_hpp_file(header_title, class_name):
    return f"""\
#ifndef {header_title}
#define {header_title}

class {class_name} {{
private:
public:
    {class_name}();
    ~{class_name}();
}};

#endif
"""

def get_cpp_file(all_path, class_name):
    return f"""\
#include "{all_path}.hpp"

{class_name}::{class_name}() {{}}

{class_name}::~{class_name}() {{}}
"""

def create_dirs(all_path):
    if "/" not in all_path:
        return
    parts = all_path.split("/")[:-1]
    current = ""
    for part in parts:
        current += part+"/"
        try:
            mkdir("include/"+current)
            print("directory created: include/"+current)
        except FileExistsError:
            pass
        try:
            mkdir("src/"+current)
            print("directory created: src/"+current)
        except FileExistsError:
            pass

def main():
    all_path = argv[1]
    file_name = all_path.split("/")[-1]
    header_title = file_name.upper()+"_HPP"
    class_name = snake_case2PascalCase(file_name)
    hpp = "include/"+all_path.lower()+".hpp"
    cpp = "src/"+all_path.lower()+".cpp"
    create_dirs(all_path)
    if is_file_exist(hpp):
        print("file already exist: "+hpp)
    else:
        with open(hpp, "w") as file:
            print(get_hpp_file(header_title, class_name), file=file, end="")
        print("file created:", hpp)
    if is_file_exist(cpp):
        print("file already exist: "+cpp)
    else:
        with open(cpp, "w") as file:
            print(get_cpp_file(all_path, class_name), file=file, end="")
        print("file created:", cpp)

if __name__ == "__main__":
    main()

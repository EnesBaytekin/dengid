#!/usr/bin/python

from sys import argv

def main():
    argv.pop(0)
    while len(argv):
        var_type = argv.pop(0)
        var_name = argv.pop(0)
        
        length = max(len(var_type), 4)

        print(f"""\
{"void".ljust(length)} set_{var_name}({var_type} new_{var_name}) {{ {var_name} = new_{var_name}; }}
{var_type.ljust(length)} get_{var_name}() {{ return {var_name}; }}
""")

if __name__ == "__main__":
    main()

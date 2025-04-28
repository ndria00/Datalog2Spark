import os
import platform
import subprocess
import re
import argparse

def get_current_folder():
    return os.path.basename(os.getcwd())

def current_folder_is_project_folder():
    if get_current_folder() == 'Datalog2Spark':
        return True
    return False

def execute_command(cmd, return_out = False):
    try:
        print(f"\tExecuting: {cmd}")
        # Run the command and capture output
        result = subprocess.run(cmd, shell=True, 
                                #stdout=subprocess.PIPE, 
                                stderr=subprocess.PIPE, 
                                text=True)
        if not result.stdout is None:
            print(result.stdout)
    except Exception as e:
        print(f"Error executing command {cmd} {str(e)}")
        exit(1)


def main():
    if not current_folder_is_project_folder():
        print(f"This script must be run from inside the 'Datalog2Spark' directory... Current directory: {get_current_folder()}")
        exit(1)

    clean_command : str = "make clean"
    make_command : str = "make -j "

    parser = argparse.ArgumentParser(prog = "Datalog2Spark-wrapper", description = "Compiles or executes a Datalog2Spark solver\n")
    subparsers = parser.add_subparsers(dest='action')

    compile_parser = subparsers.add_parser('compile', help="Compile a Datalog2Spark solver", aliases=['compile'])
    compile_parser.add_argument('--comp', help="path to a file containing rules that will be compiled\n", required=True)

    execute_parser = subparsers.add_parser('execute', help="Execute a Datalog2Spark solver", aliases=['execute'])
    execute_parser.add_argument('--jar', help="path to compiled jar(default jar location if not specified)\n", default="")
    execute_parser.add_argument('--executors', help="number of executors\n", default="*")
    execute_parser.add_argument('--instance', help="path to an instance folder\n", required=True)
    execute_parser.add_argument('--output', help="path to output folder\n", required=True)

    
    args = parser.parse_args()
    
    #project setup
    compiler_lib = "ProASP/Compiler/lib"
    antlr_lib = f"{compiler_lib}/libantlr4-runtime.a"
    antlr_lib_macos = f"{compiler_lib}/macos-libantlr4-runtime.a"
    antlr_lib_linux = f"{compiler_lib}/linux-libantlr4-runtime.a"
    if not os.path.isfile(antlr_lib):
       
        if platform.system() == "Darwin":
            execute_command(f"cp {antlr_lib_macos} {antlr_lib}")
        else:
            execute_command(f"cp {antlr_lib_linux} {antlr_lib}")

    if args.action == 'compile':
        execute_command(f"{clean_command} -C ProASP/Compiler/")

        print("Doing make:")
        execute_command(make_command + " -C ProASP/Compiler ")
        print("Compiler ready... Compiling solver:")

        print("Compiling Datalog2Spark solver:")

        compile_command : str = f"./ProASP/Compiler/output/main {args.comp}"
        execute_command(compile_command)
        
        execute_command(f"{clean_command} -C ProASP/SparkApplication")
        
        print("Compiling custom solver:")
        compile_command : str = f"{make_command} -C ProASP/SparkApplication"
        execute_command(compile_command)

    elif args.action == 'execute':
        print(f'Executing over instance {args.instance}')
        #default jar
        #ProASP/SparkApplication/Datalog2Spark-jar-with-dependencies.jar
        jar_path = "ProASP/SparkApplication/target/Datalog2Spark-jar-with-dependencies.jar"
        if args.jar != "":
            jar_path = args.jar
        execute_command(f'spark-submit --master local[{args.executors}] {jar_path} {args.instance} {args.output}')
    else:
        print("No command selected")
        parser.print_help()

if __name__ == "__main__":
    main()
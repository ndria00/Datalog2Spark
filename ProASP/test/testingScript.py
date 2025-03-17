import os
import subprocess
import re

def assert_current_folder():
    current_dir = os.path.basename(os.getcwd())
    
    if current_dir != 'ProASP':
        raise RuntimeError(
            f"This script must be run from inside the 'ProASP' directory. "
            f"Current directory: {current_dir}"
        )

def list_folders(path):
    try:
        # Get all entries in the directory
        entries = os.listdir(path)
        
        # Filter out only directories
        folders = [entry for entry in entries if os.path.isdir(os.path.join(path, entry))]
        
        return folders
    except FileNotFoundError:
        print(f"Error: The path '{path}' does not exist.")
        return []
    except PermissionError:
        print(f"Error: Permission denied to access '{path}'.")
        return []

def list_files(path):
    try:
        # Get all entries in the directory
        entries = os.listdir(path)
        
        # Filter out only files
        files = [entry for entry in entries if os.path.isfile(os.path.join(path, entry))]
        
        return files
    except FileNotFoundError:
        print(f"Error: The path '{path}' does not exist.")
        return []
    except PermissionError:
        print(f"Error: Permission denied to access '{path}'.")
        return []

def execute_command(cmd):
    try:
        
        print(f"\tExecuting: {cmd}")
        
        # Run the command and capture output
        result = subprocess.run(cmd, shell=True, 
                                stdout=subprocess.PIPE, 
                                stderr=subprocess.PIPE, 
                                text=True)
    except Exception as e:
        print(f"Error executing command {cmd}")


def execute_clingo(cmd):
    try:
        clingo_output : set = set()
        print(f"\tExecuting: {cmd}")
        result = subprocess.run(cmd, shell=True, 
                                stdout=subprocess.PIPE, 
                                stderr=subprocess.PIPE, 
                                text=True)
        if result.stdout:
            clingo_out = result.stdout
            clingo_out_filtered = re.search('Answer: 1\n(.*?)\n', clingo_out)
            #UNSAT or error
            if clingo_out_filtered is None:
                return clingo_out
            else:
                #print("Clingo output filtered : ", clingo_out_filtered.group(1))
                tuples = re.split("\s", clingo_out_filtered.group(1))
                for t in tuples:
                    clingo_output.add(t)
        return clingo_output
    except Exception as e:
        print(f"Error executing command {cmd}")
        exit(1)

def execute_spark(cmd, input_folder_path, output_folder_path):
    try:
        spark_output : set = set()
        print(f"\tExecuting: {cmd}")
        result = subprocess.run(cmd, shell=True, 
                                stdout=subprocess.PIPE, 
                                stderr=subprocess.PIPE, 
                                text=True)
        
        output_folders = list_folders(output_folder_path)
        for folder in output_folders:
            # print(f"\tReading output partitions from {output_folder_path}/{folder}")
            partitions = list_files(f"{output_folder_path}/{folder}")
            for partition in partitions:
                #ingore _SUCCESS _FAIL ...
                if partition.startswith("part-"):
                    # print(f"\tOpening partition file {output_folder_path}/{folder}/{partition}")
                    with open(f"{output_folder_path}/{folder}/{partition}") as input_file:
                        for line in input_file: 
                            line = line.rstrip("\n")
                            tuple : str = ",".join(line.split(";"))
                            spark_output.add(f"{folder}({tuple})")
        
        input_files = list_files(f"{input_folder_path}")
        for file in input_files:
            with open(f"{input_folder_path}/{file}") as input_file:
                predicate_name = file.split(".")[0]
                for line in input_file:
                    line_c = line.rstrip("\n")
                    tuple : str = ",".join(line_c.split(";"))
                    spark_output.add(f"{predicate_name}({tuple})")
        
        
        return spark_output
    except Exception as e:
        print(f"Error executing command {cmd}")
        exit(1)



def main():
    # List folders
    folders = list_folders("test/encodings")
    clean_command : str = "make clean"
    make_command : str = "make -j"
    make_jar : str = "make"
    output_test : str = "outputTestFolder"
    input_spark_folder : str = "inputSpark"
    input_clingo_folder : str = "inputClingo"
    instance_folder : str = "test/instances"
    encoding_folder : str = "test/encodings"
    # If folders are found, execute command for each
    if folders:
        for folder in folders:
            print(f"Executing tests for {folder}")
            original_dir = os.getcwd()
            os.chdir("Compiler")
            print("Doing clean:")
            execute_command(clean_command)
            print("Doing make:")
            execute_command(make_command)
            print("Compiling solver:")
            compile_command : str = f"./output/main ../{encoding_folder}/{folder}/{folder}.lp"
            execute_command(compile_command)
            os.chdir(original_dir)

            original_dir = os.getcwd()
            os.chdir("SparkApplication")
            print("Doing nvm package")
            execute_command(make_jar)
            
            os.chdir(original_dir)
            instances = list_folders(f"{instance_folder}/{folder}")
            for instance in instances:
                execute_spark_command : str = f"make -C SparkApplication run ARGS=\"../{instance_folder}/{folder}/{instance}/{input_spark_folder} ../test/{output_test}\""
                execute_clingo_command : str = f"clingo {encoding_folder}/{folder}/{folder}.lp {instance_folder}/{folder}/{instance}/{input_clingo_folder}/*"
                execute_command(f"rm -rf test/{output_test}/*\n")
                spark_output = execute_spark(execute_spark_command, f"{instance_folder}/{folder}/{instance}/{input_spark_folder}", f"test/{output_test}")
                clingo_output = execute_clingo(execute_clingo_command)

                print(f"Spark produced {len(spark_output)} tuples")
                print(f"Clingo produced {len(clingo_output)} tuples")

                if len(clingo_output) != len(spark_output):
                    print("Spark output ")
                    for t in spark_output:
                        print(t, sep=" ")
                    
                    print("clingo output ")
                    for t in clingo_output:
                        print(t, sep=" ")
                    print(f"Test failed on instance {folder}/{instance}")
                    exit(1)
                    
                for tuple in spark_output:
                    if not tuple in clingo_output:
                        print(f"Test failed on instance {folder}/{instance}")
                        exit(1)
                for tuple in clingo_output:
                    if not tuple in spark_output:
                        print(f"Test failed on instance {folder}/{instance}")
                        exit(1)
                print(f"Test passed on instance {folder}/{instance}")
            execute_command(f"rm -rf test/{output_test}/*\n")
        print("")
        
        print("All tests passed")
    else:
        print("No folders found to process.")
        

if __name__ == "__main__":
    main()
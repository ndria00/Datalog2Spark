
# Datalog2Spark 
In oder to use Datalog2Spark please clone this repository and then follow the instructions.

## Compile a Spark solver for Datalog
To compile a Spark solver for Datalog using Datalog2park you need an encoding file containing the rules that should be compiled.
The encoding file should contain both rules and type directives (if needed).
For predicates whose terms can be safely treated as strings, type directies can be omitted.

Compilation and execution of Datalog2Spark solvers can be done via the utility script Datalog2Spark.py


To compile a Datalog2Spark solver run the following command:
```
python3 Datalog2Spark.py compile --comp path_to_encoding_folder/encoding.l
```
Once the compilation is done, the compiler can be used to compile a custom solver by executing:



## Execute an ad-hoc Spark solver for Datalog
For executing a Datalog2Spark solver it is required to have an installed version of Spark(the version we used in the experiments is Spark 3.5.4). 
To install Spark please refer to: https://spark.apache.org/downloads.html

To execute the compiled solver over an arbitrary instance run:
```
python3 Datalog2Spark.py execute --jar path_to_jar/solver.jar --executors n --instance path_to_instance_folder/ --output path_to_output_folder/
```
Where n is the nmber of executor threads with which spark is executed (if omitted spark is executed with --master local[*]), and --jar is the path to the compiled jar (if omitted the path to which the jar is created by default in the project is taken)

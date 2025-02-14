.DEFAULT_GOAL := all

.PHONY: all clean

# Directory to clean (modify this to match your project structure)
BUILD_DIR = target/

# Default target - runs mvn package
all:
	@echo "Building project with Maven..."
	mvn package
	@echo "Build complete."

# Run target - executes the jar file with provided arguments
run:
	@echo "Running with instance $(ARGS)"
	java -jar $(BUILD_DIR)/SparkApplication-0.0.1-SNAPSHOT-jar-with-dependencies.jar $(ARGS)

# Clean target - removes build artifacts
clean:
	@echo "Cleaning build directory..."
	@if [ -d "$(BUILD_DIR)" ]; then \
		rm -rf $(BUILD_DIR)/* ; \
		echo "Cleaned $(BUILD_DIR) directory." ; \
	else \
		echo "Directory $(BUILD_DIR) does not exist." ; \
	fi

help:
	@echo "Available commands:"
	@echo "  make       - Builds the project using mvn package"
	@echo "  make all   - Same as above"
	@echo "  make run ARGS = \"path_to_intance_folder\""
	@echo "  make clean - Removes all files from target directory"
	@echo "  make help  - Shows this help message"

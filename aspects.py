import os
import shutil
import regex as re

# Function to add logging to a function
def add_logging_to_function(match):
    function_signature = match.group(1)
    return_type = match.group(2)
    namespace = match.group(3)
    function_name = match.group(4)
    function_body = match.group(5)
    
    modified_body = f"""
    std::cout << "Entering {return_type} {namespace}::{function_name}" << std::endl;
    {function_body}
    std::cout << "Exiting {return_type} {namespace}::{function_name}" << std::endl;"""
    return f"{function_signature} {{ {modified_body} }}"

# Function to process a single .cpp file
def process_cpp_file(file_path):
    with open(file_path, 'r') as file:
        content = file.read()

    # Regex to match function definitions
    function_pattern = re.compile(r'((?:(void)\s+)?(?:(Arrow)::)([^(]+)\([^)]*\)[^{]*)\{([^{}]*(?:\{(?5)\}[^{}]*)*)\}')
    
    modified_content = function_pattern.sub(add_logging_to_function, content)

    with open(file_path, 'w') as file:
        file.write(modified_content)

def copy_project(source_dir, dest_dir):
    # List of directories and files to include
    include_paths = [
        'app/app.pro',
        'tests/main.cpp', 'tests/tests.pro', 'tests/LevelSceneGeneration.cpp', 'tests/LevelSceneGeneration.h', 'tests/PlayerInteractionsTests.cpp', 'tests/PlayerInteractionsTests.h', 'tests/TestsGlobal.cpp', 'tests/TestsGlobal.h', 'tests/WindowGenerationTests.cpp', 'tests/WindowGenerationTests.h',
        'Joffrey_s_Journey.pro'
    ]

    # Include entire directories
    include_directories = ['include', 'src', 'data', 'fonts', 'resources']

    for f in os.listdir(source_dir):
        if os.path.isdir(f):
            if f in include_directories:
                shutil.copytree(os.path.join(source_dir, f), os.path.join(dest_dir, f))
            else:
                for f2 in os.listdir(f):
                    path = os.path.join(f, f2)
                    if path in include_paths:
                        if not os.path.exists(os.path.join(dest_dir, f)):
                            os.mkdir(os.path.join(dest_dir, f))
                        shutil.copy(os.path.join(source_dir, path), os.path.join(dest_dir, path))
        else:
            if f in include_paths:
                shutil.copy(os.path.join(source_dir, f), os.path.join(dest_dir, f))

# Function to process the project directory
def process_project(src_dir, dest_dir):
    # Delete the destination directory if it exists
    if os.path.exists(dest_dir):
        shutil.rmtree(dest_dir)
    
    # Copy only the specified directories and files
    copy_project(src_dir, dest_dir)

    # Process all .cpp files in the src directory of the copied project
    src_code_dir = os.path.join(dest_dir, 'src')
    for root, _, files in os.walk(src_code_dir):
        for file in files:
            if file.endswith('.cpp'):
                process_cpp_file(os.path.join(root, file))

if __name__ == "__main__":
    src_directory = '.'  # Original project directory
    dest_directory = './modified_project'  # Directory for the modified project

    process_project(src_directory, dest_directory)

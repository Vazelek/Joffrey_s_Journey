import os
import shutil
import regex as re

def load_aspects(aspect_dir):
    aspects = {}
    for aspect_file in os.listdir(aspect_dir):
        if aspect_file.endswith('.acpp'):
            with open(os.path.join(aspect_dir, aspect_file), 'r') as file:
                content = file.read()

                aspects_classes = re.compile(
                    r'aspect\s+(?P<aspect_name>\w+)\s*\{(?P<aspect_content>[^{}]*(?:\{(?2)\}[^{}]*)*)\}',
                    re.DOTALL
                )

                for match in aspects_classes.finditer(content):
                    aspect_name = match.group('aspect_name')
                    aspects[aspect_name] = {}

                    aspect_content = match.group('aspect_content')

                    aspect_pattern_regex = re.compile(
                        r'pattern\s+"(?P<pattern_name>[^"]+)"\s*:\s*"(?P<return_type>[^"]*)"\s*"(?P<namespace>[^"]*)"\s*"(?P<function_name>[^"]*)";\s*',
                        re.DOTALL
                    )
                    for match_pattern in aspect_pattern_regex.finditer(aspect_content):
                        pattern_name = match_pattern.group('pattern_name')
                        aspects[aspect_name][pattern_name] = {
                            'return_type': match_pattern.group('return_type'),
                            'namespace': match_pattern.group('namespace'),
                            'function_name': match_pattern.group('function_name')
                        }

                    for pattern_name in aspects[aspect_name]:
                        aspect_pattern_functions_regex = re.compile(
                            pattern_name + r'::define\s*{(?P<define_code>[^{}]*(?:\{(?1)\}[^{}]*)*)}',
                            re.DOTALL
                        )
                        
                        for match_pattern in aspect_pattern_functions_regex.finditer(aspect_content):
                            aspects[aspect_name][pattern_name]['define_code'] = match_pattern.group('define_code')

                        aspect_pattern_functions_regex = re.compile(
                            pattern_name + r'::before\s*{(?P<before_code>[^{}]*(?:\{(?1)\}[^{}]*)*)}',
                            re.DOTALL
                        )
                        
                        for match_pattern in aspect_pattern_functions_regex.finditer(aspect_content):
                            aspects[aspect_name][pattern_name]['before_code'] = match_pattern.group('before_code')

                        aspect_pattern_functions_regex = re.compile(
                            pattern_name + r'::after\s*{(?P<after_code>[^{}]*(?:\{(?1)\}[^{}]*)*)}',
                            re.DOTALL
                        )
                        
                        for match_pattern in aspect_pattern_functions_regex.finditer(aspect_content):
                            aspects[aspect_name][pattern_name]['after_code'] = match_pattern.group('after_code')

    return aspects

def apply_aspects_to_function(match, before_code, after_code, aspect_name, pattern_name):
    function_signature = match.group(1)
    return_type = match.group(2)
    namespace = match.group(3)
    function_name = match.group(4)
    function_body = match.group(5)

    before_code = before_code.replace('$$return_type$$', return_type).replace('$$namespace$$', namespace).replace('$$function_name$$', function_name).replace('$$pattern_name$$', pattern_name).replace('$$aspect_name$$', aspect_name)
    after_code = after_code.replace('$$return_type$$', return_type).replace('$$namespace$$', namespace).replace('$$function_name$$', function_name).replace('$$pattern_name$$', pattern_name).replace('$$aspect_name$$', aspect_name)
    
    modified_body = ""

    if before_code != "":
        modified_body += f"""
\t/* ########## BEGIN - Code added by aspect {aspect_name} - {pattern_name} (before) ########## */
\t{before_code.lstrip().rstrip()}
\t/* ############ END - Code added by aspect {aspect_name} - {pattern_name} (before) ########## */
"""
    modified_body += function_body

    if after_code != "":
        modified_body += f"""
\t/* ########## BEGIN - Code added by aspect {aspect_name} - {pattern_name} (after) ########## */
\t{after_code.lstrip().rstrip()}
\t/* ############ END - Code added by aspect {aspect_name} - {pattern_name} (after) ########## */
"""
    return f"{function_signature} {{ {modified_body} }}"

def process_cpp_file(file_path, aspects):
    with open(file_path, 'r') as file:
        content = file.read()
        modified_content = content

        for aspect_name in aspects:
            # print("Processing " + aspect_name)
            for pattern_name in aspects[aspect_name]:
                # print("- Match pattern " + pattern_name)
                pattern = aspects[aspect_name][pattern_name]

                return_type = pattern['return_type']
                namespace = pattern['namespace']
                function_name = pattern['function_name']
                before_code = ''
                after_code = ''
                define_code = ''

                if 'before_code' in pattern:
                    before_code = pattern['before_code']

                if 'after_code' in pattern:
                    after_code = pattern['after_code']

                if 'define_code' in pattern:
                    define_code = pattern['define_code']

                if function_name == "~": # Destructor
                    if namespace != "":
                        function_name = "~" + namespace
                    else:
                        function_name = r'~[^(]+'

                function_pattern_regex = (r'((?:(' + return_type + r')\s+)') if return_type != "" else r'((\w*)\s*'
                function_pattern_regex += (r'(?:(' + namespace + r')::)') if namespace != "" else r'(?:([^:{}()]+)::)'
                function_pattern_regex += (r'(' + function_name + r')') if function_name != "" else r'([^(]+)'
                function_pattern_regex += r'\([^)]*\)[^{]*)\{([^{}]*(?:\{(?5)\}[^{}]*)*)\}'

                
                
                if define_code != "" and re.search(function_pattern_regex, content):
                    modified_content = f"""
/* ########## BEGIN - Code added by aspect {aspect_name} - {pattern_name} (define) ########## */
{define_code.lstrip().rstrip()}
/* ############ END - Code added by aspect {aspect_name} - {pattern_name} (define) ########## */
{modified_content}
"""

                # Regex to match function definitions
                function_pattern = re.compile(function_pattern_regex)
                
                modified_content = function_pattern.sub(lambda match: apply_aspects_to_function(match, before_code, after_code, aspect_name, pattern_name), modified_content)

        with open(file_path, 'w') as file:
            file.write(modified_content)

def copy_project(source_dir, dest_dir):
    include_paths = [
        'app/app.pro',
        'tests/main.cpp', 'tests/tests.pro', 'tests/LevelSceneGeneration.cpp', 'tests/LevelSceneGeneration.h', 'tests/PlayerInteractionsTests.cpp', 'tests/PlayerInteractionsTests.h', 'tests/TestsGlobal.cpp', 'tests/TestsGlobal.h', 'tests/WindowGenerationTests.cpp', 'tests/WindowGenerationTests.h', 'tests/UnitTest.cpp', 'tests/UnitTest.h',
        'Joffrey_s_Journey.pro'
    ]

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

def process_project(src_dir, dest_dir, aspect_dir):
    if os.path.exists(dest_dir):
        shutil.rmtree(dest_dir)
    
    copy_project(src_dir, dest_dir)

    aspects = load_aspects(aspect_dir)
    
    src_code_dir = os.path.join(dest_dir, 'src')
    for root, _, files in os.walk(src_code_dir):
        for file in files:
            if file.endswith('.cpp'):
                process_cpp_file(os.path.join(root, file), aspects)

if __name__ == "__main__":
    src_directory = '.'  # Original project directory
    dest_directory = './modified_project'  # Directory for the modified project
    aspect_directory = './aspects'  # Directory containing aspect files

    process_project(src_directory, dest_directory, aspect_directory)

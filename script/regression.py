import subprocess
import sys

if len(sys.argv) < 6:
    print(
        "ERROR: No cells file provided.\n"
        "Usage: python main.py <cells.spi> <Cpp_program_path> <Evaluator_path> <output_json_dir> <score_file_path>")
    exit()

cells_name = []
with open(sys.argv[1], 'r') as file:
    for line in file:
        parts = line.split(" ")
        if parts[0] == ".SUBCKT":
            cells_name.append(parts[1])

file = open(sys.argv[5], 'w')
for cell in cells_name:
    file.write(cell + '\n')
    result_cpp = subprocess.run(
        [sys.argv[2], '-n', sys.argv[1], '-c', cell, '-o', sys.argv[4]], capture_output=True,
        text=True)
    result_eva = subprocess.run(['python3', sys.argv[3], sys.argv[4] + cell + '.json', cell, sys.argv[1]],
                                capture_output=True, text=True)
    output_cpp = result_cpp.stdout.split('\n')
    for output_line in output_cpp:
        word = output_line.split(' ')
        if word[0] == 'Total':
            file.write(output_line + '\n')

    output_eva = result_eva.stdout.split('\n')
    for output_line in output_eva:
        word = output_line.split(' ')
        if word[0] == 'Cell':
            file.write(word[0] + ' ' + word[1] + ' ' + word[2] + '\n')

file.close()

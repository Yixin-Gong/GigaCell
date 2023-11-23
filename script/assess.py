import sys
import re

if len(sys.argv) < 3:
    print(
        "ERROR: No assess file provided.\n"
        "Usage: python main.py <score_file_path> <assess_file_path>")
    exit()

runtime = 0
score = 0
assess_file = open(sys.argv[2],'w')
with open(sys.argv[1], 'r') as score_file:
    for line in score_file:
        words = line.split(' ')
        if len(words) == 1:
            continue
        if words[1] == 'runtime':
            dig_runtime = ''.join([char for char in words[3] if char.isdigit() or char == '.'])
            runtime = runtime + float(dig_runtime)
            assess_file.write("{:{}}".format(dig_runtime, 10))
        if words[0] == 'Cell':
            score = score + float(words[2])
            assess_file.write("{:{}}".format(words[2], 10))


ave_runtime = runtime/340
ave_score = score/340

assess_file.write("ave_runtime" + ' '+str(ave_runtime) + 's'+ '\n')
assess_file.write("ave_score" + ' '+str(ave_score) + '\n')
assess_file.close()
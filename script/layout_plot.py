import json
import sys

import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle

if len(sys.argv) < 3:
    print("ERROR: No placement file provided.\nUsage: python main.py <placement_file> <cell_name>")
    exit()
placement_file = sys.argv[1]
placement_stream = open(placement_file, 'r')
placement_dic = json.load(placement_stream)
placement = placement_dic["placement"]
cell_name = sys.argv[2]

width = -1
for transistor_name, properties in placement.items():
    if properties["x"] > width:
        width = properties["x"]

fig, ax = plt.subplots(figsize=(width * 10 + 1, width * 2))

ax.set_xlim(0, (width + 1) * 3 + 3)
ax.set_ylim(0, 540)

for transistor_name, properties in placement.items():
    if int(properties["y"]):
        rect = Rectangle((int(properties["x"]) * 3, 50.0), 3, int(properties["width"]), facecolor='orange',
                         edgecolor='black')
        ax.add_patch(rect)
    else:
        rect = Rectangle((int(properties["x"]) * 3, 490), 3, -int(properties["width"]), facecolor='orange',
                         edgecolor='black')
        ax.add_patch(rect)

for transistor_name, properties in placement.items():
    if int(properties["y"]):
        rect = Rectangle((int(properties["x"]) * 3 + 1, 0.0), 1, 540, facecolor='green', edgecolor='black')
        ax.add_patch(rect)
    else:
        rect = Rectangle((int(properties["x"]) * 3 + 1, 540), 1, -540, facecolor='green', edgecolor='black')
        ax.add_patch(rect)

ax.set_title(cell_name)
ax.set_xticks([])
ax.set_yticks([])

plt.show()

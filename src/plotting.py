import matplotlib
matplotlib.use('Agg')

import matplotlib.pyplot as plt
import pandas as pd
import sys
import os

def plot_connected_scatter(input_file):
    data = pd.read_csv(input_file)
    x_label = data.columns[0]
    y_label = data.columns[1]
    x = data[x_label].values
    y = data[y_label].values
    plt.figure(figsize=(1280/100, 720/100), dpi=100)
    plt.axhline(y=0, color='black', linestyle='solid', linewidth=1) # baseline
    plt.plot(x, y, '-')
    plt.xlabel(x_label)
    plt.ylabel(y_label)
    plt.autoscale(enable=True, axis='both', tight=True)
    output_file = os.path.splitext(input_file)[0] + '.png'
    plt.savefig(output_file, dpi=100, bbox_inches='tight')
    plt.close()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        sys.exit(1)
    input_file = sys.argv[1]
    plot_connected_scatter(input_file)

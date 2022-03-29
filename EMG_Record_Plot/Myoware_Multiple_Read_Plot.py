from tkinter import END
import matplotlib.pyplot as plt
import numpy as np
from prompt_user import *

def read_file():
    index_start_line = 2
    
    #Prompt user for file path
    file_path = prompt_user_file()
    
    max_index = 0
    with open (file_path, "r") as file:
        while True:
            data_line = file.readline()
            if len(data_line) == 0:
                break
            else:
                max_index +=1
    file.close()
    max_index = max_index - index_start_line - 1

    #Load file data into a numpy array
    data = np.loadtxt(fname = file_path, dtype = "int32", skiprows= index_start_line, max_rows= max_index, delimiter = ",")
    return data

def plot_file(data):    
    Fs = 1000 #Hz
    num_emg_channel = 4
    Ts = 1/Fs #sec
    x = np.arange(0, len(data)*Ts, Ts)
    start_index_channel = 1

    colors = ["b", "g", "r", "c", "m", "y", "tab:orange", 'tab:pink']
    index_start = 0
    index_stop = None

    # fig, axs = plt.subplots(2)
    # fig.suptitle("EMG data")
    # for i in range(num_emg_channel):
    #     axs[0].plot(data[index_start:index_stop,-1], data[index_start:index_stop,i], colors[i], label = "Ch"+str(i+1))
    # axs[0].legend(bbox_to_anchor=(1.05, 1))
    # axs[1].plot(data[index_start:index_stop,-1], data[index_start:index_stop,-2], "k", label = "Cue")
    # axs[1].legend(bbox_to_anchor=(1.05, 1))
    plt.suptitle("EMG data")
    for i in range(num_emg_channel):
        plt.plot(data[index_start:index_stop,-1], data[index_start:index_stop,i], colors[i], label = "Ch"+str(i+1))
    plt.legend()    
    plt.show()
    
if __name__ == "__main__":
    data = read_file()
    plot_file(data)
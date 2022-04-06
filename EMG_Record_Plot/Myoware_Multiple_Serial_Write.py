import serial
import time
import matplotlib.pyplot as plt
from operator import index
import tkinter as tk
from tkinter import filedialog
import numpy as np
from prompt_user import*
import os
import datetime

#CHANGE HERE
folder_out_path = "C:/Users/HanNguyen/UBC/BMEG 457 001 2021W1-2 Biomedical Engineering Design Project - Team ο - Neuroprosthetic Fingers - Team ο - Neuroprosthetic Fingers/Tasks/Data/EMG/20220307_EMG_2xMyoware_Feather_GelElectrode"
COM_num = 4
baud_rate = 115200


def is_float(element) -> bool:
    try:
        float(element)
        return True
    except ValueError:
        return False

def read_serial():
    # set up the serial line
    ser = serial.Serial('COM'+str(COM_num), baud_rate)
    ser.flushInput()

    data = [] # Empty matrix to store the data
    while True:
        try:
            ser_bytes = ser.readline()
            decoded_bytes = ser_bytes[0:len(ser_bytes)-2].decode("utf-8")
            split_decoded = decoded_bytes.split(",")
            float_list = []
            for i in split_decoded:
                if is_float(i):
                    val = float(i)
                    float_list.append(val)
            print(float_list)
            data.append(float_list)
            
        except KeyboardInterrupt:
            print("Keyboard Interrupt")
            break
    return data

def write_file(data):  
    print(folder_out_path)
    
    #Write the data to a .txt file
    time_now = datetime.datetime.now().strftime("%Y%m%d%H%M%S")
    file_name = "EMG_data_" + str(time_now) +".txt"
    file_path = os.path.join(folder_out_path, file_name)
    num_data_points = len(data)
    num_channels = len(data[1])

    print(num_data_points)
    print(num_channels)
    with open (file_path, "w") as file:
        for i in range(1, num_data_points):
            for j in range(num_channels):
                file.write(str(data[i][j]))
                if j < (num_channels-1):
                    file.write(",")
                else:
                    file.write("\n")          
    file.close()

if __name__ == "__main__":
    data = read_serial()
    write_file(data)
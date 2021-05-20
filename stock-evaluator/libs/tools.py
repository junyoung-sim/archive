
import csv
import matplotlib.pyplot as plt
from pandas_datareader.data import DataReader
from os import system, chdir

def write(data, file_name):
    try:
        for i in range(len(data)):
            with open(file_name[i], "w+") as File:
                csvWriter = csv.writer(File, delimiter=",")
                csvWriter.writerows(data[i])
        print("Successfully wrote data into {}\n" .format(file_name))
    except Exception as e:
        print("Error occured while writing {}, {}!" .format(file_name, e))

def read(file_name, type="float"):
    data = []
    with open(file_name, "r") as File:
        lines = File.readlines()
        if type == "float":
            data = [[float(val) for val in line.replace("\n", "").split(",")] for line in lines]
        elif type == "int":
            data = [[int(val) for val in line.replace("\n", "").split(",")] for line in lines]
    return data

def GetIndexList(indexlist):
    with open(indexlist, "r") as File:
        lines = File.readlines()
        indexes = [line.replace("\n", "") for line in lines]
    return indexes

def YahooFinance(id="", date=""):
    download = DataReader(id, "yahoo", date)
    download.to_csv("./data/" + id + ".csv")

    data, dates = [], []
    with open("./data/" + id + ".csv") as stock:
        info = stock.readlines()
        del info[0]
        lines = [line.split(",") for line in info]
        data = [float(line[6]) for line in lines]
        dates = [line[0] for line in lines]

    stock = {"prices": data, "dates": dates}
    return stock

def cleanup():
    system("rm ./data/*.csv")
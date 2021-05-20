
from csv import writer

def write(data=[], path=""):
    try:
        with open(path, "w+") as File:
            csvWriter = writer(File, delimiter=",")
            csvWriter.writerows(data)
    except Exception as e:
        print("Error occurred while writing {}, {}" .format(path, e))
        return False

def read(path=""):
    data = []
    try:
        with open(path, "r") as File:
            data = [line.replace("\n", "").split(",") for line in File.readlines()]
            for i in range(len(data)):
                for j in range(len(data[i])):
                    data[i][j] = float(data[i][j])
        return data
    except FileNotFoundError:
        print(path, " does not exist.")
        return False 
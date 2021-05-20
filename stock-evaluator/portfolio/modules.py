
from os import walk, system
from pandas_datareader.data import DataReader

def load(name):
    ids, names, goal, shares, cash = [], [], [], [], 0
    try:
        with open("portfolios/" + name + ".ptf", "r") as portfolio:
            lines = portfolio.readlines()
            for line in lines:
                index = line.replace("\n", "").split(",")
                if len(index) != 1:
                    ids.append(index[0])
                    names.append(index[1])
                    goal.append(float(index[2]))
                    shares.append(int(index[3]))
                else:
                    cash = int(index[0])
    except Exception as e:
        print("Requested portfolio ({}) does not exists!" .format(name))
    return ids, names, goal, shares, cash

def update(name, ids, names, goal, shares, cash):
    with open("portfolios/" + name + ".ptf", "w+") as portfolio:
        for i in range(len(names)):
            index = ids[i] + "," + names[i] + str(goal[i]) + "," + str(shares[i]) + "\n"
            portfolio.write(index)
        portfolio.write(str(cash))

def listPortfolios():
    for r, d, f in walk("portfolios"):
        portfolios = [file.replace(".ptf", "") for file in f if ".ptf" in file]
    return portfolios

def YahooFinance(id="", date=""):
    if id == "" or date == "":
        id = input("Enter stock index ID (ex: AAPL, ^GSPC): ")
        date = input("Enter start data of historical data (YYYY-MM-DD): ")
    download = DataReader(id, "yahoo", date)
    download.to_csv("../data/" + id + ".csv")
    
    data, dates = [], []
    with open("../data/" + id + ".csv") as stock:
        info = stock.readlines()
        del info[0]
        lines = [line.split(",") for line in info]
        data = [float(line[6]) for line in lines]
        dates = [line[0] for line in lines]
    return data, dates

from datetime import datetime
from prettytable import PrettyTable
import matplotlib.pyplot as plt
from os import system
import numpy as np
import tqdm as tqdm
import ast, json

from libs.tools import *
from libs.algo import *
from libs.model import DeepNeuralNetwork

np.set_printoptions(suppress=True)

def process_financial_data(ids=[], download_date="", trainable=True):
    gold = YahooFinance("GOLD", download_date)
    
    data, output = [], []
    loop = tqdm.tqdm(total=len(ids), position=0, leave=False)
    for index in ids:
        loop.set_description("Processing financial data [{}]... (trainable={}) " .format(index, trainable))
        stock = YahooFinance(index, download_date)
        stock, adjusted_gold = MatchData(stock.get("prices"), stock.get("dates"), gold.get("prices"), gold.get("dates"))
        
        if trainable == False:
            data.append([
                AnnualProfit(stock[:len(stock)-180]),
                Acceleration(data=stock[len(stock)-180:], delta_range=5),
                MovingAvg(data=stock[len(stock)-180:], window=35, stride=1),
                Sensitivity(stock[len(stock)-180:]),
                MovingAvg(data=adjusted_gold[len(adjusted_gold)-180:], window=35, stride=1),
            ])
        else:
            for i in range(360, len(stock) - 180, 180):
                data.append([
                    AnnualProfit(stock[:i-180]),
                    Acceleration(data=stock[i-180:i], delta_range=5),
                    MovingAvg(data=stock[i-180:i], window=35, stride=1),
                    Sensitivity(stock[i-180:i]),
                    MovingAvg(data=adjusted_gold[i-180:i], window=35, stride=1),
                ])
                output.append([
                    TimeframeProfit(stock[i-180:i])
                ])
        loop.update(1)
    dataset = {"data": data, "output": output}
    return dataset

class DeepFinance: # basic financial modeling only using a fully connected network
    def __init__(self, name="model"):
        self.name = name
        self.model = None
        self.load_model()
    def load_model(self):
        config = {}
        try:
            with open("./models/" + self.name + "/configuration.txt", "r") as File:
                config = ast.literal_eval(File.read())
        except FileNotFoundError:
            # apply default paramters when creating a new model
            config = {
                "layer_config": [[5,5],[5,5],[5,1]],
                "activation": "relu",
                "abs_synapse": 1.00,
                "cost": "MSE",
                "learning_rate": 0.01
            }
        self.model = DeepNeuralNetwork(name=self.name, model_configuration=config)
    def train(self, ids=[], download_date="2000-01-01", epoch=100, save_training_data=True, plot_error=True):
        dataset = process_financial_data(ids, download_date, True)
        training_input, training_output = np.array(dataset.get("data")), np.array(dataset.get("output"))
        if save_training_data is True:
            write([training_input, training_output], ["./data/train-financial-data", "./data/train-financial-output"])

        error = self.model.train(training_input, training_output, epoch)
        if plot_error is True:
            plt.plot(error, color="red")
            plt.savefig("./res/error")
    def run(self, ids=[]):
        date = datetime.today().strftime('%Y-%m-%d')
        date = str(int(date[:4])-3) + date[4:]

        dataset = process_financial_data(ids, date, False)
        test_data = np.array(dataset.get("data"))

        prediction = self.model.predict(test_data)
        
        print("\nInput Data:\n", test_data)
        table = PrettyTable()
        table.field_names = ['ID', 'Estimated Profit 36W (Model)']
        for i in range(len(ids)):
            table.add_row([ids[i], prediction[i] * 100])
        print("\n", table)
    def backtest(self, id="", date="2000-01-01", plot=True):
        dataset = process_financial_data([id], date, True)
        test_data, actual = np.array(dataset.get("data")), np.array(dataset.get("output")).flatten()

        prediction = self.model.predict(test_data)
        for i in range(len(prediction)):
            prediction[i] *= 100
            actual[i] = 0.00 if actual[i] < 0.00 else actual[i] * 100
        prediction = np.array(prediction)
        print("\nTest Data Output:{}\nTest Data Predictions:{}" .format(actual, prediction))

        if plot is True:
            plt.plot(actual, color="green")
            plt.plot(prediction, color="red")
            plt.savefig("./res/backtest.png")

        return {"actual": actual, "prediction": prediction}
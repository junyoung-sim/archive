
import tqdm as tqdm
import numpy as np
import os, ast, json
import matplotlib.pyplot as plt

from libs.util import *
from libs.dnn import DeepNeuralNetwork

#np.set_printoptions(suppress=True)

def relu(value=0.00, slope=1.00):
    return max(0, value * slope)

def normalize(data):
    minimum, maximum = min(data), max(data)
    normalized = np.array([(p - minimum) / (maximum - minimum) for p in data])
    return normalized

def extract_features(input=[], kernel=[], stride=1, padding=True): # convolution   
    if padding is True:
        pad = np.zeros((input.shape[0] + 2, input.shape[1] + 2))
        for i in range(1, pad.shape[0] - 1):
            for j in range(1, pad.shape[1] - 1):
                pad[i][j] = input[i-1][j-1]
        input = pad
    encoded = []
    for r in range(0, input.shape[0] - (kernel.shape[0] + stride), stride):
        encoded_row = []
        for c in range(0, input.shape[1] - (kernel.shape[1] + stride), stride):
            matmul = 0.00
            k_row, k_col = 0, 0
            for i in range(r, r + kernel.shape[0]):
                for j in range(c, c + kernel.shape[1]):
                    matmul += input[i][j] * kernel[k_row][k_col]
                    k_col += 1
                k_row += 1
                k_col = 0
            encoded_row.append(relu(value=matmul, slope=1.0))
        encoded.append(encoded_row)
    encoded = np.array(encoded)
    return encoded
    
def size_reduction(input=[], pool_size=[2,2]): # max pooling
    reduced = []
    for r in range(0, input.shape[0] - pool_size[0], pool_size[0]):
        reduced_row = []
        for c in range(0, input.shape[1] - pool_size[1], pool_size[1]):
            window = [input[i][j] for j in range(c, c + pool_size[1]) for i in range(r, r + pool_size[0])]
            reduced_row.append(max(window))
        reduced.append(reduced_row)
    reduced = np.array(reduced)
    return reduced

class Autoencoder:
    def __init__(self, name="model"):
        self.name = name
        self.layer = []
        self.kernel = []
    def save(self):
        if os.path.exists("./models/" + self.name + "_encoder/attributes") == False:
            os.mkdir("./models/" + self.name + "_encoder/")
        with open("./models/" + self.name + "_encoder/attributes", "w+") as File:
            File.write(json.dumps(self.layer))
        for i in range(self.kernel.shape[0]):
            path = "./models/" + self.name + "_encoder/" + "kernel" + str(i)
            write(self.kernel[i], path)
    def load(self):
        try:
            with open("./models/" + self.name + "_encoder/attributes", "r") as File:
                self.layer = json.loads(File.read())
            for i in range(len(self.layer)):
                self.kernel.append(np.array(read("./models/" + self.name + "_encoder/kernel" + str(i))))
            self.kernel = np.array(self.kernel)
            return True
        except FileNotFoundError:
            return False
    def add_layer(self, attributes={"conv_size": [3,3], "stride": 1, "padding": True, "pool_size": [2,2]}):
        self.layer.append(attributes)
    def initialize(self):
        if self.load() != True:
            for layer in self.layer:
                self.kernel.append(np.random.uniform(-1.0, 1.0, size=(layer.get("conv_size")[0], layer.get("conv_size")[1])))
            self.kernel = np.array(self.kernel)
        for i in range(len(self.layer)):
            print("Encoding Layer #{} = {}" .format(i, self.layer[i]))
    def encode(self, dataset=[]):
        encoded_dataset = []
        loop = tqdm.tqdm(total=dataset.shape[0], position=0, leave=False)
        # encode dataset (convolution: feature extraction, max pooling: size reduction)
        for data in dataset:
            loop.set_description("Standard encoding on dataset...")
            for l in range(len(self.layer)):
                stride, padding, pool_size = self.layer[l].get("stride"), self.layer[l].get("padding"), self.layer[l].get("pool_size")
                if l == 0:
                    data = normalize(data.flatten()).reshape(28,28)
                data = extract_features(data, self.kernel[l], stride, padding)
                data = size_reduction(data, pool_size)
            encoded_dataset.append(data)
            loop.update(1)
        encoded_dataset = np.array(encoded_dataset)
        print(encoded_dataset)
        return encoded_dataset
    def train_decoder(self, original=[], encoded=[], architecture=[], learning_rate=0.01, epoch=100):
        original_dataset = np.array([normalize(data.flatten()) for data in original])
        encoded_dataset = np.array([data.flatten() for data in encoded])
        # configure decoder neural network architecture
        decoder_nn_config = {
            "layer_config": architecture,
            "activation": "relu",
            "abs_synapse": 1.00,
            "cost": "MSE",
            "learning_rate": learning_rate
        }
        # train decoder neural network
        decoder = DeepNeuralNetwork(self.name + "_decoder", decoder_nn_config)
        error = decoder.train(encoded_dataset, original_dataset, epoch)
        # test the first input and display reconstructed image
        reconstructed = decoder.predict([encoded_dataset[0]])
        img = plt.imshow(np.array(reconstructed[0]).reshape(28,28), cmap="gray")
        plt.savefig("./res/reconstructed.png")
    def run(self, test_dataset=[], variate=True):
        encoded_dataset = np.array([data.flatten() for data in self.encode(test_dataset)])
        decoder = DeepNeuralNetwork(name=self.name + "_decoder")
        reconstructed = decoder.predict(encoded_dataset)
        return reconstructed

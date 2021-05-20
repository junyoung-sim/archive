#!/usr/bin/env python3

import json
import numpy as np
import random as random
import matplotlib.pyplot as plt
from core.autoencoder import Autoencoder
from mlxtend.data import loadlocal_mnist
from libs.dnn import DeepNeuralNetwork
from libs.util import *

dataset, labels = loadlocal_mnist(images_path="../train-images-idx3-ubyte", labels_path="../train-labels-idx1-ubyte")

def train():
    model = Autoencoder(name="mnist")
    model.add_layer({"conv_size": [2,2], "stride": 1, "padding": False, "pool_size": [2,2]})
    model.add_layer({"conv_size": [2,2], "stride": 1, "padding": False, "pool_size": [2,2]})
    model.initialize()
    # start encoding the inputs
    encoded = model.encode(dataset)
    # train decoder to reconstruct input to an augmented dataset
    error = model.train_decoder(dataset, encoded, [[16,16],[16,144],[144,784]], 0.01, 100)
    model.save()

def test():
    model = Autoencoder(name="mnist")
    model.initialize()
    augmented = model.run(test_dataset=dataset, variate=False)
    # save augmented dataset
    np.save("../augmented_dataset", augmented)

def view_augmented_dataset():
   augmented_dataset = np.load("../augmented_dataset.npy")
   augmented = [data.reshape(28,28) for data in augmented_dataset]
   for data in augmented:
       img = plt.imshow(data, cmap="gray")
       plt.show()
       input()    

if __name__ == "__main__":
    print("")
    #train()
    #test()
    view_augmented_dataset()

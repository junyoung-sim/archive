
import dnn
import wave as wave
from tqdm import tqdm
import subprocess as sp
from prettytable import PrettyTable
import time

MINIMUM_SAMPLING_RANGE = 5
DEFAULT_SAMPLING_RANGE = 10
MAXIMUM_SAMPLING_RANGE = 20

MINIMUM_POOLING_RANGE = 1
DEFAULT_POOLING_RANGE = 2
MAXIMUM_POOLING_RANGE = 5

class NPU:
    def __init__(self):
        self.dataset = []
        self.minimum_raw_length = 10000
    def upload(self, path, label, output_matrix_size):
        self.dataset.append(wave.NeuralWave(path, label, output_matrix_size))
        if self.dataset[len(self.dataset) - 1].raw_data_length() < self.minimum_raw_length:
            self.minimum_raw_length = self.dataset[len(self.dataset) - 1].raw_data_length()
        print("NPU: Uploaded neural dataset [Path =", path, "Label = ", label, "]")
    def display_dataset(self):
        table = PrettyTable()
        table.field_names = ["Dataset #", "Data Type/Address", "Label", "Raw Data Length", "Sampled Data Length", "DNN Output Matrix"]
        for i in range(len(self.dataset)):
            table.add_row([i, self.dataset[i], self.dataset[i].data_label(), 
                self.dataset[i].raw_data_length(), self.dataset[i].sampled_data_length(), self.dataset[i].dnn_matrix()])
        print(table)
        print('')
    def neural_spike_detector(self, signal, sampling_range=DEFAULT_SAMPLING_RANGE):
        """ Signal sampling algorithm on neural signals """
        if (sampling_range < MINIMUM_SAMPLING_RANGE) | (sampling_range > MAXIMUM_SAMPLING_RANGE):
            sampling_range = DEFAULT_SAMPLING_RANGE
        maximum_alteration = -10000 
        for _range in range(0, self.minimum_raw_length - sampling_range, sampling_range):
            for i in range(_range + sampling_range):
                if i + 1 >= (self.minimum_raw_length):
                    pass
                else:
                    signal_alteration = abs(signal.raw_bit(i) - (signal.raw_bit(i + 1)))
                    if signal_alteration > maximum_alteration:
                        maximum_alteration = signal_alteration
                        bit1 = wave.NeuralBit(signal.raw_bit(i))
                        bit2 = wave.NeuralBit(signal.raw_bit(i + 1))
            signal.push_sampled_bit(bit1.bit())
            signal.push_sampled_bit(bit2.bit())
    def npu(self, signal, sampling_range, pooling_range):
        """ Neural Processing Unit (NPU) """
        self.neural_spike_detector(signal, sampling_range)
    def run(self, sampling_range=DEFAULT_SAMPLING_RANGE, pooling_range=DEFAULT_POOLING_RANGE):
        print('\nRunning session...')
        print('Starting Neural Processing Unit...\n')
        time.sleep(3)
        loop = tqdm(total = len(self.dataset), position = 0, leave = False)
        for i in range(len(self.dataset)):
            loop.set_description('NPU Processing neural database...' .format(i))
            self.npu(self.dataset[i], sampling_range, pooling_range)
            loop.update(1)
        print('\nNPU: Completed neural database processing!\n')
        loop.close()
        time.sleep(2)
        self.display_dataset()
        
        confirmation = input('Proceed deep neural network training? [y/n]: ')
        if confirmation == 'y':
            print('\nInitiating DNN training session!')
            dataset_pkg = []
            dataset_output_pkg = []
            for i in range(len(self.dataset)): # package the processed datasets
                dataset_pkg.append(self.dataset[i].sampled())
            for i in range(len(self.dataset)): # package the output matrix of the datsets
                dataset_output_pkg.append(self.dataset[i].dnn_matrix())
            dnn.train(dataset_pkg, dataset_output_pkg)
        else:
            print('Terminating process...\nAll processed datasets are discarded...')
    def predict(self, sampling_range=DEFAULT_SAMPLING_RANGE, pooling_range=DEFAULT_POOLING_RANGE):
        # assuming that this function will ONLY be called in run.py,
        # process the input, package it into a 2d list, execute run_tf_dnn_sess() with TESTING MODE
        print('\nRunning session in TEST mode...')
        print('Starting Neural Processing Unit (NPU)...\n')
        time.sleep(3)
        loop = tqdm(total = len(self.dataset), position = 0, leave = False)
        for i in range(len(self.dataset)):
            loop.set_description('NPU Processing neural database...' .format(i))
            self.npu(self.dataset[i], sampling_range, pooling_range)
            loop.update(1)
        print('\nNPU: Completed neural database processing!\n')
        loop.close()
        time.sleep(2)
        self.display_dataset()

        print("Packaging dataset...")
        dataset_pkg = []
        dataset_output_pkg = []
        for i in range(len(self.dataset)): # package the processed datasets
            dataset_pkg.append(self.dataset[i].sampled())
        
        print("\nRunning model...")
        dnn.test(dataset_pkg)
# class object to store neural signal data

class NeuralBit:
    def __init__(self, value):
        self.value = value
    def bit(self):
        return self.value

class NeuralWave:
    def __init__(self, path, label, output_matrix_size):
        """ Specify the path to the data set, upload the data points"""
        self.label = label
        self.raw_data = []
        self.sampled_data = []
        self.output_matrix = []
        self.initial_mse = None
        self.optimized_mse = None
        file = open(path, "r")
        for val in file.read().split(','):
            self.raw_data.append(int(val))
        file.close()
        # configure the DNN output matrix of the neural wave
        for i in range(output_matrix_size):
            if i == label:
                self.output_matrix.append(1.00)
            else:
                self.output_matrix.append(0.00)
    def data_label(self):
        return self.label
    def raw(self):
        return self.raw_data
    def raw_bit(self, index):
        if (index < 0) | (index >= len(self.raw_data)):
            return -1
        else:
            return self.raw_data[index]
    def sampled(self):
        return self.sampled_data
    def sampled_bit(self, index):
        if (index < 0) | (index >= len(self.sampled_data)):
            return -1
        else:
            return self.sampled_data[index]
    def clear_sampled_matrix(self):
        del self.sampled_data[:]
    def dnn_matrix(self):
        return self.output_matrix
    def replace_raw_bit(self, index, value):
        if (index < 0) | (index >= len(self.raw_data)):
            pass
        else:
            self.raw_data[index] = value
    def push_sampled_bit(self, val):
        self.sampled_data.append(val)
    def raw_data_length(self):
        return len(self.raw_data)
    def sampled_data_length(self):
        return len(self.sampled_data)

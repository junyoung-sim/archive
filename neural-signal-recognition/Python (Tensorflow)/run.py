#!/usr/bin/env python3 

import neuralwave

if __name__ == "__main__":
    print('')
    path = input("Enter path to neural signal: ")
    label = input("Specify label = ")
    output_matrix_size = input("Specify output matrix size = ")
    sess = neuralwave.NPU()
    # upload neural signal file path for model prediction
    sess.upload(path, int(label), int(output_matrix_size))
    sess.predict()
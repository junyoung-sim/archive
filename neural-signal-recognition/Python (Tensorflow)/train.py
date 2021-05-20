#!/usr/bin/env python3

import neuralwave

database = "../Database/"

if __name__ == "__main__":
    print('')
    sess = neuralwave.NPU()
    # upload datasets in the database file
    for d in range(0, 10):
        for i in range(1, 11):
            path = database + "Digit" + str(d)
            path += "/wave" + str(i) + ".txt"
            sess.upload(path, d, 10)
    sess.run() # run the NPU
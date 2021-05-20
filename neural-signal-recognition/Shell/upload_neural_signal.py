
import os
import shutil

def upload():
	# Uploading the new neural signal data file
	# User should specify full path to neural signal data file
	# and also what that dataset is labeled to
	neural_signal_data_path = input('Enter full path to neural signal data: ')
	neural_signal_label = input('Enter label number of the dataset: ')

	dataset_archive = "../NeuralSignalDataSet/Digit " + str(neural_signal_label)

	shutil.copy(neural_signal_data_path, dataset_archive)
	os.remove(neural_signal_data_path)

if __name__ == "__main__":
	upload()
	

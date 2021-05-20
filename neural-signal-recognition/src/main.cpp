
#include <iostream>
#include <string>
#include "../Interpreter/neuralwave.hpp"

using namespace std;

int main()
{
	// unless the directory of the dataset has changed, 
	// this main file is already ready to go 
	NeuralSignalInterpreter nsi;
	string dataset_storage_dir = "Database/";

	for (int digit = 0; digit <= 9; digit++) {
		for (int wav = 1; wav <= 9; wav++) {
			string dataset = dataset_storage_dir;
			dataset += "/Digit" + to_string(digit) + "/wave";
			dataset += to_string(wav) + ".txt";
			// upload the neural signal dataset directory to the processor
			// this will automatically extract data from the brain wave signal .txt
			nsi.upload_dataset(dataset, digit);
		}
	}

	nsi.interpret_dataset(DEFAULT_SAMPLING_WINDOW_SIZE); // process the given datasets
	nsi.train_nn_model(1000, 0.01, 10); // train the neural network model with the datasets

	return 0;
}

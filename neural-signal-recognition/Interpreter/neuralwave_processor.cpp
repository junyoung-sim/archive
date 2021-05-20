
/*

NEURAL SIGNAL INTERPRETER ALGORITHM
(SEGMENTATION POOLING FOR ANALYZING NEURAL SIGNAL DATA SETS)

*/

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include "neuralwave.hpp"
#include "../DNN/neural_network.hpp"

using namespace std;

vector<int> NeuralSignalInterpreter::neural_signal_sampling(std::vector<int> raw_signal, unsigned int sampling_range) {
	int maximum_signal_alteration = -10000;
	vector<NeuralSignal> sampled_points;
	vector<int> sampled_matrix;

	sampled_points.push_back(NeuralSignal());
	sampled_points.push_back(NeuralSignal());

	for (unsigned int range = 0; range < minimum_signal_length - sampling_range; range += (sampling_range - 1)) {
		for (unsigned int i = range; i < range + sampling_range; i++) {
			// NEURAL SIGNAL SEGMENTATION ALGORITHM
			// calculate the signal alteration that occurs to every two points in the segmentation range
			// the two signal points with the highest signal alteration will be sampled for the segmentated matrix
			if (i + 1 >= range + sampling_range) {}
			else {
				int signal_alteration = abs(raw_signal[i] - raw_signal[i + 1]);

				if (signal_alteration > maximum_signal_alteration) {
					sampled_points[0].set_signal_data(raw_signal[i], i);
					sampled_points[1].set_signal_data(raw_signal[i + 1], i);
				}
				else {}
			}
		}

		// push in the sampled signal data points to the segmentation matrix
		sampled_matrix.push_back(sampled_points[0].signal_value());
		sampled_matrix.push_back(sampled_points[1].signal_value());
	}

	sampled_points.clear();
	cout << "Sampled data points from raw signal data..." << endl;

	return sampled_matrix;
}

void NeuralSignalInterpreter::interpret_dataset(unsigned int sampling_range=DEFAULT_SAMPLING_WINDOW_SIZE) {
	// verify segmentation window size
	if (sampling_range > MAXIMUM_SAMPLING_WINDOW_SIZE || sampling_range < MINIMUM_SAMPLING_WINDOW_SIZE) {
		sampling_range = DEFAULT_SAMPLING_WINDOW_SIZE;
	}

	for (unsigned int n = 0; n < neural_signal_holder.size(); n++) {
		neural_signal_holder[n].push_sampled_signal(neural_signal_sampling(neural_signal_holder[n].raw_signal(), sampling_range));
	}
}

void NeuralSignalInterpreter::train_nn_model(unsigned int iterations, double learning_rate, unsigned int amount_of_output_nodes) {
	// prepare the output matrix for all NeuralSignalHolders
	for (unsigned int n = 0; n < neural_signal_holder.size(); n++) {
		neural_signal_holder[n].configure_signal_output_matrix(amount_of_output_nodes);
	}

	unsigned int sampled_data_length = neural_signal_holder[0].sampled_size();

	vector<Layer> layer;
	layer.push_back(Layer(sampled_data_length, sampled_data_length, HIDDEN_LAYER));
	layer.push_back(Layer(sampled_data_length, amount_of_output_nodes, OUTPUT_LAYER));

	NeuralNetwork dnn(layer);

	for (unsigned int d = 0; d < neural_signal_holder.size(); d++) {
		dnn.upload_neural_signal_dataset(neural_signal_holder[d]);
	}
	dnn.sess_run(learning_rate, iterations);
}

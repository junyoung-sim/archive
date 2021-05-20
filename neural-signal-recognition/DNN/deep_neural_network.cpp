
#include <iostream>
#include <cstdlib>
#include <vector>
#include <unistd.h>
#include <fstream>
#include "neural_network.hpp"

using namespace std;

void NeuralNetwork::upload_neural_signal_dataset(NeuralSignalHolder data) {
	training_data_set.push_back(data);
}

void NeuralNetwork::variate_dataset() {
	vector<int> index_stack;
	for (unsigned int i = 0; i < training_data_set.size(); i++) {
		index_stack.push_back(i);
	}

	// variate the training data set by mixing them up randomly
	unsigned int index = 0;
	for (unsigned int i = 0; i < training_data_set.size(); i++) {
		// find vacant index
		while (index_stack[index] == -1) {
			index = rand() % training_data_set.size();
		}

		// swap the randomly selected datasets
		NeuralSignalHolder temp = training_data_set[i];
		training_data_set[i] = training_data_set[index];
		training_data_set[index] = temp;

		index_stack[index] = -1;
	}

	cout << "variated dataset...\n";
}

vector<double> NeuralNetwork::feedforward(NeuralSignalHolder input) {
	vector<double> output;

	for (unsigned int l = 0; l < layer.size(); l++) {
		for (unsigned int n = 0; n < layer[l].neurons(); n++) {
			layer[l].reset_summation(n);
			layer[l].reset_activation(n);
		}
	}

	double p = 0.00;
	for (unsigned int l = 0; l < layer.size(); l++) {
		for (unsigned int n = 0; n < layer[l].neurons(); n++) {
			for (unsigned int i = 0; i < layer[l].inputs(); i++) {
				if (l == 0) p += layer[l].synapse(n, i) * input.sampled_signal_datapoint(i);
				else p += layer[l].synapse(n, i) * layer[l - 1].activation(i);
			}

			layer[l].add_summation(n, p); // set the dot product of neuron (automatically thresholds product in function)
			p = 0.00;

			if (l == layer.size() - 1) { // output layer
				output.push_back(layer[l].activation(n));
			}
			else {}
		}
	}

	return output;
}

void NeuralNetwork::GradientDescentOptimization(double learning_rate, unsigned int iterations) {
	vector<double> output;

	double _gradient = 0.00, _adjustment = 0.00;
	double MSE = 0.00;
	double network_mse = 0.00;

	cout << endl << "------------ Deep Neural Network Training ------------" << endl;

	for (unsigned int r = 0; r < 100; r++) {
		for (unsigned int d = 0; d < training_data_set.size(); d++) {
			for (unsigned int itr = 0; itr < iterations; itr++) {
				output = feedforward(training_data_set[d]); // evaluate training data set to feedforward

				// compute error of the network's output (reduce_sum <- MEAN SQUARED ERROR )
				for (unsigned int n = 0; n < output.size(); n++) {
					MSE += pow(training_data_set[d].desired_output(n) - output[n], 2);
				}
				MSE /= output.size();

				if (itr == 0) training_data_set[d].set_initial_mse(MSE);
				else if (itr == iterations - 1) training_data_set[d].set_optimized_mse(MSE);
				else {
					if (itr % 100 == 0) {
						cout << "(Step: " << itr << ") Neural Signal #" << d << " [Wave: " << training_data_set[d].label() << "] = MSE (" << MSE << endl;
					}
				}

				for (int l = layer.size() - 1; l >= 0; l--) {
					for (unsigned int n = 0; n < layer[l].neurons(); n++) {
						if (l == layer.size() - 1) {
							// COMPUTE DELTA (GRADIENT) AND ADJUSTMENT FOR THE SYNAPSE IN OUTPUT LAYER
							_gradient = (training_data_set[d].desired_output(n) - layer[l].activation(n)) *
								sigmoid_derivative(layer[l].summation(n));

							for (unsigned int c = 0; c < layer[l].inputs(); c++) {
								// COMPUTE ADJUSTMENT VALUE
								// AND SAVE THEM IN THE NEURONS
								_adjustment = learning_rate * _gradient * layer[l - 1].activation(c);

								layer[l].set_adjustment(n, c, _adjustment);
								layer[l].update_synapse(n, c);

								// SUM: MULTIPLY GRADIENT AND SYNAPSE VALUES --> ADD TO PREVIOUS HIDDEN LAYER NEURON ERROR SUM 
								// TO COMPUTE HOW MUCH ERROR THE HIDDEN LAYER NEURON CONTRIBUTED TO THE OUTPUT LAYER
								for (unsigned int _n = 0; _n < layer[l - 1].neurons(); _n++) {
									layer[l - 1].add_error_summation(_n, _gradient * layer[l].synapse(n, c));
								}
							}
						}
						// COMPUTE DELTA (GRADIENT) AND ADJUSTMENT IN THE HIDDEN LAYER
						else {
							for (unsigned int c = 0; c < layer[l].inputs(); c++) {
								_gradient = layer[l].error_summation(n) * sigmoid_derivative(layer[l].summation(n)) * training_data_set[d].sampled_signal_datapoint(c);
								_adjustment = learning_rate * _gradient;

								layer[l].set_adjustment(n, c, _adjustment);
								layer[l].update_synapse(n, c);

								layer[l].reset_error_summation(n);
							}
						}

						_gradient = 0.00;
					}
				}

				MSE = 0.00;
			}

			cout << "\nNeural Signal #" << d << " [Wave: " << training_data_set[d].label() << "] = Initial MSE (" << training_data_set[d].init_mse()
				<< ") ---> After Optimization (" << training_data_set[d].opt_mse() << endl;
		}
	}

	
	// after training process, evaluate all training data sets
	// to confirm the loss of each training set has decreased
	cout << endl << " ==== DNN Neural Signal Training Results ====" << endl << endl;
	for (unsigned int d = 0; d < training_data_set.size(); d++) {
		output = feedforward(training_data_set[d]);

		for (unsigned int n = 0; n < output.size(); n++) {
			MSE += pow(training_data_set[d].desired_output(n) - output[n], 2);
		}

		MSE /= output.size();
		network_mse += MSE;

		cout << "Neural Signal #" << d << " [Wave: " << training_data_set[d].label() << "] = MSE (" << MSE << ")" << endl;
	}

	network_mse /= training_data_set.size();
	cout << "Overall Network MSE = [" << network_mse << "]" << endl;
}

void NeuralNetwork::sess_run(double learning_rate, unsigned int iterations) {
	cout << endl;
	variate_dataset();

	// show how the dataset was mixed up
	cout << "\nNeural Signal Data Set Sequence: \n[ ";
	for (unsigned int i = 0; i < training_data_set.size(); i++) {
		cout << training_data_set[i].label() << " ";
	} cout << endl << endl;

	GradientDescentOptimization(learning_rate, iterations); // run the optimizer (train data sets)
	save_sess();
}

void NeuralNetwork::save_sess() {
	string sess_save_path = "sess_save/";
	string path = sess_save_path;
	// write the synaptic weights of each neuron in separate files
	for(unsigned int l = 0; l < layer.size(); l++) {
		for(unsigned int n = 0; n < layer[l].neurons(); n++) {
			path += "Layer" + to_string(l) + "/" + "neuron" + to_string(n);
			//cout << path << " Open Status = ";
			ofstream out(path, ios::out | ios::binary);
			if (!out) {
				cout << "Failed!" << endl;
			}
			else{
				double synapses[layer[l].inputs()];
				for(unsigned int i = 0; i < layer[l].inputs(); i++) {
					synapses[i] = layer[l].synapse(n, i);
				}
				out.write((char *) &synapses, sizeof(synapses));
			}
			path = sess_save_path;
			out.close();
		}
	}
}

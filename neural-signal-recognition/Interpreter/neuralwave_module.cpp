/*

CONFIGURATES THE BASIC FUNCTIONS (UPLOADING DATA SET, TRANSFERING DATA)
FOR THE NEURAL SIGNAL INTERPRETER.

*/


#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include "neuralwave.hpp"

using namespace std;

void NeuralSignal::set_signal_data(int val, int idx) {
	value = val;
	index = idx;
}
void NeuralSignal::clone(NeuralSignal src) {
	value = src.signal_value();
	index = src.signal_index();
}
int NeuralSignal::signal_value() {
	return value;
}
int NeuralSignal::signal_index() {
	return index;
}

int NeuralSignalHolder::label() {
	return data_label;
}
vector<int> NeuralSignalHolder::raw_signal() {
	return raw;
}
void NeuralSignalHolder::push_sampled_signal(vector<int> processed_matrix) {
	sampled = processed_matrix;
}
int NeuralSignalHolder::sampled_signal_datapoint(unsigned int index) {
	return sampled[index];
}
unsigned int NeuralSignalHolder::raw_size() {
	return raw_length;
}
unsigned int NeuralSignalHolder::sampled_size() {
	return sampled.size();
}
double NeuralSignalHolder::init_mse() {
	return initial_mse;
}
double NeuralSignalHolder::opt_mse() {
	return optimized_mse;
}
double NeuralSignalHolder::desired_output(int node) {
	return output[node];
}
void NeuralSignalHolder::set_initial_mse(double value) {
	initial_mse = value;
}
void NeuralSignalHolder::set_optimized_mse(double value) {
	optimized_mse = value;
}
void NeuralSignalHolder::configure_signal_output_matrix(unsigned int output_matrix_size) {
	if (data_label >= output_matrix_size) {
		cout << "this dataset's desired output is exceeding the amount of output nodes, stating that it is invalid for DNN operations" << endl;
		validated = false;
	}
	else {
		for (unsigned int i = 0; i < output_matrix_size; i++) {
			(i == data_label) ? output.push_back(1.00) : output.push_back(0.00);
		}
	}
}
void NeuralSignalInterpreter::upload_dataset(string dataset_dir, int digit) {
	int n;
	char comma[1];
	vector<int> signal_stream;

	FILE *file = fopen(dataset_dir.c_str(), "r");

	if (file == NULL) {
		cout << "ERROR: Could not open file (Wrong directory or contains no data)" << endl;
		return;
	}

	while (fscanf(file, "%d %c", &n, comma) != EOF) {
		signal_stream.push_back(n);
	}

	neural_signal_holder.push_back(NeuralSignalHolder(signal_stream, digit));
	cout << "Neural Signal Dataset Uploaded... [DIR = " << dataset_dir << "]" << endl;

	// check if currently uploaded dataset is the shorest data length
	if (neural_signal_holder[neural_signal_holder.size() - 1].raw_size() < minimum_signal_length) {
		minimum_signal_length = neural_signal_holder[neural_signal_holder.size() - 1].raw_size();
	} else {}
}

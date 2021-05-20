/*

ALL CLASSES AND DATA STRUCTURES USED FOR
THE NEURAL SIGNAL INTERPRETER MODULE

*/

#ifndef __NEURAL_SIGNAL_INTERPRETER_HPP_
#define __NEURAL_SIGNAL_INTERPRETER_HPP_

#include <iostream>
#include <string>
#include <vector>

#define MINIMUM_SAMPLING_WINDOW_SIZE 5
#define DEFAULT_SAMPLING_WINDOW_SIZE 10
#define MAXIMUM_SAMPLING_WINDOW_SIZE 25

class NeuralSignal {
private:
	int value;
	int index;
public:
	NeuralSignal() { value = 0; index = 0; }
	NeuralSignal(int val, int idx) : value(val), index(idx) {}
	void set_signal_data(int val, int idx);
	void clone(NeuralSignal src);
	int signal_value();
	int signal_index();
};

class NeuralSignalHolder {
private:
	int data_label;
	bool validated;
	unsigned int raw_length;
	double initial_mse, optimized_mse;
	std::vector<double> output;
	std::vector<int> raw; 
	std::vector<int> sampled; 
public:
	NeuralSignalHolder() {}
	NeuralSignalHolder(std::vector<int> raw_data, int label) : raw(raw_data), raw_length(raw_data.size()), data_label(label) {}
	
	int label();
	std::vector<int> raw_signal();
	void push_sampled_signal(std::vector<int> processed_matrix);
	int sampled_signal_datapoint(unsigned int index);

	unsigned int raw_size();
	unsigned int sampled_size();

	double init_mse();
	double opt_mse();
	double desired_output(int node);
	void set_initial_mse(double value);
	void set_optimized_mse(double value);
	void configure_signal_output_matrix(unsigned int output_matrix_size);
};

class NeuralSignalInterpreter: public NeuralSignalHolder {
private:
	std::vector<NeuralSignalHolder> neural_signal_holder;
	unsigned int minimum_signal_length;
	unsigned int segmented_signal_length;
public:
	NeuralSignalInterpreter() {
		minimum_signal_length = 10000; // DO NOT CHANGE THIS VALUE IN ANY CONDITION
	}
	void upload_dataset(std::string dataset_dir, int digit);
	void interpret_dataset(unsigned int sampling_range);
	std::vector<int> neural_signal_sampling(std::vector<int> raw_signal, unsigned int sampling_range);
	void train_nn_model(unsigned int iterations, double learning_rate, unsigned int amount_of_output_nodes);
};

#endif

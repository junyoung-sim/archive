#ifndef __NEURON_HPP_
#define __NEURON_HPP_

/*

THIS CLASS DEFINES THE FUNCTIONALITIES OF A NEURON
INSIDE THE DEEP NEURAL NETWORK

*/

#include <cmath>
#include <ctime>
#include <cstdlib>
#include <vector>

#define SYNAPSE_MAX 2
#define SYNAPSE_MIN -2

double sigmoid(double x);
double sigmoid_derivative(double x);

class Neuron {
private:
	double error_summation;
	double summation;
	double activation;
	unsigned int amount_of_inputs;

	std::vector<double> synapse;
	std::vector<double> adjustment;
public:
	Neuron() {}
	Neuron(unsigned int _amount_of_inputs) : amount_of_inputs(_amount_of_inputs) {
		// assign random synaptic weights to the neuron
		for (unsigned int c = 0; c < amount_of_inputs; c++) {
			synapse.push_back((SYNAPSE_MAX - SYNAPSE_MIN) * ((double)rand() / (double)RAND_MAX) + SYNAPSE_MIN);
		}

		adjustment.resize(amount_of_inputs);
		error_summation = 0.00;
		summation = 0.00;
		activation = 0.00;
	}

	void initialize_summation();
	void initialize_error_summation();
	void initialize_activation();

	void set_summation(double value); // set summation value of the neuron (automatically sets activation value)
	void add_error_sum(double value); // add up values to the error summation

	void configure_adjustment(int c, double value); // set adjustment value for specified synapse of the neuron
	void optimize(int c); // optimize the specified synapse connection

	double return_synapse(int c); // return specified synapse connection value
	double return_activation(); // return neuron's activation value
	double return_summation(); // return neuron's summation value
	double return_error_summation(); // return neuron's error summation value
};
 
#endif

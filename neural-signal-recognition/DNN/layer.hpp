#ifndef __LAYER_HPP_
#define __LAYER_HPP_

/*
THIS CLASS DEFINES THE HIDDEN LAYERS
USED INSIDE THE DEEP NEURAL NETWORK
*/

#include <vector>
#include "neuron.hpp"

#define HIDDEN_LAYER 0 // DEFAULT LAYER TYPE
#define OUTPUT_LAYER 1

class Layer : public Neuron {
private:
	unsigned int layer_type;
	unsigned int amount_of_neurons;
	unsigned int amount_of_inputs;
	std::vector<Neuron> neuron;
public:
	Layer() {}
	Layer(unsigned int _amount_of_inputs, unsigned int _amount_of_neurons, unsigned int _layer_type) :
		amount_of_inputs(_amount_of_inputs), amount_of_neurons(_amount_of_neurons), layer_type(_layer_type) {
		// create neurons for the layer
		for (unsigned int n = 0; n < amount_of_neurons; n++) {
			neuron.push_back(Neuron(amount_of_inputs));
		}

		if (layer_type != HIDDEN_LAYER && layer_type != OUTPUT_LAYER) {
			// revert the layer type to "hidden layer" when
			// the configured layer type is invalid
			layer_type = HIDDEN_LAYER;
		}
		else {}
	}

	unsigned int neurons(); // returns amount of neurons in the layer
	unsigned int inputs(); // returns amount of inputs in the layer

	void add_summation(int n, double value); // set the neuron summation
	void add_error_summation(int n, double value); // set the neuron's error summation 
	
	void reset_summation(int n); // reset the summation value of a neuron
	void reset_error_summation(int n); // reset the error summation of a neuron
	void reset_activation(int n); // reset the activation value of a neuron
	
	void set_adjustment(int n, int c, double value); // set adjustmet value to neuron's synapse
	void update_synapse(int n, int c); // update the neuron's synapse

	double synapse(int n, int c); // return synapse value
	double activation(int n); // return activation value
	double summation(int n); // return summation value
	double error_summation(int n); // return error summation value
};

#endif

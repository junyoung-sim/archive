
/*
	THIS DEFINES THE FUNCTIONALITY OF 
	HIDDEN LAYERS IN THE DEEP NEURAL NETWORK
*/

#include <iostream>
#include <vector>
#include "layer.hpp"

using namespace std;

unsigned int Layer::neurons() {
	return amount_of_neurons;
}

unsigned int Layer::inputs() {
	return amount_of_inputs;
}

void Layer::add_summation(int n, double value) {
	neuron[n].set_summation(value); // automatically normalizes in the neuron
}

void Layer::add_error_summation(int n, double value) {
	neuron[n].add_error_sum(value);
}

void Layer::reset_summation(int n) {
	neuron[n].initialize_summation();
}

void Layer::reset_error_summation(int n) {
	neuron[n].initialize_error_summation();
}

void Layer::reset_activation(int n) {
	neuron[n].initialize_activation();
}

void Layer::set_adjustment(int n, int c, double value) {
	neuron[n].configure_adjustment(c, value);
}

void Layer::update_synapse(int n, int c) {
	neuron[n].optimize(c);
}

double Layer::synapse(int n, int c) {
	return neuron[n].return_synapse(c);
}

double Layer::activation(int n) {
	return neuron[n].return_activation();
}

double Layer::summation(int n) {
	return neuron[n].return_summation();
}

double Layer::error_summation(int n) {
	return neuron[n].return_error_summation();
}

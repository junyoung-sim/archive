
/*
	THIS DEFINES THE FUNCTIONALITY OF 
	A NEURON USED IN THE DEEP NEURAL NETWORK
*/

#include <iostream>
#include <vector>
#include "neuron.hpp"

using namespace std;

double sigmoid(double x) {
	return 1 / (1 + exp(-x));
}

double sigmoid_derivative(double x) {
	return sigmoid(x) * (1 - sigmoid(x));
}

void Neuron::initialize_activation() {
	activation = 0.00;
}

void Neuron::initialize_error_summation() {
	error_summation = 0.00;
}

void Neuron::initialize_summation() {
	summation = 0.00;
}


void Neuron::set_summation(double value) {
	summation = value;
	activation = sigmoid(summation);
}

void Neuron::add_error_sum(double value) {
	error_summation += value;
}

void Neuron::configure_adjustment(int c, double value) {
	adjustment[c] = value;
}

void Neuron::optimize(int c) {
	synapse[c] += adjustment[c];
}

double Neuron::return_synapse(int c) {
	return synapse[c];
}

double Neuron::return_activation() {
	return activation;
}

double Neuron::return_summation() {
	return summation;
} 

double Neuron::return_error_summation() {
	return error_summation;
}

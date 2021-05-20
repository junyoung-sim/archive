
#ifndef __NEURON_HPP_
#define __NEURON_HPP_

#define SIGMOID_NEURON 0
#define TANH_NEURON 1
#define RELU_NEURON 2

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <vector>

double sigmoid(double val);
double sigmoid_derivative(double val);
//double tanh(double val);
//double relu(double val);
std::vector<double> softmax(std::vector<double> matrix);
std::vector<std::vector<double> > readcsv(char *name);


class Neuron {
private:
    double sum, actv;
    double error_sum;
    unsigned int amount_of_inputs, neuron_type;
    std::vector<double> synapses;
public:
    Neuron(): neuron_type(SIGMOID_NEURON), sum(0.00), actv(0.00) {}
    Neuron(unsigned int type, std::string synapse_file): neuron_type(type), sum(0.00), actv(0.00) {
        // use when uploading model
        char path[synapse_file.size() + 1];
        strcpy(path, synapse_file.c_str());
        std::vector<std::vector<double> > synapse_load = readcsv(path);
        for(unsigned int c = 0; c < synapse_load[0].size(); c++) {
            synapses.push_back(synapse_load[0][c]);
        }
    }
    Neuron(unsigned int inputs, unsigned int type): amount_of_inputs(inputs), neuron_type(type), sum(0.00), actv(0.00) {
        for(unsigned int c = 0; c < amount_of_inputs; c++) {
            // assign random synapse values
            double val = (double)rand() / RAND_MAX;
            synapses.push_back(-1.00 + val * (1.00 - (-1.00)));
        }
    }
    void configure_synapses();
    unsigned int inputs() { return amount_of_inputs; }
    unsigned int type() { return neuron_type; }
    double summation() { return sum; }
    double activation() { return actv; }
    double error_summation() { return error_sum; }
    void set_summation(double val) { sum = val; }
    void set_activation(double val) { actv = val; }
    void add_error_summation(double val) { error_sum += val; }
    void set_synapse(unsigned int c, double val) { synapses[c] = val; }
    double synapse(unsigned int idx) { return synapses[idx]; }
};

void view_neuron_attributes(Neuron neuron);

#endif

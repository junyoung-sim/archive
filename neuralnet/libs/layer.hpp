
#ifndef __LAYER_HPP_
#define __LAYER_HPP_

#include <vector>
#include "neuron.hpp"

class Layer {
private:
    unsigned int neuron_type;
    unsigned int amount_of_inputs, amount_of_neurons;
    std::vector<Neuron> neurons;
public:
    Layer() {}
    Layer(unsigned int amount_inputs, unsigned int amount_neurons, unsigned int type): amount_of_inputs(amount_inputs), amount_of_neurons(amount_neurons), neuron_type(type) {
        for(unsigned int n = 0; n < amount_neurons; n++) {
            neurons.push_back(Neuron(amount_inputs, type));
        }
    }
    unsigned int ntype() { return neuron_type; }
    unsigned int inputs() { return amount_of_inputs; }
    unsigned int number_of_neurons() { return amount_of_neurons; }
    void update_neuron(unsigned int idx, Neuron neuron) { neurons[idx] = neuron; }
    Neuron neuron(unsigned int idx) { return neurons[idx]; }
};

void view_layer_attributes(Layer layer);

#endif
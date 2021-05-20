#ifndef __MODEL_HPP_
#define __MODEL_HPP_

#include <vector>
#include <cstring>
#include "layer.hpp"

class Model {
private:
    std::vector<Layer> layer;
    std::vector<std::vector<double> > inputs;
    std::vector<std::vector<double> > outputs;
public:
    Model() {}
    Model(std::vector<Layer> layers) {
        set_layers(layers);
    }
    void set_layers(std::vector<Layer> layers) {
        layer = layers;
        for(unsigned int l = 0; l < layer.size(); l++) {
            view_layer_attributes(layer[l]);
        }
    }
    void fit(std::vector<std::vector<double> > training_input, std::vector<std::vector<double> > training_output);
    std::vector<double> evaluate(std::vector<double> input);
    void train(double learning_rate,  unsigned int epoch);
    void run(std::vector<std::vector<double> > data);
    void save(std::string model_name);
    bool load(std::string model_name);
};

#endif

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "../libs/model.hpp"

using namespace std;

int main(int argc, char **argv) {
    string mode = argv[1];
    string model_name = argv[2];
    if(mode == "train") { // train
        vector<vector<double> >  input = readcsv("input.csv");
        vector<vector<double> > output = readcsv("output.csv");
        // load model and fit input/output dataset to the model for training
        Model model;
        bool exists = model.load(model_name);
        if(!exists) {
            vector<Layer> layers;
            layers.push_back(Layer(input[0].size(), input[0].size(), SIGMOID_NEURON));
            layers.push_back(Layer(input[0].size(), input[0].size(), SIGMOID_NEURON));
            layers.push_back(Layer(input[0].size(), output[0].size(), SIGMOID_NEURON));
            // configure model with new layers
            model.set_layers(layers);
        }
        model.fit(input, output);
        model.train(0.01, 100);
        model.save(model_name);
    } else if(mode == "run") { // run
        Model model;
        model.load(model_name);
        model.run(readcsv("input.csv"));
        model.save(model_name);
    } else {}

    return 0;
}

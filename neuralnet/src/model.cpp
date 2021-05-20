#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <cmath>
#include "../libs/model.hpp"

using namespace std;

void Model::fit(vector<vector<double> > training_input, vector<vector<double> > training_output) {
    inputs = training_input;
    outputs = training_output;
    cout << "Input Dataset Size = " << inputs.size() << "x" << inputs[0].size() << endl;
    cout << "Output Dataset Size = " << outputs.size() << "x" << outputs[0].size() << endl;
    // check if the training dataset matches the size of the layers
    // if not, print a warning that results will be inaccurate
    if(inputs[0].size() != layer[0].inputs()){
        cout << "\nWARNING: INPUT dataset does not match with layer dimensions. Results of model will be inaccurate!\n\n";
    } else if(outputs[0].size() != layer[layer.size() - 1].number_of_neurons()) {
        cout << "\nWARNING: OUTPUT dataset does not match with layer dimensions. Results of model will be inaccurate!\n\n";
    } else { cout << "\n\n"; }
}

void Model::save(string model_name) {
    string save_path = model_name + "/";
    // save synapses
    for(unsigned int l = 0; l < layer.size(); l++) {
        string cmd = "cd " + save_path + "layer" + to_string(l);
        if(system(cmd.c_str()) == 0) {
            cmd = "rm -rf " + save_path + "layer" + to_string(l);
            system(cmd.c_str()); // clear all existing files
        } else {}
        cmd = "mkdir " + save_path + "layer" + to_string(l);
        system(cmd.c_str());

        for(unsigned int n = 0; n < layer[l].number_of_neurons(); n++) {
            string synapses;
            Neuron neuron = layer[l].neuron(n);
            string path = save_path + "/layer" + to_string(l) + "/neuron" + to_string(n) + ".csv";
            ofstream out(path);
            for(unsigned int c = 0; c < layer[l].inputs(); c++) {
                synapses += to_string(neuron.synapse(c));
                if(c < layer[l].inputs() - 1) synapses += ",";
            }
            out << synapses;
            out.close();
        }
    }
    // save model attributes (i.e., layer configurations)
    string cmd = "rm " + save_path + "attributes.csv";
    system(cmd.c_str());
    ofstream out(save_path + "attributes.csv");
    if(out.is_open()) {
        for(unsigned int l = 0; l < layer.size(); l++) {
            out << layer[l].inputs() << "," << layer[l].number_of_neurons() << "," << layer[l].ntype();
            if(l < layer.size() - 1) out << "\n";
        }
    } out.close();
}

bool Model::load(string model_name) {
    bool model_exists = false;
    string file = model_name + "/attributes.csv";
    char *attributes_file = new char[file.length() + 1];
    strcpy(attributes_file, file.c_str());
    vector<vector<double> > attributes = readcsv(attributes_file);
    if(attributes.size() != 0) {
        model_exists = true;
        for(unsigned int i = 0; i < attributes.size(); i++) {
            layer.push_back(Layer(attributes[i][0], attributes[i][1], attributes[i][2]));
        }
        // upload synapses
        for(unsigned int l = 0; l < layer.size(); l++) {
            for(unsigned int n = 0; n < layer[l].number_of_neurons(); n++) {
                string path = model_name + "/layer" + to_string(l) + "/neuron" + to_string(n) + ".csv";
                Neuron neuron(layer[l].ntype(), path);
                layer[l].update_neuron(n, neuron);
            }
        }
    } else {} // model does not exist (i.e., initial training)
    return model_exists;
}

vector<double> Model::evaluate(vector<double> input) {
    for(unsigned int l = 0; l < layer.size(); l++) {
        for(unsigned int n = 0; n < layer[l].number_of_neurons(); n++) {
            double sum = 0.00;
            Neuron neuron = layer[l].neuron(n);
            for(unsigned int i = 0; i < layer[l].inputs(); i++) {
                if(l == 0) { sum += neuron.synapse(i) * input[i]; }
                else {
                    Neuron input_node = layer[l - 1].neuron(i);
                    sum += neuron.synapse(i) * input_node.activation();
                }
            }
            neuron.set_summation(sum);
            if(neuron.type() == SIGMOID_NEURON) {
                neuron.set_activation(sigmoid(sum));
            } else{}
            layer[l].update_neuron(n, neuron);
        }
    }

    vector<double> output;
    for(unsigned int n = 0; n < layer[layer.size() - 1].number_of_neurons(); n++) {
        Neuron output_node = layer[layer.size() - 1].neuron(n);
        output.push_back(output_node.activation());
    }
    return output;
}

void Model::train(double learning_rate, unsigned int epoch) {
    vector<double> mse;
    double avg_network_mse = 0.00;
    for(unsigned int e = 0; e < epoch; e++) {
        for(unsigned int d = 0; d < inputs.size(); d++) {
            for(unsigned int ei = 0; ei < epoch / 10; ei++) {
                vector<double> output = evaluate(inputs[d]);
                for(int l = layer.size() - 1; l >= 0; l--) {
                    for(unsigned int n = 0; n < layer[l].number_of_neurons(); n++) {
                        double delta = 0.00;
                        Neuron neuron = layer[l].neuron(n);
                        for(unsigned int c = 0; c < layer[l].inputs(); c++) {
                            if(neuron.synapse(c) < 1.00) {
                                if(l == layer.size() - 1) {
                                    delta = (outputs[d][n] - neuron.activation()) * sigmoid_derivative(neuron.summation()) * neuron.activation();
                                    // add error summation of hidden layer to compute how much error the hidden layer contributed to the output layer's
                                    for(unsigned int _n = 0; _n < layer[l - 1].number_of_neurons(); _n++) {
                                        Neuron _neuron = layer[l - 1].neuron(_n);
                                        _neuron.add_error_summation(delta * neuron.synapse(c));
                                        layer[l - 1].update_neuron(_n, _neuron);
                                    }
                                } else { // hidden layer optimization
                                    delta = neuron.error_summation() * sigmoid_derivative(neuron.summation()) * inputs[d][c];
                                }
                                neuron.set_synapse(c, neuron.synapse(c) + learning_rate * delta); // update synapse
                            }
                        }
                        layer[l].update_neuron(n, neuron);
                    }
                }
            }
            double mse = 0.00;
            vector<double> output = evaluate(inputs[d]);
            for(unsigned int i = 0; i < layer[layer.size() - 1].number_of_neurons(); i++) {
                mse += pow((outputs[d][i] - output[i]), 2);
            }
            mse /= layer[layer.size() - 1].number_of_neurons();
            avg_network_mse += mse;
        }
        avg_network_mse /= inputs.size();
        cout << "Iteration #" << e << "   MSE = " << avg_network_mse << endl;
        mse.push_back(avg_network_mse);
        avg_network_mse = 0.00;
    }
    ofstream mse_log;
    mse_log.open("error.log");
    for(unsigned int i = 0; i < mse.size(); i++) {
        mse_log << to_string(mse[i]) + "\n";
    } mse_log.close();
}

void Model::run(vector<vector<double> > data) {
    // run model on each dataset
    vector<vector<double> > output;
    for(unsigned int i = 0; i < data.size(); i++) {
        output.push_back(evaluate(data[i]));
    }
    // write all outputs into result.csv
    ofstream out("result.csv");
    if(out.is_open()) {
        for(unsigned int i = 0; i < output.size(); i++){
            string result;
            for(unsigned int j = 0; j < output[i].size(); j++) {
                result += to_string(output[i][j] * 100);
                if(j < output[i].size() - 1) result += ",";
            }
            out << result;
            if(i < output.size() - 1) out << "\n";
        }
    } out.close();
}

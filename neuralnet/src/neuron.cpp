
#include <iostream>
#include <vector>
#include <cmath>
#include "../libs/neuron.hpp"

using namespace std;

vector<vector<double> > readcsv(char *name) {
    string line, segment;
    vector<vector<double> > data;
    ifstream file(name);

    if(file.is_open()) {
        while(getline(file, line)) {
            vector<double> data_line;
            stringstream stream(line);
            while(getline(stream, segment, ',')) {
                data_line.push_back(stod(segment));
            }
            data.push_back(data_line);
        }
    } file.close();

    cout << "Successfully read data from " << name << endl;
    return data;
}

double sigmoid(double val) {
    return 1 / (1 + exp(-val));
}

double sigmoid_derivative(double val) {
    return sigmoid(val) * (1 - sigmoid(val));
}

/*
double tanh(double val) {

}
*/

/*
double relu(double val) {

}
*/

vector<double> softmax(vector<double> matrix) {
    vector<double> probabilities;
    for(unsigned int i = 0; i < matrix.size(); i++) {
        double exp_sum = 0.00;
        for(unsigned int j = 0; j < matrix.size(); j++) {
            exp_sum += exp(matrix[j]);
        }
        probabilities.push_back(exp(matrix[i]) / exp_sum);
    }
    return probabilities;
}

void view_neuron_attributes(Neuron neuron) {
    cout << "Neuron " << &neuron << ": (Inputs=" << neuron.inputs() << ", Type=" << neuron.type() << ")"
        << ", (Summation=" << neuron.summation() << ", Activation=" << neuron.activation() << ")" << endl;
}

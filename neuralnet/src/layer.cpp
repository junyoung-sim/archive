
#include <iostream>
#include "../libs/layer.hpp"

using namespace std;

void view_layer_attributes(Layer layer) {
    cout << "Layer " << &layer << ": (Inputs=" << layer.inputs() 
        << ", Neurons=" << layer.number_of_neurons() << endl;
}
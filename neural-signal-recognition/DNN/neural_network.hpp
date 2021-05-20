
#ifndef __NERUALNETWORK_HPP_

#include <vector>
#include "layer.hpp"
#include "../Interpreter/neuralwave.hpp"

class NeuralNetwork : public Layer {
private:
	std::vector<Layer> layer;
	std::vector<NeuralSignalHolder> training_data_set;
public:
	NeuralNetwork() {}
	NeuralNetwork(std::vector<Layer> _l) : layer(_l) {}

	void upload_neural_signal_dataset(NeuralSignalHolder data);
	void variate_dataset(); // mix up the uploaded training data sets
	void sess_run(double learning_rate, unsigned int iterations);
	std::vector<double> feedforward(NeuralSignalHolder input);
	void GradientDescentOptimization(double learning_rate, unsigned int iterations);
	void save_sess();
};

#endif

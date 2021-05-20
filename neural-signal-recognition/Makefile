# Unless the .cpp files have changed their directory,
# this Makefile is always ready to blast!

COMPILER=g++
COMPILER_VERSION=-std=c++11

src=src/
interpreter=Interpreter/
dnn=DNN/

output: main.o neuralwave_module.o neuralwave_processor.o neuron.o layer.o deep_neural_network.o
	$(COMPILER) main.o neuralwave_module.o neuralwave_processor.o neuron.o layer.o deep_neural_network.o -o exec

main.o: $(src)main.cpp
	$(COMPILER) $(COMPILER_VERSION) -c $(src)main.cpp

neuralwave_module.o: $(interpreter)neuralwave_module.cpp
	$(COMPILER) $(COMPILER_VERSION) -c $(interpreter)neuralwave_module.cpp
neuralwave_processor.o: $(interpreter)neuralwave_processor.cpp
	$(COMPILER) $(COMPILER_VERSION) -c $(interpreter)neuralwave_processor.cpp

neuron.o: $(dnn)neuron.cpp
	$(COMPILER) $(COMPILER_VERSION) -c $(dnn)neuron.cpp
layer.o: $(dnn)layer.cpp
	$(COMPILER) $(COMPILER_VERSION) -c $(dnn)layer.cpp
deep_neural_network.o: $(dnn)deep_neural_network.cpp
	$(COMPILER) $(COMPILER_VERSION) -c $(dnn)deep_neural_network.cpp

clean:
	rm *.o

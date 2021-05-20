COMPILER=g++
VERSION=-std=c++11
SRC=src/

output: $(SRC)main.cpp $(SRC)neuron.cpp $(SRC)layer.cpp $(SRC)model.cpp
	$(COMPILER) $(SRC)main.cpp $(SRC)neuron.cpp $(SRC)layer.cpp $(SRC)model.cpp -o exec
clean:
	rm *.o

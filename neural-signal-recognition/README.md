# Neural Signal Recognition Algorithm (with Deep Neural Network)

Date: 2017.07.29, 
Contributor: Junyoung (Eden) Sim,
YouTube Link for this repository: ()

A neural signal (pre-frontal cortex EEG signal) recognition algorithm using a deep learning neural network engine.
The neural signal data set is collected by MindWave. MindWave has recorded EEG signals from the pre-frontal cortex generated from the brain of the test subject (David Vivancos) while exposed to visual stimulus on number digits from 0 to 9 for 2 seconds, then imaging the 
exact digit number for a while. 

In a database called "MindBigData", they have 395,072,896 EGG brain signal data points uploaded online for free.
Link to the database: http://www.mindbigdata.com/opendb/

# Compile/Run

Type in "make" in the repository file to compile all the cpp modules inside the repository.
When changing the directory of the cpp modules, you will need to manually compile all files, 
or change the contents in the Makefile.

~~~~~~~~~~~~~~~~~~~~~~~
make
./exec
~~~~~~~~~~~~~~~~~~~~~~~

# Dataset Usage

All the signal data points are stored in the directory, "NeuralSignalDataSet."
Inside the folder, there are 10 folders that store 10 text files containing neural signal data points
that represents each digit number. 

![](/Pictures/Datasetfile.jpg)

All text files are saved in the folders in this format:

~~~~~~~~~~~~~~~~~~~~~~
wave0.txt
wave1.txt
wave2.txt

. . .
. (so long, so forth)
. . .

wave9.txt
~~~~~~~~~~~~~~~~~~~~~~

Unless any information inside the data set directory is modified, the main.cpp is prepared to handle all the datasets and 
uploaded them to the algorithm for processing. 

# How the Algorithm Works

This is the basic outline of how the entire algorithm is implemented:

* Upload neural signal dataset files (main)
* Data-Preprocessing: Neural Signal Segmentation Algorithm (neural_signal_interpreter_algorithm)
* Upload processed signal datasets to deep neural network dataset
* Training the datasets in the neural network (Gradient Descent Optimizer)
* Evaluating training datasets
* Minor Tuning Process

For more detailed explanation about the algorithm and code, you may visit my YouTube video! (Link in the top of README)

# Uploading External Datasets

You can edit the main.cpp file for uploading external datasets, 
but using the bash script to upload neural signal data will be more conveinient.

~~~~~~~~~~~~
cd Shell
source upload_neural_signal.sh
upload_ns (path to repository)
~~~~~~~~~~~~

The bash script will call a Python script that asks the path to the new data file,
including its desired label. This will automatically transfer the data file 
to the NeuralSignalDataSet Archive.

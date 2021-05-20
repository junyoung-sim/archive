
import os
import numpy as np
import tensorflow as tf

os.environ ['TF_CPP_MIN_LOG_LEVEL'] = '2'

def train(dataset_pkg, output_pkg):
    """ THIS IS ONLY FOR TRAINING """ 
    training_data = np.zeros([len(dataset_pkg), len(dataset_pkg[0])])
    training_output = np.zeros([len(output_pkg), len(output_pkg[0])])

    output_matrices, output_matrix_size = training_output.shape
    amount_of_datasets, amount_of_datapoints = training_data.shape

    # upload the datasets/expected output matrices onto the numpy array
    for d in range(amount_of_datasets):
        for i in range(amount_of_datapoints):
            training_data[d][i] = dataset_pkg[d][i] # upload the dataset
        for i in range(output_matrix_size):
            training_output[d][i] = output_pkg[d][i]

    print('\nTraining Database = ', end='')
    print(training_data)

    # configuring the structure of the deep neural network
    # the configuration of the deep neural network varies based on the dataset's size
    nn_input = tf.compat.v1.placeholder(tf.float32)
    nn_output = tf.compat.v1.placeholder(tf.float32)

    hidden_layer_synapse = tf.Variable(tf.random.uniform([amount_of_datapoints, amount_of_datapoints], -1., 1.), name="hls")
    output_layer_synapse = tf.Variable(tf.random.uniform([amount_of_datapoints, output_matrix_size], -1., 1.), name="ols")

    hidden_neurons = tf.nn.tanh(tf.matmul(nn_input, hidden_layer_synapse))
    output_neurons = tf.nn.sigmoid(tf.matmul(hidden_neurons, output_layer_synapse))
    softmax = tf.nn.softmax(output_neurons)

    error = -tf.reduce_sum(nn_output * tf.math.log(tf.clip_by_value(output_neurons,1e-10,1.0)) + (1 - nn_output) * tf.math.log(tf.clip_by_value((1-output_neurons),1e-10,1.0)))
    optimizer = tf.compat.v1.train.GradientDescentOptimizer(0.001).minimize(error)

    saver = tf.compat.v1.train.Saver([hidden_layer_synapse, output_layer_synapse])
    sess = tf.compat.v1.Session()
    sess.run(tf.compat.v1.global_variables_initializer())
    
     # run the DNN optimizer
    for i in range(1000000):
        sess.run(optimizer, feed_dict = {nn_input: training_data, nn_output: training_output})
        if i % 10000 == 0:
            print('Iteration #', i, ' Neural Network Error = [', sess.run(error, feed_dict = {nn_input: training_data, nn_output: training_output}), ']')
    print('')
    saver.save(sess, "neuralwave_model")
    
def test(dataset_pkg):
    """ THIS IS FOR TESTING. ONLY IMPLEMENTED IN RUN.PY """
    input_data = np.zeros([len(dataset_pkg), len(dataset_pkg[0])])

    for d in range(len(dataset_pkg)):
        for i in range(len(dataset_pkg[d])):
            input_data[d][i] = dataset_pkg[d][i] # upload the dataset

    sess = tf.compat.v1.Session()
    restore_model = tf.compat.v1.train.import_meta_graph('neuralwave_model.meta')
    restore_model.restore(sess, tf.compat.v1.train.latest_checkpoint('./'))
    
    graph = tf.compat.v1.get_default_graph()
    nn_input = tf.compat.v1.placeholder(tf.float32)
    
    hidden_layer_synapse = graph.get_tensor_by_name("hls")
    output_layer_synapse = graph.get_tensor_by_name("ols")

    hidden_neurons = tf.nn.tanh(tf.matmul(nn_input, hidden_layer_synapse))
    output_neurons = tf.nn.sigmoid(tf.matmul(hidden_neurons, output_layer_synapse))
    softmax = tf.nn.softmax(output_neurons)

    print(sess.run(softmax, feed_dict = {nn_input: input_data}))

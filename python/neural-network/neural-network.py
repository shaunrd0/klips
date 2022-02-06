################################################################################
# Author: Shaun Reed                                                           #
# About: ANN implementation with adjustable layers and layer lengths           #
# Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com  | GitHub: shaunrd0    #
################################################################################

from matplotlib import pyplot as plt
from sklearn.datasets import load_iris
from typing import List
import argparse
import json
import math
import numpy as np
import pandas as pd  # Unused unless optional code is manually uncommented
import random
import sys
import viznet as vn


################################################################################
# CLI Argument Parser
################################################################################

# ==============================================================================

def init_parser():
    parser = argparse.ArgumentParser(
        description='Neural network implementation',
        formatter_class=argparse.RawTextHelpFormatter
    )

    parser.add_argument(
        'inputs', metavar='INPUTS', type=int, nargs='?',
        help=
        '''Number of inputs for the neural network
    (default: '%(default)s')
        ''',
        default=3
    )

    parser.add_argument(
        'perceptrons', metavar='PERCEPTRONS', type=int, nargs='?',
        help=
        '''Number of perceptrons in each hidden layer
    (default: '%(default)s')
        ''',
        default=8
    )
    
    parser.add_argument(
        'outputs', metavar='OUTPUTS', type=int, nargs='?',
        help=
        '''Number of outputs for the neural network
    (default: '%(default)s')
        ''',
        default=3
    )

    parser.add_argument(
        '--hidden-layers', '-l', metavar='HIDDEN_LAYERS', type=int, nargs='?',
        help=
        '''Number of hidden layers
    (default: '%(default)s')
        ''',
        default=1
    )

    parser.add_argument(
        '--cycles', '-c', metavar='CYCLES', type=int, nargs='?',
        help=
        '''Number of cycles to run through the network
    (default: '%(default)s')
        ''',
        default=3
    )

    parser.add_argument(
        '--learn-rate', metavar='LEARNING_RATE', type=float, nargs='?',
        help=
        '''Learning rate to use for the network.
    Must be within range of 0.0 < rate <= 1.0
    (default: '%(default)s')
        ''',
        default=0.25
    )

    parser.add_argument(
        '--bias', '-b', metavar='INITIAL_BIAS', type=float, nargs='?',
        help=
        '''The initial bias to use for perceptrons within the network.
    Must be within range of -1.0 <= bias <= 1.0
    If value is unset, bias will be initialized randomly
         ''',
    )

    parser.add_argument(
        '--weight', '-w', metavar='INITIAL_EDGE_WEIGHTS', type=float, nargs='?',
        help=
        '''The initial edge weight to use for node connections in the network
    If value is unset, edge weights will be initialized randomly
        '''
    )

    parser.add_argument(
        '--error-threshold', '--error', metavar='ERROR_THRESHOLD', type=float, nargs='?',
        help=
        '''The acceptable error threshold to use for training the network.
    (default: '%(default)s')
        ''',
        default=0.5
    )

    parser.add_argument(
        '--fire-threshold', '--fire', metavar='FIRE_THRESHOLD', type=float, nargs='?',
        help=
        '''The fire threshold for perceptrons in the network.
    If a perceptron\'s cumulative inputs reach this value, the perceptron fires
    (default: '%(default)s')
    ''',
        default=0.25
    )

    parser.add_argument(
        '--spacing', metavar='LAYER_SPACING', type=float, nargs='?',
        help=
        '''Distance between origin of network layers within visualization
    (default: '%(default)s')
        ''',
        default=2.0
    )

    parser.add_argument(
        '--horizontal', '--flip', action='store_true',
        help=
        '''The network visualization will flow left-to-right
    (default: '%(default)s')
        ''',
        default=False
    )

    parser.add_argument(
        '--silent', action='store_true',
        help=
        '''Do not show the network visualization, only print output to console
    (default: '%(default)s')
        ''',
        default=False
    )

    parser.add_argument(
        '--verbose', '-v', action='store_true',
        help=
        '''When this flag is set, error rate and change in weight will be output for each calculation
    (default: '%(default)s')
        ''',
        default=False
    )

    parser.add_argument(
        '--file', '-f', metavar='file_path', nargs='?', type=open,
        help=
        '''Optionally provide a json file to configure any option available through the cli
    json keys match --long version of each option, where --long-split option key is "long_split" in json
        ''',
    )

    return parser


################################################################################
# Neural Network
################################################################################

# ==============================================================================

def parse_file():
    """
    Validates keys in JSON file and updates CLI input context

    :return: (seq_input, seq_label) Initialized to input and label sequences in JSON file if present
    """

    # Load the JSON input file, validate keys
    file_data = json.load(context['file'])
    for key in file_data:
        if key == "input_sequence" or key == "label_sequence":
            continue
        assert key in context
    # Update the CLI context with JSON input
    context.update(file_data)

    # If JSON file provided input and label sequences, load and return them
    seq_input = seq_label = None
    if 'input_sequence' in file_data:
        seq_input = np.array(file_data['input_sequence'])
    if 'label_sequence' in file_data:
        seq_label = np.array(file_data['label_sequence'])
    return seq_input, seq_label


def network_layers():
    """
    Initialize a dictionary of layers where each layer is a list of nodes: {'input': [0, 1, 2]}
    The hidden layer in this dictionary is a list of lists for each hidden layer: {'hidden': [[3, 4, 5], [6, 7, 8]]}

    :return: A dictionary, as an example: {'input': [0, 1, 2], 'hidden': [[3, 4, 5], [6, 7, 8]], 'output': [9, 10, 11] }
    """
    inputs = [i for i in range(context["inputs"])]
    offset = context["inputs"]

    # For each hidden layer add the requested number of perceptrons
    hidden = [[] for x in range(context["hidden_layers"])]
    for x in range(context["hidden_layers"]):
        hidden[x] = [i for i in range(offset, context["perceptrons"] + offset)]
        offset += context["perceptrons"]

    outputs = [i for i in range(offset, context["outputs"] + offset)]
    offset += context["outputs"]

    layers = {"inputs": inputs, "hidden": hidden, "outputs": outputs}
    [print(f'{layer} layer: {layers[layer]}') for layer in layers]
    return layers


def random_matrix(rows, cols, low=-1.0, high=1.0):
    """ Produce a random matrix of size ROWSxCOLS using LOW and HIGH as upper and lower bounds """
    return np.random.uniform(low, high, (rows, cols))


def get_matrix_dict():
    """
    Produces a dictionary that holds edge weight transition matrices for each layer of the network
    matrix_dict['input'] maps to a single 2D matrix

    matrix_dict['hidden'] maps to a 3D matrix
    + where matrix_dict['hidden'][0] is the 2D transition matrix for the first hidden layer

    :return: A dictionary, as an example: {'input': [[...]], 'hidden': [[[...]], [[...]]], 'output': [[...]] }
    """
    if context["weight"] is None:
        # Create matrices to represent edges and weights for each layer of the network
        input_matrix = random_matrix(context["inputs"], context["perceptrons"])
        hidden_matrices = [random_matrix(context["perceptrons"], context["perceptrons"])
                           for x in range(context["hidden_layers"]-1)]
        output_matrix = random_matrix(context["perceptrons"], context["outputs"])
    else:
        # If an initial edge weight was specified, fill matrices with that value instead of generating randomly
        input_matrix = np.full((context["inputs"], context["perceptrons"]), context["weight"])
        hidden_matrices = [np.full((context["perceptrons"], context["perceptrons"]), context["weight"])
                           for x in range(context["hidden_layers"]-1)]
        output_matrix = np.full((context["perceptrons"], context["outputs"]), context["weight"])

    matrix_dict = {'input': input_matrix, 'hidden': np.array(hidden_matrices), 'output': output_matrix}
    return matrix_dict


def get_bias_dict():
    """
    Produces a dictionary that stores bias vectors for perceptrons in each layer of the network
    The hidden layer in this dictionary is a list of lists for bias in each hidden layer: {'hidden': [[...], [...]]}

    :return: A dictionary, as an example: {'input': [0.5, 0.5], 'hidden': [[0.5, 0.5 0.5], ...], 'output': [...] }
    """
    # If there was a bias provided, use it; Else use random perceptron bias
    bias = round(random.uniform(-1.0, 1.0), 2) if context["bias"] is None else context["bias"]
    # Create vectors to represent perceptron bias in each layer
    input_bias = [bias for x in range(0, context["inputs"])]
    hidden_bias = [[bias for x in range(0, context["perceptrons"])] for x in range(0, context["hidden_layers"])]
    output_bias = [bias for x in range(0, context["outputs"])]
    bias_dict = {'input': input_bias, 'hidden': hidden_bias, 'output': output_bias}
    return bias_dict


def threshold_fire(input_sum):
    """
    Applies step function using fire_threshold set by CLI to determine if perceptron is firing or not

    :param input_sum: The sum of inputs for this perceptron
    :return: A list of outputs for each perceptron in the layer. If only the first fired: [1, 0, 0, 0]
    """
    output = [1 if val > context["fire_threshold"] else 0 for val in input_sum.tolist()]
    return output


def adjust_weight(matrix_dict, out_output, label):
    """
    Back propagation for adjusting edge weights of nodes that produces incorrect output

    :param matrix_dict: A dictionary of matrices for the network produces by get_matrix_dict()
    :param out_output: The actual output for this input sequence
    :param label: The desired result for this input sequence
    :return: A dictionary of transition matrices for the network with adjusted edge weights
    """
    # Find erroneous indices
    bad_nodes = error_nodes(out_output, label)
    if len(bad_nodes) == 0:
        return matrix_dict

    # Adjust the edge weights leading to the error nodes; Don't adjust correct nodes
    for layer, mat in reversed(matrix_dict.items()):
        if layer == 'output':
            for node in bad_nodes:
                for row in range(len(mat)):
                    mod = context['learn_rate'] * (label[node] - out_output[node])  # * Input (???)
                    if context['verbose']:
                        print(f'Adjusting output weights at ({row}, {node}) with {mod}')
                    mat[row][node] += mod

        # In a fully connected neural network, all edges are updated if any output node is wrong
        # + Every node of every layer connects to every node in the next layer
        # + Any wrong node updates all edges in previous layers
        if layer == 'hidden':
            # If there are any hidden layers that do not connect to input or output layers directly
            if mat.size > 0:
                # For each hidden layer matrix, update all edge weights
                for i, hl_mat in enumerate(mat):
                    for row in range(len(hl_mat)):
                        mod = context['learn_rate']
                        for col in range(len(hl_mat[row])):
                            # print(f'Adjusting output weights at ({row}, {col}) with {mod}')
                            mat[i][row][col] += context["learn_rate"]

        if layer == 'input':
            for row in range(len(mat)):
                mod = context['learn_rate']
                for col in range(len(mat[row])):
                    # print(f'Adjusting output weights at ({row}, {col}) with {mod}')
                    mat[row][col] += mod
    return matrix_dict


def error_rate(actual_output, label):
    """
    Determines error rate for this input sequence
    Error rate is later used to determine if edge weights should be adjusted

    :param actual_output: The actual output for this input sequence
    :param label: The desired output for this input sequence
    :return: The error rate for the sequence
    """
    error_sum = 0
    for n, output in enumerate(actual_output):
        err = label[n] - output
        error_sum += math.pow(err, 2)
    err = math.sqrt(error_sum)
    return err


def error_nodes(out_output, label):
    """
    Find which output nodes are incorrect

    :param out_output: Actual output for this input sequence
    :param label: The desired output for this input sequence
    :return: A list of node indices that produced the wrong output for this sequence
    """
    # Loop through each output, check if it matches the label; If it doesn't add index to returned list
    return [i for i, output in enumerate(out_output) if output != label[i]]


def layer_pass(weight_matrix, input_vector, bias_vector):
    """
    Passes input from layer A to layer B

    :param weight_matrix: Transition matrix of edge weights where perceptrons from layer A are rows and B are columns
    :param input_vector: An input vector that represents the output from A to B
    :param bias_vector: The bias vector for perceptrons in layer B
    :return: Final output from the layer, after step function is applied in threshold_fire()
    """
    layer_edge_weights = np.array(weight_matrix).T
    prev_output = np.atleast_2d(input_vector).T
    this_layer_input = layer_edge_weights.dot(prev_output).T.flatten()
    this_layer_input += np.array(bias_vector)

    return threshold_fire(this_layer_input)


def train_network(seq_input, seq_label, bias_dict, matrix_dict):
    """
    Performs forward pass through network, moving through the number of cycles requested by the CLI

    :param seq_input: Sequence of inputs to feed into the network
    :param seq_label: Sequence of labels to verify network output and indicate error
    :param bias_dict: Dictionary of bias vectors for the perceptrons in each layer
    :param matrix_dict: Dictionary of transition matrices for the edge weights between layers in the network
    :return: Information gathered from training the network used to output final accuracy
    """
    # Info dictionary used to track accuracy
    info = {'correct': 0, 'wrong': 0, 'total': len(seq_input) * context["cycles"], 'first_acc': 0}

    # A list of error rates for each cycle
    # + These aren't used much for the program, but they hold nice data to explore while debugging
    cycle_errors = []
    cycle_outputs = [[] for x in range(context["cycles"])]
    for cycle_index in range(1, context["cycles"] + 1):
        # print(f'\nCycle number {cycle_index}')
        for seq_index in range(0, len(seq_input)):
            # One list for storing the outputs of each layer, and another to store inputs
            seq_outputs = []

            # Input layer -> Hidden layer
            # Apply input perceptron bias vector to initial inputs of the input layer
            in_input = np.array(np.array(seq_input[seq_index]) + np.array(bias_dict['input']))
            # Find output of the input layer
            in_output = threshold_fire(in_input)
            seq_outputs.append(in_output)

            # Find output for first hidden layer
            hl_output = layer_pass(matrix_dict["input"], seq_outputs[-1], bias_dict['hidden'][0])
            seq_outputs.append(hl_output)

            # For each hidden layer find inputs and outputs, up until the last hidden layer
            # + Start at 1 since we already have the output from first hidden layer
            for layer_index in range(1, context["hidden_layers"]):
                # Hidden layer -> Hidden layer
                edges = matrix_dict['hidden'][layer_index - 1]
                bias = bias_dict['hidden'][layer_index - 1]
                # Find output for hidden layer N
                hl_output = layer_pass(edges, seq_outputs[-1], bias)
                seq_outputs.append(hl_output)

            # Hidden layer -> Output layer
            # Find output for output layer
            out_output = layer_pass(matrix_dict['output'], seq_outputs[-1], bias_dict['output'])
            seq_outputs.append(out_output)

            # Forward pass through network finished
            # Find error rate for this input sequence
            err = error_rate(out_output, seq_label[seq_index])

            if context['verbose'] and err > 0:
                print(f'Error rate for sequence {seq_index} cycle {cycle_index}: {err}')
            # If error rate for this sequence is above threshold, adjust weighted edges
            if err > context["error_threshold"]:
                matrix_dict = adjust_weight(matrix_dict, out_output, seq_label[seq_index])

            # Track correctness of sequences and cycles
            if err == 0:
                info['correct'] += 1
            else:
                info['wrong'] += 1

            # Append the result to the cycle_outputs list for this cycle; -1 for 0 index array offset
            # cycle_outputs contains a list for each cycle. Each list contains N outputs for N input sequences
            cycle_outputs[cycle_index - 1].append(out_output)
            cycle_errors.append(err)

        # Move to next learning cycle in for loop
        info_total_temp = info['correct'] + info['wrong']
        if cycle_index == 1:
            info['first_acc'] = round(100.0 * float(info["correct"] / info_total_temp), 4)
        print(
            f'[Cycle {cycle_index}]   \tAccuracy: {100.0 * float(info["correct"] / info_total_temp):.4f}% \t'
            f'[{info["correct"]} / {info["wrong"]}]'
        )
        if context["verbose"]:
            for layer in matrix_dict:
                print(
                    f'Network {layer} layer: \n{matrix_dict[layer]}\n'
                    # Bias vector doesn't change, so it's not very interesting output per-cycle
                    # f'{layer} bias vector: {bias_dict[layer]}'
                )

    info['cycle_error'] = cycle_errors
    return info


def draw_graph(net_plot, net_layers, draw_horizontal=None, spacing=None):
    """
    This is the only function where viznet is used. Viznet is a module to visualize network graphs using matplotlib.
    https://viznet.readthedocs.io/en/latest/core.html
    https://viznet.readthedocs.io/en/latest/examples.html#examples

    To draw the graph, we need to at least specify the following information for-each layer in the network -
        1. The number of nodes in the layer
        2. The type of nodes that make up each layer (https://viznet.readthedocs.io/en/latest/viznet.theme.html)
        3. The distance between the center (origin) of each layer
    With this we can use viznet helper functions to draw network

    :param net_plot: A matplotlib subplot to draw the network on
    :param net_layers: A dictionary of layers that make up the network nodes
    :param draw_horizontal: True if graph should be drawn so direction flows left->right; False for bottom->top
    :param spacing: The distance between the center of origin for each layer in the network
    """
    # If no spacing was provided to the call, use spacing set by CLI
    spacing = context["spacing"] if spacing is None else spacing
    # If no draw mode was provided to the call, use mode set by CLI
    draw_horizontal = context["horizontal"] if draw_horizontal is None else draw_horizontal

    # 1. Number of nodes in each layer is provided by dictionary: len(net_layers['input'])

    # 2. Define node type to draw for each layer in the network (default ['nn.input', 'nn.hidden', nn.output])
    node_types = ['nn.input'] + ['nn.hidden'] * context["hidden_layers"] + ['nn.output']

    # 3. Use spacing distance to create list of X positions with equal distance apart (default  [0, 1.5, 3.0])
    # 1.5 * 0 = 0; 1.5 * 1 = 1.5; 1.5 * 2 = 3.0; 1.5 * 3 = 4.5; etc
    layer_pos = spacing * np.arange(context["hidden_layers"] + 2)

    # Create a sequence of Node objects using viznet helper function node_sequence
    # + Allows defining a NodeBrush for-each node, which is used by the library to style nodes
    node_sequence = []
    layer_index = 0
    for layer in net_layers:
        # If we are on the hidden layers, iterate through each
        if layer == 'hidden':
            for hl in net_layers[layer]:
                brush = vn.NodeBrush(node_types[layer_index], net_plot)
                ctr = (layer_pos[layer_index], 0) if draw_horizontal else (0, layer_pos[layer_index])
                node_sequence.append(vn.node_sequence(
                    brush, len(hl),
                    center=ctr, space=(0, 1) if draw_horizontal else (1, 0))
                )
                layer_index += 1
        else:
            brush = vn.NodeBrush(node_types[layer_index], net_plot)
            ctr = (layer_pos[layer_index], 0) if draw_horizontal else (0, layer_pos[layer_index])
            node_sequence.append(vn.node_sequence(
                brush, len(net_layers[layer]),
                center=ctr, space=(0, 1) if draw_horizontal else (1, 0))
            )
            layer_index += 1

    # Define an EdgeBrush that draws arrows between nodes using matplotlib axes
    edge_brush = vn.EdgeBrush('-->', net_plot)
    for start, end in zip(node_sequence[:-1], node_sequence[1:]):
        # Connect each node in `start` layer to each node in `end` layer
        for start_node in start:
            for end_node in end:
                # Apply the EdgeBrush using matplotlib axes and node edge tuple
                edge_brush >> (start_node, end_node)

    plt.show()


################################################################################
# Main
################################################################################

# ==============================================================================

def main(args: List[str]):
    parser = init_parser()
    global context
    context = vars(parser.parse_args(args[1:]))
    seq_input = None
    seq_label = None
    if context['file']:
        seq_input, seq_label = parse_file()

    if seq_input is None or seq_label is None:
        # You cannot provide input or label sequences via the CLI
        # If no file was provided with data, use iris dataset as example data

        # Use sklearn.dataset to grab example data
        iris = load_iris()
        # iris_data = iris.data[:, (0, 1, 2, 3)]
        iris_data = iris.data[:, (0, 2, 3)]
        # iris_data = iris.data[:, (2, 3)]
        iris_label = iris.target

        # Or read a CSV manually using pandas
        # iris = pd.read_csv('/home/kapper/Code/School/CS/AI/Assignment/two/IRIS.csv').to_dict()
        # iris_data = [[x, y] for x, y in zip(iris['petal_length'].values(), iris['petal_width'].values())]
        # iris_data = [[x, y, z] for x, y, z in zip(iris['petal_length'].values(),
        #                                           iris['petal_width'].values(),
        #                                           iris['sepal_length'].values())]
        # iris_label = [x for x in iris['species'].values()]

        # To change the number of output nodes, we need to adjust the number of labels for classification
        # iris_data = iris.data[0:99, (0, 2, 3)]
        # iris_label = [l for l in iris_label if l != 2]

        # Convert labels to: 0-> [1, 0, 0]; 1-> [0, 1, 0]; 2->[0, 0, 1]
        seq_input = iris_data
        seq_label = []
        for i, label in enumerate(set(iris_label)):
            same = [s for s in iris_label if s == label]
            for l in same:
                new_label = np.zeros(len(set(iris_label))).tolist()
                new_label[i] = 1
                seq_label.append(new_label)

    # Assert that the provided learning rate is valid
    assert(0.0 < context['learn_rate'] <= 1.0)

    # This check ensures that the number of inputs match the number of input nodes
    # + And does the same for output nodes with possible classifications
    # + But, this removes the ability to grow / shrink input / output layers through CLI
    if context["inputs"] != len(seq_input[0]):
        print(f'Warning: Input sequences each contain {len(seq_input[0])} entries '
              f'but {context["inputs"]} input nodes were requested.\n'
              f'\tUsing {len(seq_input[0])} input nodes instead of {context["inputs"]}'
              )
        context["inputs"] = len(seq_input[0])
    if context["outputs"] != len(set(map(tuple, seq_label))):
        print(f'Warning: Output labels contain {len(set(map(tuple, seq_label)))} possible classifications '
              f'but {context["outputs"]} output were nodes requested.\n'
              f'\tUsing {len(set(map(tuple, seq_label)))} output nodes instead of {context["outputs"]}'
              )
        context["outputs"] = len(set(map(tuple, seq_label)))

    # Output the problem settings
    print(f'Creating a single layer neural network: \n'
          f'\tTotal input nodes: {context["inputs"]}\n'
          f'\tNumber of perceptrons in each hidden layer: {context["perceptrons"]}\n'
          f'\tTotal output nodes: {context["outputs"]}\n'
          f'\tNumber of hidden layers: {context["hidden_layers"]}\n'
          f'\tFire threshold: {context["fire_threshold"]}\n'
          f'\tError threshold: {context["error_threshold"]}\n'
          f'\tLearn rate: {context["learn_rate"]}\n'
          f'\tInitial bias: {context["bias"] if context["bias"] is not None else "Random"}\n'
          f'\tInitial edge weights: {context["weight"] if context["weight"] is not None else "Random"}\n'
          f'Network visualization settings: \n'
          f'\tGraph visualization is enabled: {not context["silent"]}\n'
          f'\tGraph visualization is horizontal: {context["horizontal"]}\n'
          f'\tGraph visualization is vertical: {not context["horizontal"]}\n'
          f'\tGraph visualization layer spacing: {context["spacing"]}\n'
          f'\tTest data input count: {len(seq_input)}'
          )

    # Initialize a dictionary of vectors for mapping to each layer node
    # + layers['hidden'][0] = [3, 4, 5, 6] --> Hidden layer nodes are at index 3, 4, 5, 6
    layers = network_layers()

    # A dictionary where matrix_dict['input'] maps to edge weight matrix for input_layer->first_hidden_layer
    # matrix_dict['hidden'] maps to a list of matrices; matrix_dict['hidden'][0] is edge weights for first_hl->second_hl
    # matrix_dict['output'] maps to edge weight matrix for last_hl->output_layer
    matrix_dict = get_matrix_dict()
    # Randomly generate perceptron bias if none was provided through CLI
    bias_dict = get_bias_dict()

    info = train_network(seq_input, seq_label, bias_dict, matrix_dict)
    # Final console output for overall results
    info_total_temp = info['correct'] + info['wrong']
    acc = 100.0 * float(info["correct"] / info_total_temp)
    print(
        f'\nCorrect: {info["correct"]} \t Wrong: {info["wrong"]} \t Total: {context["cycles"] * len(seq_input)}'
        f'\nCycle 1 accuracy: {info["first_acc"]}% \tCycle {context["cycles"]} accuracy: {acc:.4f}%'
        f'\n{round(acc - info["first_acc"], 4)}% change over {context["cycles"]} cycles '
        f'\t{round((acc - info["first_acc"]) / context["cycles"], 4)}% average change per cycle'
    )

    # All cycles have finished; Draw the network for a visual example to go with output
    if not context["silent"]:
        draw_graph(plt.subplot(), layers)


if __name__ == "__main__":
    sys.exit(main(sys.argv))

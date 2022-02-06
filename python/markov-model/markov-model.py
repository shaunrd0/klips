################################################################################
# Author: Shaun Reed                                                           #
# About: HMM implementation to calculate most probable path for sequence       #
# Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com  | GitHub: shaunrd0    #
################################################################################

from matplotlib import pyplot as plt
from typing import List
import argparse
import itertools
import json
import networkx as nx
import numpy as np
import random
import sys


################################################################################
# CLI Argument Parser
################################################################################

# ==============================================================================

def init_parser():
    parser = argparse.ArgumentParser(
        description='Calculates most probable path of HMM given an observation sequence',
        formatter_class=argparse.RawTextHelpFormatter
    )

    parser.add_argument(
        'sequence', metavar='OBSERVATION_SEQUENCE', nargs='*',
        help=
        '''An observation sequence to calculate the most probable path
    (default: '%(default)s')
        ''',
        default=['A', 'B', 'D', 'C']
    )

    parser.add_argument(
        '--nodes', '-n', metavar='GRAPH_NODE_COUNT',type=int, nargs='?',
        help=
        '''The total number of node states in the HMM graph
    (default: '%(default)s')
        ''',
        default=4
    )

    parser.add_argument(
        '--edges', '-e', metavar='GRAPH_EDGE_COUNT',type=int, nargs='?',
        help=
        '''The total number of edges in the HMM graph
    (default: '%(default)s')
        ''',
        default=8
    )

    parser.add_argument(
        '--show-all', action='store_true',
        help=
        '''When this flag is set, all path probabilities and their calculations will be output
    (default: '%(default)s')
        ''',
        default=False
    )

    parser.add_argument(
        '--interactive', action='store_true',
        help=
        '''Allow taking input to update matrices with triple (row, col, value)
    (default: '%(default)s')
        ''',
        default=False
    )

    parser.add_argument(
        '--silent', action='store_true',
        help=
        '''When this flag is set, final graph will not be shown
    (default: '%(default)s')
        ''',
        default=False
    )

    parser.add_argument(
        '--file', '-f', metavar='FILE_PATH', nargs='?', type=open,
        help=
        '''Optionally provide file for data to be read from. Each point must be on it\'s own line with format x,y 
        ''',
    )
    return parser


################################################################################
# Helper Functions
################################################################################

# ==============================================================================

def parse_file():
    """
    Validates keys in JSON file and updates CLI input context

    Initializes a MultiDiGraph object using input data model_graph
    Initializes a matrix of emission probabilities emission_matrix
    :return: model_graph, emission_matrix
    """
    # Load the JSON input file, validate keys
    file_data = json.load(context['file'])
    for key in file_data:
        if key == "transition_matrix" or key == "emission_matrix":
            continue
        assert key in context
    # Update the CLI context with JSON input
    context.update(file_data)

    model_graph = nx.MultiDiGraph(build_graph(np.array(file_data['transition_matrix'])))
    emission_matrix = np.array(file_data['emission_matrix'])
    return model_graph, emission_matrix


def random_emission():
    """
    Initialize an emission matrix size SxE
    Where S is number of states and E is number of emissions

    :return: Initialized emission_matrix
    """
    emission_matrix = np.zeros((context["nodes"], len(set(context["sequence"]))))
    shape = emission_matrix.shape
    for row in range(0, shape[0]):
        for col in range(0, shape[1]):
            # Let random number swing below 0 to increase chance of nodes not emitting
            emit_prob = round(random.uniform(-0.25, 1.0), 2)
            emit_prob = 0.0 if  emit_prob < 0.0 else emit_prob
            emission_matrix[row][col] = emit_prob
    return emission_matrix


def random_graph(nodes, edges=2):
    """
    Create a random graph represented as a list [(from_node, to_node, {'weight': edge_weight}), ...]
    Networkx can use this list in constructors for graph objects

    :param nodes: The number of nodes in the graph
    :param edges: The number of edges connecting nodes in the graph
    :return: A list [(from_node, to_node, {'weight': edge_weight}), ...]
    """
    # By default, make twice as many edges as there are nodes
    edges *= nodes if edges == 2 else 1
    r_graph = []
    for x in range(0, edges):
        while True:
            new_edge = (
                random.randint(0, nodes - 1),  # Randomly select a from_node index
                random.randint(0, nodes - 1),  # Randomly select a to_node index
                {
                    # Randomly set an edge weight between from_node and to_node
                    'weight':
                        round(random.uniform(0.0, 1.0), 2)
                }
            )
            if not any((new_edge[0], new_edge[1]) == (a, b) for a, b, w in r_graph):
                break
        r_graph.append(new_edge)
    return r_graph


def build_graph(t_matrix):
    """
    Converts a transition matrix to a list of edges and weights
    This list can then be passed to NetworkX graph constructors

    :param t_matrix: The transition matrix to build the graph from
    :return: A list [(from_node, to_node, {'weight': edge_weight}), ...]
    """
    n_graph = []
    shape = t_matrix.shape
    for row in range(0, shape[0]):
        for col in range(0, shape[1]):
            if t_matrix[row][col] <= 0.0:
                continue
            new_edge = (row, col, {'weight': t_matrix[row][col]})
            n_graph.append(new_edge)
    return n_graph


def transition_matrix(graph: nx.MultiDiGraph):
    """
    Build a transition matrix from a Networkx MultiDiGraph object

    :param graph: An initialized MultiDiGraph graph object
    :return: An initialized transition matrix with shape (NODE_COUNT, NODE_COUNT)
    """
    # Initialize a matrix of zeros with size ExE where E is total number of states (nodes)
    t_matrix = np.zeros((context["nodes"], context["nodes"]))
    # Build matrices from iterating over the graph
    for a, b, weight in graph.edges(data='weight'):
        t_matrix[a][b] = weight
        if context["show_all"]:
            print(f'{a}->{b}: {weight}')
    return t_matrix


def make_emission_dict(emission_matrix):
    """
    Create a dictionary that maps to index keys for each emission. emission_keys
    Create a dictionary that maps to a list of emitting nodes for each emission. emission_dict

    :param emission_matrix: An emission_matrix size NxE
        Where N is the number of nodes (states) and E is the number of emissions
    :return: emission_dict, emission_keys
    """
    emission_dict = {}
    for emission in sorted(set(context["sequence"])):
        emission_dict[emission] = []
    emission_keys = dict.fromkeys(emission_dict.keys())

    # Initialize emission_dict to store a list of all nodes that emit the key value
    shape = emission_matrix.shape
    i = 0
    for key in emission_dict.keys():
        for row in range(0, shape[0]):
            if emission_matrix[row][i] > 0:
                emission_dict[key].append(row)
        emission_keys[key] = i
        i += 1
    return emission_dict, emission_keys


def int_input(prompt):
    """
    Forces integer input. Retries and warns if bogus values are entered.

    :param prompt: The initial prompt message to show for input
    :return: The integer input by the user at runtime
    """
    while True:
        try:
            value = int(input(prompt))
            break
        except ValueError:
            print("Please enter an integer value")
    return value


def triple_input(matrix):
    """
    Takes 3 integer input, validates it makes sense for the selected matrix
    If row or column selected is outside the limits of the matrix, warn and retry input until valid

    :param matrix: The matrix to use for input validation
    :return: The validated input
    """
    row = int_input("Row: ")
    col = int_input("Col: ")
    value = int_input("Value: ")
    row, col = check_input(row, col, matrix)
    return row, col, value


def check_input(row, col, matrix):
    """
    Checks that row, col input values are within the bounds of matrix
    If valid values are passed initially, no additional prompts are made.
    Retries input until valid values are input.

    :param row: The row index input by the user
    :param col: The col index input by the user
    :param matrix: The matrix to use for input validation
    :return: The validated input for row and column index
    """
    while row > matrix.shape[0] - 1:
        print(f'{row} is too large for transition matrix of shape {matrix.shape}')
        row = int_input("Row : ")
    while col > matrix.shape[1] - 1:
        print(f'{col} is too large for transition matrix of shape {matrix.shape}')
        col = int_input("Col: ")
    return row, col


################################################################################
# Hidden Markov Model
################################################################################

# ==============================================================================

def find_paths(emission_dict, t_matrix):
    """
    Find all possible paths for an emission sequence

    :param emission_dict: A dictionary of emitters for emissions {emission_1: [0, 1], emission_2: [1, 3], ...}
    :param t_matrix: A transition matrix size NxN where N is the total number of nodes in the graph
    :return: A list of validated paths for the emission given through the CLI
    """
    paths = []
    for emission in context["sequence"]:
        paths.append(emission_dict[emission])
    # Take the cartesian product of the emitting nodes to get a list of all possible paths
    # + Return only the paths which have > 0 probability given the transition matrix
    return validate_paths(list(itertools.product(*paths)), t_matrix)


def validate_paths(path_list: list, t_matrix):
    """
    Checks all paths in path_list [[0, 1, 2, 3], [0, 1, 1, 2], ...]
    If the transition matrix t_matrix indicates any node in a path can't reach the next node in path
        The path can't happen given our graph. Remove it from the list of paths.

    :param path_list: A list of paths to validate
    :param t_matrix: A transition matrix size NxN where N is the total number of nodes in the graph
    :return: A list of validated paths [[0, 1, 2, 3], [0, 1, 1, 2], ...]
    """
    valid_paths = []
    for path in path_list:
        valid = True
        for step in range(0, len(path) - 1):
            current_node = path[step]
            # If the transition matrix indicates that the chance to move to next step in path is 0
            if t_matrix[current_node][path[step+1]] <= 0.0:
                # The path cannot possibly happen. Don't consider it.
                valid = False
                break
        if valid:
            # We reached the end of our path without hitting a dead-end. The path is valid.
            valid_paths.append(path)
    return valid_paths


def find_probability(emission_matrix, t_matrix, emission_keys, valid_paths):
    """
    Find probability of paths occurring given our current HMM
    Store result in a dictionary {probability: (0, 1, 2, 3), probability_2: (0, 0, 1, 2)}

    :param emission_matrix: A matrix of emission probabilities NxE where N is the emitting node and E is the emission
    :param t_matrix: A transition matrix NxN where N is the total number of nodes in the graph
    :param emission_keys: A dictionary mapping to index values for emissions as E in the emission_matrix
    :param valid_paths: A list of valid paths to calculate probability given an emission sequence
    :return: A dictionary of {prob: path}; For example {probability: (0, 1, 2, 3), probability_2: (0, 0, 1, 2)}
    """
    path_prob = {}
    seq = list(context["sequence"])
    for path in valid_paths:
        calculations = f'Calculating {path}: '
        prob = 1.0
        for step in range(0, len(path) - 1):
            current_node = path[step]
            next_node = path[step + 1]
            emission_index = emission_keys[seq[step]]
            emission_prob = emission_matrix[current_node][emission_index]
            transition_prob = t_matrix[current_node][next_node]
            calculations += f'({emission_prob:.2f} * {transition_prob:.2f}) * '
            prob *= emission_prob * transition_prob
        emission_index = emission_keys[seq[step + 1]]
        final_emission_prob = emission_matrix[next_node][emission_index]
        prob *= final_emission_prob
        calculations += f'{final_emission_prob:.2f} = {prob:.6f}'
        if prob > 0.0:  # Don't keep paths which aren't possible due to emission sequence
            path_prob[prob] = path
        if context["show_all"]:
            print(calculations)
    return path_prob


def run_problem(transition_matrix, emission_matrix):
    """
    Runs the HMM calculations given a transition_matrix and emission_matrix

    :param transition_matrix: A matrix size NxN where N is the total number of nodes and values represent probability
    :param emission_matrix: A matrix size NxE where N is total nodes and E is total number of emissions
    :return: A dictionary of {probability: path} sorted by probability key from in descending order
    """
    # Dictionary of {emission: [emitter, ...]}
    emission_dict, emission_keys = make_emission_dict(emission_matrix)
    valid_paths = find_paths(emission_dict, transition_matrix)
    path_prob = find_probability(emission_matrix, transition_matrix, emission_keys, valid_paths)
    result = {key: path_prob[key] for key in dict.fromkeys(sorted(path_prob.keys(), reverse=True))}
    print(f'Finding most probable path for given observation sequence: {context["sequence"]}\n'
          f'\tTotal nodes in graph: {context["nodes"]}\n'
          f'\tTotal edges in graph: {context["edges"]}\n'
          f'\tNumber of sequences: {len(set(context["sequence"]))}\n'
          f'\tInteractive mode: {context["interactive"]}\n'
          f'\tEmitting nodes: {emission_dict}\n'
          f'Transition matrix: \n{transition_matrix}\n'
          f'Emission matrix: \n{emission_matrix}'
          )
    return result


def show_result(result):
    """
    Prints results from running the HMM calculations

    :param result: The result dictionary returned by run_problem()
    """
    if len(result) == 0:
        print(f'No valid paths found for sequence {context["sequence"]}')
    elif context["show_all"]:
        print(f'Final paths sorted by probability:')
        [print(f'{path} has probability:\t {prob:.6f}') for prob, path in result.items()]
    else:
        print(f'{list(result.values())[0]} has the highest probability of {list(result.keys())[0]}')


def draw_graph(graph):
    """
    Draws the model_graph for the current HMM using NetworkX

    :param graph: An initialized MultiDiGraph object with edge weights representing transition probability
    """
    # Get a dictionary of {node: position} for drawing the graph
    dict_pos = nx.spring_layout(graph)
    nx.draw(
        graph, dict_pos,
        with_labels=True,
        node_size=[x * 200 for x in dict(graph.degree).values()],
        alpha=1,
        arrowstyle="->",
        arrowsize=25,
    )
    # TODO: Fix parallel path weight display
    nx.draw_networkx_edge_labels(graph, dict_pos)
    plt.show()


################################################################################
# Main
################################################################################

# ==============================================================================

def main(args: List[str]):
    parser = init_parser()
    global context
    context = vars(parser.parse_args(args[1:]))
    if context["file"]:  # If a file was provided, use that data instead
        model_graph, emission_matrix = parse_file()
    else:
        # If no file was provided, build a random graph with the requested number of nodes and edges
        model_graph = nx.MultiDiGraph(random_graph(context["nodes"], context["edges"]))
        # Create a random emission matrix
        emission_matrix = random_emission()

    t_matrix = transition_matrix(model_graph)
    result = run_problem(t_matrix, emission_matrix)
    show_result(result)

    # Draw the graph for a visual example to go with output
    if not context["silent"]:
        draw_graph(model_graph)

    # Unless we are in interactive mode, we're finished. Return.
    if not context["interactive"]:
        return

    # Prompt to update the transition or emission matrix, then rerun problem with new values
    print("Choose matrix to update:\n\t1. Transition\n\t2. Emission\n\t3. Both", end='')
    choice = input()
    if choice == '1':
        row, col, value = triple_input(t_matrix)
        t_matrix[row][col] = value
    elif choice == '2':
        row, col, value = triple_input(emission_matrix)
        emission_matrix[row][col] = value
    elif choice == '3':
        print('\nInput for updating transition matrix')
        row, col, value = triple_input(t_matrix)
        t_matrix[row][col] = value
        print('\nInput for updating emission matrix')
        row, col, value = triple_input(emission_matrix)
        emission_matrix[row][col] = value
    result = run_problem(t_matrix, emission_matrix)
    show_result(result)

    # Draw the graph for a visual example to go with output
    if not context["silent"]:
        model_graph = nx.MultiDiGraph(build_graph(np.array(t_matrix)))
        draw_graph(model_graph)


if __name__ == "__main__":
    sys.exit(main(sys.argv))

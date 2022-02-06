################################################################################
# Author: Shaun Reed                                                           #
# About: K-Means clustering CLI                                                #
# Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com  | GitHub: shaunrd0    #
################################################################################

from ast import literal_eval
from itertools import chain
from matplotlib import pyplot as plt
from typing import List
import argparse
import math
import numpy as np
import random
import sys


################################################################################
# CLI Argument Parser
################################################################################

# ==============================================================================

def init_parser():
    parser = argparse.ArgumentParser(
        description='K-means clustering program for clustering data read from a file, terminal, or randomly generated',
        formatter_class=argparse.RawTextHelpFormatter
    )

    parser.add_argument(
        'clusters', metavar='CLUSTER_COUNT', type=int, nargs='?',
        help=
        '''Total number of desired clusters
    (default: '%(default)s')
        ''',
        default=2
    )

    parser.add_argument(
        'shift', metavar='CENTROID_SHIFT', type=float, nargs='?',
        help=
        '''Centroid shift threshold. If cluster centroids move less-than this value, clustering is finished
    (default: '%(default)s')
        ''',
        default=1.0
    )

    parser.add_argument(
        'loops', metavar='LOOP_COUNT', type=int, nargs='?',
        help=
        '''Maximum count of loops to perform clustering
    (default: '%(default)s')
        ''',
        default=3
    )

    parser.add_argument(
        '--data', '-d', metavar='X,Y', type=point, nargs='*',
        help=
        '''A list of data points separated by spaces as: x,y x,y x,y ...
    (default: '%(default)s')
        ''',
        default=[(1.0, 2.0), (2.0, 3.0), (2.0, 2.0), (5.0, 6.0), (6.0, 7.0), (6.0, 8.0), (7.0, 11.0), (1.0, 1.0)]
    )

    parser.add_argument(
        '--seeds', '--seed', '-s', metavar='X,Y', type=point, nargs='*',
        help=
        '''A list of seed points separated by spaces as: x,y x,y x,y ...
    Number of seeds provided must match CLUSTER_COUNT, or else CLUSTER_COUNT will be overriden.
        ''',
    )

    parser.add_argument(
        '--silent', action='store_true',
        help=
        '''When this flag is set, scatter plot visualizations will not be shown
    (default: '%(default)s')
        ''',
        default=False
    )

    parser.add_argument(
        '--verbose', '-v', action='store_true',
        help=
        '''When this flag is set, cluster members will be shown in output
    (default: '%(default)s')
        ''',
        default=False
    )

    parser.add_argument(
        '--random', '-r', action='store_true',
        help=
        '''When this flag is set, data will be randomly generated
    (default: '%(default)s')
        ''',
        default=False
    )

    parser.add_argument(
        '--radius', metavar='RADIUS', type=float, nargs='?',
        help=
        '''Initial radius to use for clusters
    (default: '%(default)s')
        ''',
        default=None
    )

    parser.add_argument(
        '--lock-radius', '-l', action='store_true',
        help=
        '''When this flag is set, centroid radius will not be recalculated
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

def point(arg):
    """
    Helper function for parsing x,y points provided through argparse CLI

    :param arg: A single argument passed to an option or positional argument
    :return: A tuple (x, y) representing a data point
    """
    try:
        x, y = literal_eval(arg)
        return float(x), float(y)  # Cast all point values to float
    except:
        raise argparse.ArgumentTypeError("Please provide data points in x,y format")


def random_data():
    """
    Generates random data points for testing clustering

    :return: A list of random data point tuples [(1, 1), (2, 4), ...]
    """
    data_size = random.randint(50, random.randint(100, 200))
    data = []
    for x in range(0, data_size):
        data.append((random.randint(0, 100), random.randint(0, 100)))
    return data


def round_points(points, precision=4):
    """
    Rounds all points in a list to a given decimal place

    :param points: A list of data points to round to requested decimal place
    :param precision: The decimal place to round to
    :return: A list of points where (x, y) has been rounded to match requested precision value
    """
    points = [(round(x, precision), round(y, precision)) for x,y in points]
    return points


################################################################################
# K-means Clustering
################################################################################

# ==============================================================================

def select_seeds(data):
    """
    Randomly select N seeds where N is the number of clusters requested through the CLI

    :param data: A list of data points [(0, 1), (2, 2), (1, 4), ...]
    :return: Dictionary of {seeds: radius}; For example {(2, 2): 5.0, (1, 4): 5.0}
    """
    assert(len(data) > context.clusters)
    x, y = zip(*data)
    seeds = {}  # Store seeds in a dictionary<seed, radius>
    for i in range(0, context.clusters):
        while True:
            new_seed = data[random.randint(0, len(data) - 1)]
            if new_seed not in seeds:
                break
        seeds[new_seed] = i if not context.radius else context.radius

    if context.radius:
        # An initial radius was provided and applied. Use it.
        return seeds
    else:
        # No initial radius was provided, so calculate one
        return update_clusters(seeds)


def points_average(data):
    """
    Finds average (x, y) for points in data list [(x, y), (x, y), ...]
    Used for updating cluster centroid positions

    :param data: List [(x, y), (x, y), ...]
    :return: An average (x, y) position for the list of points
    """
    x, y = 0, 0
    for pair in data:
        x += pair[0]
        y += pair[1]
    x = float(x / len(data))
    y = float(y / len(data))
    return x, y


def update_clusters(seeds, clusters=None):
    """
    Seeds {(x, y), radius} for clusters must be provided
        If no clusters {(x, y), [members, ...]} are provided, initialize cluster radius given seeds
        If clusters are provided, update centroids and radius

    :param seeds: Dictionary of {cluster_seed: radius}; Example {(x, y), radius, (x, y): radius, ...}
    :param clusters: Dictionary of {cluster_seed: member_list}; Example {(x, y): [(x, y), (x, y), ...], ...}
    :return: Cluster seeds dictionary with updates positions and radius values
    """
    radius = sys.maxsize
    new_seeds = dict()
    if clusters is None:  # If we only provided seeds, initialize their radius
        for seed in seeds:
            for other_seed in seeds.copy():
                if other_seed == seed:
                    continue
                dist = math.dist(seed, other_seed)
                # Track the smallest distance between 2 centroids
                radius = dist if dist < radius else radius

        # Update all seeds to the initial cluster radius
        radius /= 2
        for seed in seeds:
            seeds[seed] = radius
    else:
        # Update centroid positions for clusters if they were provided
        for centroid, members in clusters.items():
            cluster_data = set(members) | {centroid}
            avgX, avgY = points_average(cluster_data)
            new_seeds[tuple((avgX, avgY))] = seeds[centroid]
        # If we have passed the CLI flag to lock cluster radius, return new seeds without updating radius
        # + If we have not passed the -l flag, update cluster radius
        seeds = new_seeds if context.lock_radius else update_clusters(new_seeds)
    return seeds


def cluster_data(data, seeds):
    """
    Runs K-Means clustering on some provided data using a dictionary of cluster seeds {centroid: radius}

    :param data: A list of data points to cluster [(x, y), (x, y), ...]
    :param seeds: Dictionary of cluster centroid positions and radius {centroid: radius}
    :return: Dictionary of final clusters found {centroid: member_list, ...} and updated seeds dictionary
    """
    outliers = set()
    clusters = {}
    for seed in seeds:  # Initialize empty clusters for each seed
        # If centroid is a data point, it is also a member of the cluster
        clusters[seed] = [seed] if seed in data else []

    print(f'Updating cluster membership using cluster seeds, radius: ')
    for seed, radius in seeds.items():
        print(f'\t(({seed[0]:.4f}, {seed[1]:.4f}), {radius:.4f})')

    # For each point, calculate the distance from all seeds
    for point in data:
        for seed, radius in seeds.items():
            if point is seed:  # Do not check for distance(point, point)
                continue
            dist = math.dist(point, seed)
            if dist <= radius:  # If the distance from any cluster is within range, add point to the cluster
                # This print statement is noisy, but it can be uncommented to see output for each new cluster member
                # print(f'{point} added to cluster {seed}\n\tDistance ({dist}) is within radius ({radius})')
                # Take union of point and cluster data
                clusters.update({seed: list(set(clusters[seed]) | set([point]))})

    # Initialize outliers using difference between sets
    outliers = set(data) - (set(chain(*clusters.values())) | set(clusters.keys()))
    print(f'Outliers present: {outliers}')
    return clusters, seeds


def show_clusters(data, seeds, plot, show=True):
    """
    Shows clusters using matplotlib

    :param data: Data points to draw on the scatter plot
    :param seeds: Cluster seed dictionary {centroid: radius, ...}
    :param plot: The subplot to plot data on
    :param show: Toggles displaying a window for the plot.
        Allows two plots to be drawn on the same subplot and then shown together using a subsequent call to plt.show()
    """
    dataX, dataY = zip(*data)
    plot.set_aspect(1. / plot.get_data_ratio())

    plot.scatter(dataX, dataY, c='k')
    # Draw circles for clusters
    cs = []
    while len(cs) < context.clusters:  # Ensure we have enough colors to display all clusters
        cs.extend(['b', 'g', 'r', 'c', 'm', 'y', 'k'])
    for seed, radius, c in zip(seeds.keys(), seeds.values(), cs):
        plot.scatter(seed[0], seed[1], color=c)
        circle = plt.Circle(seed, radius, alpha=0.25, color=c)
        plot.add_patch(circle)

    plot.grid()
    if show:
        print(f'Close window to update centroid positions and re-cluster data...')
        plt.show()


def print_cluster_info(initial_clusters, seeds, centroid_diff):
    """
    Outputs some information on clusters after each iteration

    :param initial_clusters: The clusters as they were before reclustering
    :param seeds: The new seeds dictionary {centroid: radius, ...}
    :param centroid_diff: List of difference in centroid positions for each cluster
    """
    for initial_point, initial_radius, updated, radius, dist in\
            zip(initial_clusters.keys(), initial_clusters.values(), seeds.keys(), seeds.values(), centroid_diff):
        print(f'Initial cluster at ({initial_point[0]:.4f}, {initial_point[1]:.4f}) '
              f'moved to ({updated[0]:.4f}, {updated[1]:.4f})'
              f'\n\tTotal shift: {dist:.4f}'
              f'\n\tFinal radius: {radius:.4f}')
        if initial_radius != radius:
            print(f'\tInitial radius: {initial_radius:.4f}')


################################################################################
# Main
################################################################################

# ==============================================================================

def main(args: List[str]):
    parser = init_parser()
    global context
    context = parser.parse_args(args[1:])
    if context.file:  # If a file was provided, use that data instead
        context.data = [literal_eval(line.rstrip()) for line in context.file]
        context.data = [(float(x), float(y)) for x, y in context.data]
    elif context.random:  # If random flag was set, randomly generate some data
        print("TODO: Randomly generate data")
        context.data = random_data()

    print(
        f'Finding K-means clusters for given data {context.data}\n'
        f'\tUsing {context.clusters} clusters, {context.shift} max centroid shift, and {context.loops} iterations'
    )

    seeds = {}
    if context.seeds:  # Enforce CLUSTER_COUNT matching initial number of seeds
        context.clusters = len(context.seeds)
        seeds = update_clusters(dict.fromkeys(context.seeds, 0))
    else:  # Select 2 random seeds once, before we enter clustering loop
        seeds = select_seeds(context.data)

    # Save a copy of the initial clusters to show comparison at the end
    initial_clusters = seeds.copy()
    for loop in range(0, context.loops):
        print(f'\nClustering iteration {loop}')
        plt.title(f'Cluster iteration {loop}')
        # Check distance from all points to seed
        clusters, seeds = cluster_data(context.data, seeds)
        if loop > 0:  # The initial graph has no centroid shift to print
            # If we are on any iteration beyond the first, print updated cluster information
            # + The first iteration shows initial data, since it has no updated data yet
            print_cluster_info(prev_centroids, seeds, centroid_diff)
            if context.verbose:
                print(f'Cluster members:')
                for member in [f'{np.round(cent, 4)}: {members}' for cent, members in clusters.items()]:
                    print(member)
        elif loop == 0 and not context.silent:
            # If we are on the first iteration, show the initial data provided through CLI
            print(
                f'Showing initial data with {context.clusters} clusters '
                f'given seed points {round_points(seeds.keys())}'
            )

        # Show the plot for every iteration if it is not suppressed by the CLI --silent flag
        if not context.silent:
            show_clusters(context.data, seeds, plt.subplot())

        # Update centroids for new cluster data
        prev_centroids = seeds.copy()
        seeds = update_clusters(seeds, clusters)
        print(
            f'\nUpdated clusters ({round_points(prev_centroids.keys())}) '
            f'with new centroids {round_points(seeds.keys())}'
        )

        # Find the difference in position for all centroids using their previous and current positions
        centroid_diff = [round(math.dist(prev, curr), 4) for prev, curr in
                         list(zip(prev_centroids.keys(), seeds.keys()))]
        print(f'New centroids {round_points(seeds.keys())} shifted {centroid_diff} respectively')

        # If any centroid has moved more than context.shift, the clusters are not stable
        stable = not any((diff > context.shift for diff in centroid_diff))
        if stable:  # If centroid shift is not > context.shift, centroids have not changed
            break   # Stop re-clustering process and show final result

    print("\n\nShowing final cluster result...")
    centroid_diff = [round(math.dist(prev, curr), 4) for prev, curr in
                     list(zip(initial_clusters.keys(), seeds.keys()))]
    print_cluster_info(initial_clusters, seeds, centroid_diff)

    # If the clusters reached a point where they were stable, show output to warn
    if stable:
        print(
            f'\nStopping...\n'
            f'Cluster centroids have not shifted at least {context.shift}, clusters are stable'
        )

    if not context.silent:
        # Create a side-by-side subplot to compare first iteration with final clustering results
        print(f'Close window to exit...')
        f, arr = plt.subplots(1, 2)
        arr[0].set_title(f'Cluster {0} (Initial result)')
        show_clusters(context.data, initial_clusters, arr[0], False)
        arr[1].set_title(f'Cluster {loop} (Final result)')
        show_clusters(context.data, seeds, arr[1], False)
        plt.show()


if __name__ == "__main__":
    sys.exit(main(sys.argv))

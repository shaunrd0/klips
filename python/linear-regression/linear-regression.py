################################################################################
# Author: Shaun Reed                                                           #
# About: Linear regression CLI                                                 #
# Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com  | GitHub: shaunrd0    #
################################################################################

from ast import literal_eval
from matplotlib import pyplot as plt
from typing import List
import argparse
import math
import numpy as np
import sys


################################################################################
# Commandline Argument Parser
################################################################################

# ==============================================================================

def init_parser():
    parser = argparse.ArgumentParser(
        description='Find most fitting line plot for given data points and predict value given some X',
        formatter_class=argparse.RawTextHelpFormatter
    )

    parser.add_argument(
        'given', metavar='GIVEN_X', type=float, nargs='?',
        help=
        '''Value for X for prediction using linear regression
    (default: '%(default)s')
        ''',
        default=4.5
    )

    parser.add_argument(
        'data', metavar='X,Y', type=point, nargs='*',
        help=
        '''A list of data points separated by spaces as: x,y x,y x,y ...
    (default: '%(default)s')
        ''',
        default=[(1, 3), (2, 7), (3, 5), (4, 9), (5, 11), (6, 12), (7, 15)]
    )

    parser.add_argument(
        '--silent', action='store_true',
        help=
        '''When this flag is set, line plot visualization will not be shown
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


def point(arg):
    """
    Helper function for parsing x,y points provided through argparse CLI

    :param arg: A single argument passed to an option or positional argument
    :return: A tuple (x, y) representing a data point
    """
    try:
        x, y = literal_eval(arg)
        return x, y
    except:
        raise argparse.ArgumentTypeError("Please provide data points in x,y format")


################################################################################
# Linear Regression Calculation
################################################################################

# ==============================================================================

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


def points_variance(data, points_avg):
    """
    Find variance for a series of data points

    :param data: List of data points [(x, y), (x, y), ...]
    :param points_avg: Average (x, y) position for the list of points in data
    :return: Variance of X and Y for the data set as a tuple (x, y)
    """
    x, y = 0, 0
    for point in data:
        x += math.pow((point[0] - points_avg[0]), 2)
        y += math.pow((point[1] - points_avg[1]), 2)
    return x, y


def points_covariance(data, points_avg):
    """
    Find covariance between X, Y within the data set

    :param data: List of data points [(x, y), (x, y), ...]
    :param points_avg: Tuple of average X, Y for data set list
    :return: Single float value representing covariance
    """
    cov = 0
    for point in data:
        cov += (point[0] - points_avg[0]) * (point[1] - points_avg[1])
    return float(cov / (len(data) - 1))


def show_regression(data, beta, alpha):
    """
    Shows the linear regression in the matplotlib subplot
    Line drawn with Y = BX + A

    :param data: Data to show on the scatter plot
    :param beta: Value for B in the line equation
    :param alpha: Value for A in the line equation
    """
    dataX, dataY = zip(*data)
    scaleX = np.linspace(min(dataX) - 1, max(dataX) + 1, 100)
    scaleY = beta * scaleX + alpha
    plt.plot(scaleX, scaleY, c='g')
    plt.scatter(dataX, dataY, c='k')
    print(f'For X = {context.given}, Y is predicted to be {beta * context.given + alpha} ')
    plt.scatter(context.given, beta * context.given + alpha, c='#e6e600')
    plt.show()


################################################################################
# Main
################################################################################

# ==============================================================================

def main(args: List[str]):
    parser = init_parser()
    global context
    context = parser.parse_args(args[1:])
    print(f'Finding fitting line plot for given data {context.data}')
    if context.file:  # If a file was provided, use that data instead
        context.data = [literal_eval(line.rstrip()) for line in context.file]
        context.data = [(float(x), float(y)) for x, y in context.data]

    # Find the average for the data X and Y points
    data_avg = points_average(context.data)
    print(f'points_avg: {data_avg}')

    # Find the variance for the data X and Y points
    data_variance = points_variance(context.data, data_avg)
    print(f'variance: {data_variance}')

    # Find the standard deviations for X and Y values
    data_sigma = (math.sqrt(float(data_variance[0] / (len(context.data) - 1))),
                  math.sqrt(float(data_variance[1] / (len(context.data) - 1))))
    print(f'sigma: {data_sigma}')

    # Find the covariance between X, Y within data set
    data_covariance = points_covariance(context.data, data_avg)
    print(f'covariance: {data_covariance}')

    # Find correlation between X, Y within data set
    data_correlation = (1.0/math.prod(data_sigma)) * data_covariance
    print(f'correlation: {data_correlation}')

    # Find equation for linear regression for the given data set
    print(f'Our line Y = BX + A must pass through the point {data_avg}')
    data_beta = data_correlation * float(data_sigma[1] / data_sigma[0])
    data_alpha = data_avg[1] - data_beta * data_avg[0]
    print(f'Y = ({data_beta})X + {data_alpha}')

    # Show the final graph produced by linear regression calculations
    # + Predicts the Y value, given the X value provided through the CLI
    if not context.silent:
        show_regression(context.data, data_beta, data_alpha)


if __name__ == "__main__":
    sys.exit(main(sys.argv))

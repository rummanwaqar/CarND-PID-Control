#!/usr/bin/env python

import sys
import csv
import matplotlib.pyplot as plt

def read_csv(filename):
    data = []
    with open(filename) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        for row in csv_reader:
            data.append([float(x) for x in row])
    return data

def plot(kp, ki, kd, cte, cte_diff, cte_sum, effort):
    ax1=plt.subplot(2, 2, 1)
    ax1.plot(cte)
    plt.title('CTE')
    ax2=plt.subplot(2, 2, 2)
    ax2.plot(effort, 'b')
    plt.title('effort')
    ax3=plt.subplot(2, 2, 3)
    ax3.plot(cte_diff)
    plt.title('CTE diff')
    ax4=plt.subplot(2, 2, 4)
    ax4.plot(cte_sum)
    plt.title('CTE sum')
    # plt.title('kp:{:.3f}, kd:{:.3f}, ki:{:.3f}'.format(kp, kd, ki))
    plt.show()

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("Usage plot.py csvfile")
        exit(0)

    csv_file = sys.argv[1]
    data = read_csv(csv_file)
    plot(data[0][4], data[0][5], data[0][6], [x[0] for x in data],
        [x[1] for x in data], [x[2] for x in data], [x[3] for x in data])

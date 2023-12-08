import matplotlib.pyplot as plt

with open('resultss.txt', 'r') as f:
    #fig = plt.figure()
    xs  = []
    y1s = []
    y1fast = []
    line = f.readline()
    line = f.readline()
    line = f.readline()
    while True:
        line = f.readline()
        if line[0] == '-':
            break
        line = line.split(',')
        xs.append(float(line[0]))
        y1s.append(float(line[1]))
        y1fast.append(float(line[2][:-1]))

    plt.title("2 vs 1 Variant. treshold = 100")
    plt.xlabel("matrix size")
    plt.ylabel("time, msecs")
    plt.scatter(xs, y1s, label="Slow")
    plt.scatter(xs, y1fast, label="Fast")
    plt.legend()
    plt.show()

    line = f.readline()
    line = f.readline()

    xs  = []
    y1s = []
    y2fast = []

    while True:
        line = f.readline()
        if line[0] == '-':
            break
        line = line.split(',')
        xs.append(float(line[0]))
        y1s.append(float(line[1]))
        y2fast.append(float(line[2][:-1]))

    plt.title("2 vs 1 Variant. treshold = 200")
    plt.xlabel("matrix size")
    plt.ylabel("time, msecs")
    plt.scatter(xs, y1s, label="Slow")
    plt.scatter(xs, y2fast, label="Fast")
    plt.legend()
    plt.show()

    line = f.readline()
    line = f.readline()

    xs  = []
    y1s = []
    y3fast = []

    while True:
        line = f.readline()
        if line[0] == '-':
            break
        line = line.split(',')
        xs.append(float(line[0]))
        y1s.append(float(line[1]))
        y3fast.append(float(line[2][:-1]))

    plt.title("2 vs 1 Variant. treshold = 50")
    plt.xlabel("matrix size")
    plt.ylabel("time, msecs")
    plt.scatter(xs, y1s, label="Slow")
    plt.scatter(xs, y3fast, label="Fast")
    plt.legend()
    plt.show()

    line = f.readline()
    line = f.readline()

    xs  = []
    y1s = []
    y4fast = []

    while True:
        line = f.readline()
        if line == '':
            break
        line = line.split(',')
        xs.append(float(line[0]))
        y1s.append(float(line[1]))
        y4fast.append(float(line[2][:-1]))

    plt.title("2 vs 1 Variant. treshold = 300")
    plt.xlabel("matrix size")
    plt.ylabel("time, msecs")
    plt.scatter(xs, y1s, label="Slow")
    plt.scatter(xs, y4fast, label="Fast")
    plt.legend()
    plt.show()

    plt.title("Fast variant for all treshold")
    plt.xlabel("matrix size")
    plt.ylabel("time, msecs")
    plt.scatter(xs, y1fast, label="100")
    plt.scatter(xs, y2fast, label="200")
    plt.scatter(xs, y3fast, label="50")
    plt.scatter(xs, y4fast, label="300")
    plt.legend()
    plt.show()
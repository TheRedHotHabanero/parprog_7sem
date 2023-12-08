import matplotlib.pyplot as plt

with open('results.txt', 'r') as f:
    #fig = plt.figure()
    xs  = []
    y1s = []
    y2s = []
    line = f.readline()
    line = f.readline()
    line = f.readline()
    while True:
        line = f.readline()
        if line[0] == '-':
            break
        line = line.split(',')
        xs.append(int(line[0]))
        y1s.append(int(line[1]))
        y2s.append(int(line[2][:-1]))

    plt.title("Boosted seq vs boosted par")
    plt.xlabel("matrix size")
    plt.ylabel("time, msecs")
    plt.scatter(xs, y1s, label="Boosted seqential")
    plt.scatter(xs, y2s, label="Boosted parallel")
    plt.show()

    line = f.readline()
    line = f.readline()

    xs  = []
    y1s = []
    y2s = []

    while True:
        line = f.readline()
        if line[0] == '-':
            break
        line = line.split(',')
        xs.append(int(line[0]))
        y1s.append(int(line[1]))
        y2s.append(int(line[2][:-1]))

    plt.title("Boosted parallel vs trivial parallel")
    plt.xlabel("matrix size")
    plt.ylabel("time, msecs")
    plt.scatter(xs, y1s, label="Trivial parallel")
    plt.scatter(xs, y2s, label="Boosted parallel")
    plt.show()

    xs  = []
    y1s = []

    line = f.readline()
    line = f.readline()
    while True:
        line = f.readline()
        if line == "":
            break
        line = line.split(',')
        xs.append(int(line[0]))
        y1s.append(int(line[1][:-1]))
    
    plt.title("Boosted par for some fixed matrix sizes")
    plt.xlabel("matrix size")
    plt.ylabel("time, msecs")
    plt.scatter(xs, y1s)
    plt.show()
import matplotlib.pyplot as plt


CACHE_BENCH = 'cache_bench.out'
MEM_BENCH = 'mem_bench.out'
WIDTH_TIME_BENCH = 'width_time.out'
DEPTH_TIME_BENCH = 'depth_time.out'
NODE_TIME_BENCH = 'node_time.out'
RESULTS_LOCATION = '../results/'


def read_cache_bench_results():
    x = []
    y = []
    with open(RESULTS_LOCATION + CACHE_BENCH) as file:
        lines = file.readlines()

    for line in lines:
        line = line.strip()
        index, value = line.split(' ')
        index = int(index)
        value = float(value.replace(',', '.'))
        x.append(index)
        y.append(value)

    return x, y


def read_mem_bench_results():
    x = []
    y = []
    with open(RESULTS_LOCATION + MEM_BENCH) as file:
        lines = file.readlines()

    for line in lines:
        line = line.strip()
        index, value = line.split(' ')
        index = int(index)
        value = int(value)
        x.append(index)
        y.append(value)

    return x, y

def read_mem_bench_results():
    x = []
    y = []
    with open(RESULTS_LOCATION + MEM_BENCH) as file:
        lines = file.readlines()

    for line in lines:
        line = line.strip()
        index, value = line.split(' ')
        index = int(index)
        value = int(value)
        x.append(index)
        y.append(value)

    return x, y


def read_width_time_bench_results():
    x = []
    y = []
    with open(RESULTS_LOCATION + WIDTH_TIME_BENCH) as file:
        lines = file.readlines()

    for line in lines:
        line = line.strip()
        index, mean, median = line.split('\t')
        index = int(index)
        mean = float(mean)
        median = float(median)
        x.append(index)
        y.append(median)

    return x, y

def read_depth_time_bench_results():
    x = []
    y = []
    with open(RESULTS_LOCATION + DEPTH_TIME_BENCH) as file:
        lines = file.readlines()

    for line in lines:
        line = line.strip()
        index, mean, median = line.split('\t')
        index = int(index)
        mean = float(mean)
        median = float(median)
        x.append(index)
        y.append(median)

    return x, y


def read_node_time_bench_results():
    x = []
    y = []
    z = []
    with open(RESULTS_LOCATION + NODE_TIME_BENCH) as file:
        lines = file.readlines()

    for line in lines:
        line = line.strip()
        index, mean, median, node_mean, node_median = line.split('\t')
        index = int(index)
        mean = float(mean)
        median = float(median)
        node_mean= float(node_mean)
        node_median = float(node_median)
        x.append(index)
        y.append(median)
        z.append(node_median)

    return x, y, z


def draw_cache_bench():
    x, y = read_cache_bench_results()
    plt.plot(x, y, '--bo')
    plt.title("Cache misses")
    plt.ylabel("Procent odwołań do danych, których nie było w p. podręcznej")
    plt.xlabel("Parametr g")


def draw_mem_bench():
    x, y = read_mem_bench_results()
    plt.plot(x, y, '--bo')
    plt.title("Użycie pamięci, a rozmiar grafu")
    plt.ylabel("Użycie pamięci [B]")
    plt.xlabel("Parametr g")


def draw_width_time_bench():
    x, y = read_width_time_bench_results()
    plt.plot(x, y, '--bo')
    plt.title("Czas obliczeń, a rozmiar grafu")
    plt.ylabel("Czas obliczeń [ms]")
    plt.xlabel("Parametr g")

def draw_depth_time_bench():
    x, y = read_depth_time_bench_results()
    plt.plot(x, y, '--bo')
    plt.title("Czas obliczeń, a ilość warstw grafu")
    plt.ylabel("Czas obliczeń [ms]")
    plt.xlabel("Parametr lambda")


def draw_const_vertices_time_bench():
    x, y, _ = read_node_time_bench_results()
    plt.plot(x, y, '--bo')
    plt.title("Czas obliczania dla stałej ilości wierzchołków w grafie")
    plt.ylabel("Czas obliczeń [ms]")
    plt.xlabel("Parametr g")

def draw_node_time_bench():
    x, _, y = read_node_time_bench_results()
    plt.plot(x, y, '--bo')
    plt.title("Czas obliczania dla pojedynczego wierzchołka")
    plt.ylabel("Czas obliczeń [ms]")
    plt.xlabel("Parametr g")


def draw_benchmarks():
    plt.subplot(111)
    draw_cache_bench()

    plt.tight_layout()
    plt.show()

    plt.subplot(111)
    draw_mem_bench()

    plt.tight_layout()
    plt.show()

    plt.subplot(111)
    draw_width_time_bench()

    plt.tight_layout()
    plt.show()

    plt.subplot(111)
    draw_depth_time_bench()

    plt.tight_layout()
    plt.show()

    plt.subplot(111)
    draw_node_time_bench()

    plt.tight_layout()
    plt.show()

    plt.subplot(111)
    draw_const_vertices_time_bench()

    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    draw_benchmarks()

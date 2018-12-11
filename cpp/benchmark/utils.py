

def bytes_to_human(num, suffix='B'):
    for unit in ['','Ki','Mi','Gi','Ti','Pi','Ei','Zi']:
        if abs(num) < 1024.0:
            return "%3.1f%s%s" % (num, unit, suffix)
        num /= 1024.0
    return "%.1f%s%s" % (num, 'Yi', suffix)


def expected_memory_usage(width, hash_func="sha256"):
    digest_size = 256 / 8
    uint_size = 64 / 8
    hash_elements_size = 2 * (2 ** width) * digest_size
    graph_structure_size = 2 * width * (2 ** width) * uint_size

    print(bytes_to_human(hash_elements_size))
    print(bytes_to_human(graph_structure_size))

    return hash_elements_size + graph_structure_size

//
// Created by konrad on 09.12.18.
//

#include "riffle_scrambler.cpp"
#include "utils.cpp"
#include "progress_bar.cpp"

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>


using namespace std;

const string WIDTH_TIME_OUT_FILE_NAME = "width_time.out", NODE_TIME_OUT_FILE_NAME = "node_time.out";


void benchmark_riffle_scrambler_width_time() {
    progress_bar bar{cout, 70, "Width time"};
    const uint64_t max_graph_width = 20, repetitions = 10, graph_depth = 2;
    
    vector<vector<double>> execution_times{max_graph_width + 1};
    
    for(uint64_t graph_width = 1; graph_width <= max_graph_width; graph_width++) {
        for(int i = 0; i < repetitions; i++) {
            double execution_time = benchmark_riffle_scrambler_call(graph_width, graph_depth);
            execution_times[graph_width].push_back(execution_time);
        }

        sort(execution_times[graph_width].begin(), execution_times[graph_width].end());

        bar.write(double(graph_width) / double(max_graph_width));
    }

    ofstream results_file;
    results_file.open(WIDTH_TIME_OUT_FILE_NAME);

    results_file << "Execution time for different graph width (depth: " << graph_depth << ")" << endl;
    results_file << "Width\tMean\tMedian"  << endl;
    for(int i = 1; i <= max_graph_width; i++) {
        results_file << i << "\t" << get_mean(execution_times[i]) << "\t" << get_median(execution_times[i]) << endl;
    }

    results_file.close();
}

void benchmark_riffle_scrambler_node_time() {
    const uint64_t max_graph_width = 20, vertices = 8000000, repetitions = 10;
    progress_bar bar{cout, 70, "Node time"};

    vector<vector<double>> execution_times{max_graph_width + 1};

    for(uint64_t graph_width = 1; graph_width <= max_graph_width; graph_width++) {
        for(int i = 0; i < repetitions; i++) {
            const uint64_t graph_depth = get_depth_for_width_and_vertices(graph_width, vertices);
            double execution_time = benchmark_riffle_scrambler_call(graph_width, graph_depth);
            execution_times[graph_width].push_back(execution_time);

            bar.write((double(graph_width - 1) + double(i) / double(repetitions))/ double(max_graph_width));
        }

        sort(execution_times[graph_width].begin(), execution_times[graph_width].end());

        bar.write(double(graph_width) / double(max_graph_width));
    }

    ofstream results_file;
    results_file.open(NODE_TIME_OUT_FILE_NAME);

    results_file << "Execution time for different graph width with constant vertices number (" << vertices << ")" << endl;
    results_file << "Width\tMean\tMedian\tNode mean\tNode median"  << endl;
    for(int i = 1; i <= max_graph_width; i++) {
        uint64_t ui = static_cast<uint64_t>(i);
        const auto mean = get_mean(execution_times[i]);
        const auto median = get_median(execution_times[i]);
        const auto node_mean = get_time_per_node_vertices(mean, ui, vertices);
        const auto node_median = get_time_per_node_vertices(median, ui, vertices);

        results_file << i << "\t" << mean << "\t" << median << "\t" << node_mean << "\t" << node_median << endl;
    }

    results_file.close();
}

void run_riffle_shuffle_for_given_vertices(const uint64_t width, const uint64_t vertices) {
    uint64_t graph_depth = get_depth_for_width_and_vertices(width, vertices);
    cout << "Calculating RF for " << width << " and " << graph_depth << endl;
    double execution_time = benchmark_riffle_scrambler_call(width, graph_depth);
}


int main(int argc, char **argv) {

    if(argc > 1) {
        const string arg = argv[1];
        const int width = stoi(arg);

        if(argc == 3) {
            const string arg = argv[2];
            const int depth = stoi(arg);
            benchmark_riffle_scrambler_call(width, depth);
        } else if(argc == 2){
            run_riffle_shuffle_for_given_vertices(static_cast<uint64_t >(width), 10000000);
        }

        return 0;
    }

    benchmark_riffle_scrambler_width_time();
    benchmark_riffle_scrambler_node_time();

    return 0;
}


//
// Created by konrad on 10.12.18.
//

#include <vector>
#include <numeric>

#include <iostream>

template <typename T>
T get_median(const std::vector<T> &v) {
    const auto size = v.size();
    T median;
    if ((size % 2) == 0) {
        median = (v[size / 2 - 1] + v[size / 2]) / T(2);
    } else {
        median = v[size / 2];
    }

    return median;
}

template <typename T>
T get_mean(const std::vector<T> &v) {
    const auto size = v.size();
    const T sum = std::accumulate(v.begin(), v.end(), T(0));

    return sum / size;
}
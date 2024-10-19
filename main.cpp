#include "io.hpp"

#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>
#include <iterator>
#include <cassert>
using namespace std;

const int D = 13;
const int INPUT_SIZE = 8192;
vector<long double> x[INPUT_SIZE];
vector<long double> y(INPUT_SIZE);
vector<int> vid(INPUT_SIZE);

mt19937 rnd(time(nullptr));

struct RESULT {
    vector<long double> w;
    long double E_in, E_out;
    RESULT() {}
    RESULT(vector<long double> _w, long double _E_in, long double _E_out) : w(_w), E_in(_E_in), E_out(_E_out) {}
};

RESULT make_experiment(int N) {
    vector<int> selected_id;
    sample(vid.begin(), vid.end(), back_inserter(selected_id), N, rnd);
    MATRIX X(N, D);
    vector<long double> Y(N);
    for (int i = 0; i < N; i++) {
        X[i] = x[selected_id[i]];
        Y[i] = y[selected_id[i]];
        #ifdef POP_TO_2
        while (X[i].size() > 3) X[i].pop_back();
        #endif
    }
    X.transpose();
    MATRIX XTX = X * X;
    XTX.invert();
    XTX.transpose();
    vector<long double> w = XTX * (X * Y);
    long double E_in = 0, E_out = 0;
    int id = 0;
    for (int i = 0; i < INPUT_SIZE; i++) {
        long double dif = w * x[i] - y[i];
        if (id < N && i == selected_id[id]) {
            E_in += dif * dif;
            id++;
        } else {
            E_out += dif * dif;
        }
    }
    E_in /= N;
    E_out /= (INPUT_SIZE - N);
    return RESULT(w, E_in, E_out);
}

int main(int argc, char *argv[]) {
    iota(vid.begin(), vid.end(), 0);
    ofstream output(argv[1]);
    for (int i = 0; i < INPUT_SIZE; i++) {
        x[i].resize(D);
        string s;
        getline(cin, s);
        convert_string_to_vec(s, x[i], y[i]);
    }
    int EXPERIMENT_COUNT;
    vector<int> N;
    #ifdef MULTIPLE_N
    EXPERIMENT_COUNT = 16;
    for (int i = 25; i <= 2000; i += 25) N.push_back(i);
    #else
    EXPERIMENT_COUNT = 1126;
    N.push_back(32);
    #endif
    for (auto n : N) {
        #ifdef PRINT
        cout << "--- N = " << n << " ---" << '\n';
        #endif
        for (int i = 1; i <= EXPERIMENT_COUNT; i++) {
            RESULT result = make_experiment(n);
            #ifdef PRINT
            cout << "experiment #" << i << ": " << '\n';
            cout << "(E_in, E_out) = (" << result.E_in << ", " << result.E_out << ')' << '\n';
            #endif
            output << result.E_in << ' ' << result.E_out << '\n';
        }
    }
    return 0;
}
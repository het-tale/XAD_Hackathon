/* Listing 3: Benchmark code for Frobenius norm performance of MatrixView */

#include <random>
#include <chrono>
#include <iostream>
#include "../include/Matrix.hpp"
#include "../include/MatrixView.hpp"
#include "../include/fornebius.hpp"


void ft_listing_3() {
	constexpr int N = 10000;
	constexpr int M = 1000;
	// create a big matrix of NxN
	Matrix m(N, N);

	std::default_random_engine eng(1234);
	std::uniform_real_distribution<double> dist(-1.0, 1.0);
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			m(i, j) = dist(eng);
		}
	}
	auto stop = std::chrono::high_resolution_clock::now();
	auto t_init = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() * 1e-3;

	double sum = 0.0;
	// calculate Frobenius norms of rectangular tiles of different sizes
	std::uniform_int_distribution<int> startdist(0, N - M), spandist(1, M);
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 1000; ++i) {
		int starti = startdist(eng);
		int startj = startdist(eng);
		int spani = spandist(eng);
		int spanj = spandist(eng);

		MatrixView mv(m, starti, startj, spani, spanj);

		// use the result to avoid aggressive compiler to optimise out the loop.
		sum += frobeniusNorm(mv);
	}
	stop = std::chrono::high_resolution_clock::now();
	auto t_comp = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() * 1e-3;

	std::cout << "init time = " << t_init << "ms\n" << "run time = " << t_comp << "ms\n" << "sum = " << sum << "\n";
}

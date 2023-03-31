#include "sparse.hpp"
#include <chrono>
#include <execution>

#ifndef UTIL_HPP
#define UTIL_HPP

template <typename T, template<typename> class MatrixType>
double getTime(const MatrixType<T>& A, int runs)
{
	// Create vector of ones
	std::vector<T> y;
	int n = A.getN();
	std::vector<T> x(n,1);

	const double msToS = 1.0e-6;
	auto t1 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < runs; i++)
	{
		y = A.pow(x,1000);
	}
	auto t2 = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1);
	return msToS*elapsed.count()/runs;
}

template <typename T, template<typename> class MatrixType>
double getTime_par(const MatrixType<T>& A, int runs)
{
	// Create vector of ones
	std::vector<T> y;
	int n = A.getN();
	std::vector<T> x(n,1);

	const double msToS = 1.0e-6;
	auto t1 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < runs; i++)
	{
		y = A.pow_par(std::execution::par_unseq,x,1000);
	}
	auto t2 = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1);
	return msToS*elapsed.count()/runs;
}

template <typename Policy,typename T, template<typename> class MatrixType>
double getTime_par(Policy&& policy, const MatrixType<T>& A, int runs)
{
	// Create vector of ones
	std::vector<T> y;
	int n = A.getN();
	std::vector<T> x(n,1);

	const double msToS = 1.0e-6;
	auto t1 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < runs; i++)
	{
		y = A.pow_par(policy,x,10000);
	}
	auto t2 = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1);
	return msToS*elapsed.count()/runs;
}

#endif

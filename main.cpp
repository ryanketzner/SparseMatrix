#include "sparse.hpp"
#include <chrono>

template <typename T>
double getTime(const SparseMatrix<T>& A, int runs)
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

int main()
{
	std::string ibm = "../input/ibm32.mtx";
	std::string memplus = "../input/memplus.mtx";
	std::string pwt = "../input/pwt.mtx";
	std::string goodwin = "../input/goodwin.mtx";

	SparseMatrix<bool> A(ibm);
	SparseMatrix<float> A_2(goodwin);
	SparseMatrix<float> A_3(memplus);
	SparseMatrix<float> A_4(pwt);

	// Since execution time is small, ibm is averaged over ten runs
	double t_ibm = getTime(A,10);
	std::cout << "IBM Time (s): " << t_ibm << std::endl;

	double t_goodwin = getTime(A_2,1);
	std::cout << "Goodwin Time (s): " << t_goodwin << std::endl;

	double t_memplus = getTime(A_3,1);
	std::cout << "Memplus Time (s): " << t_memplus << std::endl;

	double t_pwt = getTime(A_4,1);
	std::cout << "PWT Time (s): " << t_pwt << std::endl;

	return 0;
}
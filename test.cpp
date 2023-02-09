#include "sparse.hpp"
#include <chrono>

int main()
{
	std::string ibm = "../input/ibm32.mtx";
	std::string memplus = "../input/memplus.mtx";
	std::string pwt = "../input/pwt.mtx";
	std::string goodwin = "../input/goodwin.mtx";

	SparseMatrix<bool> A(ibm);
	std::vector<bool> x(6,1);

	std::vector<bool> y;

	int runs = 100;
	auto t1 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < runs; i++)
	{
		y = A.pow(x,1000);
	}
	auto t2 = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1);
	std::cout << elapsed.count()/runs << std::endl;

	SparseMatrix<float> A_2(memplus);
	std::vector<float> x_2(17758,1.0);
	std::vector<float> y_2;

	runs = 3;
	t1 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < runs; i++)
	{
		y_2 = A_2.pow(x_2,1000);
	}
	t2 = std::chrono::high_resolution_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1);
	std::cout << elapsed.count()/runs << std::endl;

	SparseMatrix<float> A_3(goodwin);
	std::vector<float> x_3(7320,1.0);
	std::vector<float> y_3;

	runs = 3;
	t1 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < runs; i++)
	{
		y_3 = A_3.pow(x_3,1000);
	}
	t2 = std::chrono::high_resolution_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1);
	std::cout << elapsed.count()/runs << std::endl;

	SparseMatrix<float> A_4(pwt);
	std::vector<float> x_4(36519,1.0);
	std::vector<float> y_4;

	runs = 3;
	t1 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < runs; i++)
	{
		y_4 = A_4.pow(x_4,1000);
	}
	t2 = std::chrono::high_resolution_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1);
	std::cout << elapsed.count()/runs << std::endl;

	return 0;
}
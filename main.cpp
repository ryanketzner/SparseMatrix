#include "sparse.hpp"
#include "tjds.hpp"
#include "util.hpp"

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

	TJDS<bool> A_t(ibm);
	TJDS<float> A_2t(goodwin);
	TJDS<float> A_3t(memplus);
	TJDS<float> A_4t(pwt);

	//Since execution time is small, ibm is averaged over ten runs
	t_ibm = getTime(A_t,10);
	std::cout << "IBM Time (s): " << t_ibm << std::endl;

	t_goodwin = getTime(A_2t,1);
	std::cout << "Goodwin Time (s): " << t_goodwin << std::endl;

	t_memplus = getTime(A_3t,1);
	std::cout << "Memplus Time (s): " << t_memplus << std::endl;

	t_pwt = getTime(A_4t,1);
	std::cout << "PWT Time (s): " << t_pwt << std::endl;

	return 0;
}
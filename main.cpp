#include "sparse.hpp"
#include "tjds.hpp"
#include "util.hpp"

int main()
{
	std::string ibm = "../input/ibm32.mtx";
	std::string memplus = "../input/memplus.mtx";
	std::string pwt = "../input/pwt.mtx";
	std::string goodwin = "../input/goodwin.mtx";
	std::string curtis54 = "../input/curtis54.mtx";

	SparseMatrix<bool> A(ibm);
	SparseMatrix<float> A_2(goodwin);
	SparseMatrix<float> A_3(memplus);
	SparseMatrix<float> A_4(pwt);
	SparseMatrix<bool> A_5(curtis54);

	// Since execution time is small, ibm is averaged over ten runs
	double t_ibm = getTime(A,50);
	std::cout << "CSR IBM Time (s): " << t_ibm << std::endl;
	double flops = 2*A.get_nnz()/t_ibm;
	std::cout << "FLOPS: " << flops << std::endl;

	double t_goodwin = getTime(A_2,10);
	std::cout << "CSR Goodwin Time (s): " << t_goodwin << std::endl;
	flops = 2*A_2.get_nnz()/t_ibm;
	std::cout << "FLOPS: " << flops << std::endl;

	double t_memplus = getTime(A_3,10);
	std::cout << "CSR Memplus Time (s): " << t_memplus << std::endl;
	flops = 2*A_3.get_nnz()/t_ibm;
	std::cout << "FLOPS: " << flops << std::endl;

	double t_pwt = getTime(A_4,10);
	std::cout << "CSR PWT Time (s): " << t_pwt << std::endl;
	flops = 2*A_4.get_nnz()/t_ibm;
	std::cout << "FLOPS: " << flops << std::endl;

	double t_curtis = getTime(A_5,10);
	std::cout << "CSR Curtis54 Time (s): " << t_curtis << std::endl;
	flops = 2*A_5.get_nnz()/t_ibm;
	std::cout << "FLOPS: " << flops << std::endl;


	TJDS<bool> A_t(ibm);
	TJDS<float> A_2t(goodwin);
	TJDS<float> A_3t(memplus);
	TJDS<float> A_4t(pwt);
	TJDS<bool> A_5t(curtis54);

	//Since execution time is small, ibm is averaged over ten runs
	t_ibm = getTime(A_t,10);
	std::cout << "TJDS IBM Time (s): " << t_ibm << std::endl;
	flops = 2*A_t.get_nnz()/t_ibm;
	std::cout << "FLOPS: " << flops << std::endl;

	t_goodwin = getTime(A_2t,1);
	std::cout << "TJDS Goodwin Time (s): " << t_goodwin << std::endl;
	flops = 2*A_2t.get_nnz()/t_ibm;
	std::cout << "FLOPS: " << flops << std::endl;

	t_memplus = getTime(A_3t,1);
	std::cout << "TJDS Memplus Time (s): " << t_memplus << std::endl;
	flops = 2*A_3t.get_nnz()/t_ibm;
	std::cout << "FLOPS: " << flops << std::endl;

	t_pwt = getTime(A_4t,1);
	std::cout << "TJDS PWT Time (s): " << t_pwt << std::endl;
	flops = 2*A_4t.get_nnz()/t_ibm;
	std::cout << "FLOPS: " << flops << std::endl;

	t_curtis = getTime(A_5t,10);
	std::cout << "TJDS Curtis54 Time (s): " << t_curtis << std::endl;
	flops = 2*A_5t.get_nnz()/t_ibm;
	std::cout << "FLOPS: " << flops << std::endl;

	return 0;
}
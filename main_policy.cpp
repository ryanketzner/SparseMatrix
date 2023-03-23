#include "sparse.hpp"
#include "tjds.hpp"
#include "util.hpp"
#include <execution>

int main()
{
	std::string ibm = "../input/ibm32.mtx";
	std::string memplus = "../input/memplus.mtx";
	std::string pwt = "../input/pwt.mtx";
	std::string goodwin = "../input/goodwin.mtx";
    std::string psmigr = "../input/psmigr_1.mtx";

	SparseMatrix<bool> A(ibm);
	SparseMatrix<float> A_2(goodwin);
	SparseMatrix<float> A_3(memplus);
	SparseMatrix<float> A_4(pwt);
    SparseMatrix<float> A_5(psmigr);

	// Since execution time is small, ibm is averaged over ten runs
	double t_ibm = getTime_par(std::execution::seq, A,50);
	std::cout << "Sequential IBM Time (s): " << t_ibm << std::endl;

	double t_goodwin = getTime_par(std::execution::seq,A_2,10);
	std::cout << "Sequential Goodwin Time (s): " << t_goodwin << std::endl;

	double t_memplus = getTime_par(std::execution::seq,A_3,10);
	std::cout << "Sequential Memplus Time (s): " << t_memplus << std::endl;

	double t_pwt = getTime_par(std::execution::seq, A_4,10);
	std::cout << "Sequential PWT Time (s): " << t_pwt << std::endl;

    double t_psmigr = getTime_par(std::execution::seq, A_5,10);
	std::cout << "Sequential PSMIGR Time (s): " << t_psmigr << std::endl;


    // Parallel
    	// Since execution time is small, ibm is averaged over ten runs
	 t_ibm = getTime_par(std::execution::par, A,50);
	std::cout << "Parallel IBM Time (s): " << t_ibm << std::endl;

	 t_goodwin = getTime_par(std::execution::par,A_2,10);
	std::cout << "Parallel Goodwin Time (s): " << t_goodwin << std::endl;

	 t_memplus = getTime_par(std::execution::par,A_3,10);
	std::cout << "Parallel Memplus Time (s): " << t_memplus << std::endl;

	 t_pwt = getTime_par(std::execution::par, A_4,10);
	std::cout << "Parallel PWT Time (s): " << t_pwt << std::endl;

    t_psmigr = getTime_par(std::execution::par, A_5,10);
	std::cout << "Parallel PSMIGR Time (s): " << t_psmigr << std::endl;

    // Parallel
    	// Since execution time is small, ibm is averaged over ten runs
	 t_ibm = getTime_par(std::execution::par_unseq, A,50);
	std::cout << "Parallel Unsequenced IBM Time (s): " << t_ibm << std::endl;

	 t_goodwin = getTime_par(std::execution::par_unseq,A_2,10);
	std::cout << "Parallel Unsequenced Goodwin Time (s): " << t_goodwin << std::endl;

	 t_memplus = getTime_par(std::execution::par_unseq,A_3,10);
	std::cout << "Parallel Unsequenced Memplus Time (s): " << t_memplus << std::endl;

	 t_pwt = getTime_par(std::execution::par_unseq, A_4,10);
	std::cout << "Parallel Unsequenced PWT Time (s): " << t_pwt << std::endl;

        t_psmigr = getTime_par(std::execution::par_unseq, A_5,10);
	std::cout << "Parallel Unsequenced PSMIGR Time (s): " << t_psmigr << std::endl;

	return 0;
}
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <algorithm>

template <typename T>
using Entry = std::pair<std::array<int,2>,T>;

template <typename T>
class SparseMatrix
{  
public:

    SparseMatrix(std::string path)
    {
        std::ifstream ifs(path);
        if (ifs.is_open())
        {
            std::string header;

            // Skip comment in first line
            std::getline(ifs,header);
            std::getline(ifs,header);

            // Read matrix dimensions and number of elements from header
            std::stringstream ss(header);
            ss >> m;
            ss >> n;
            ss >> size;

            std::vector<Entry<T>> row_order = read_lines(ifs);

            // Will sort array entries lexicographically:
            // rows, then columns
            std::sort(row_order.begin(),row_order.end());
            from_list(row_order);
        }
        else
        {
            std::cout << "Cannot open file " << path << std::endl;
        }
        ifs.close();
    }

    std::vector<Entry<T>> read_lines(std::ifstream& ifs)
    {
        std::string line;
        std::vector<Entry<T>> row_order;
        for (int k = 0; k < size; k++)
        {
            int i;
            int j;
            T val;
            std::getline(ifs,line);
            std::stringstream linestream(line);
            linestream >> i;
            linestream >> j;
            linestream >> val;

            // Convert to zero-index
            row_order.push_back({{i-1,j-1},val});
        }
        return row_order;
    }

    void from_list(const std::vector<Entry<T>>& indices)
    {
        int last_rowptr = 0;
        int i = 0;
        int skipped = 0;
        for(int row = 0; row < m && i < size; row++)
        {
            if (indices[i].first[0] == row)
            {
                // Push extra row pointers if any rows were skipped
                if (skipped)
                {
                    for(int k = 0; k < skipped; k++)
                    {
                        row_ptr.push_back(i);
                    }
                    skipped = 0;
                }
                
                val.push_back(indices[i].second);
                col_ind.push_back(indices[i].first[1]);
                row_ptr.push_back(i);
                i++;
            }
            else // row is not present in the input data (all zeros)
            {
                skipped++;
                continue;
            }

            while (indices[i].first[0] == row && i < size)
            {
                val.push_back(indices[i].second);
                col_ind.push_back(indices[i].first[1]);
                i++;
            }
        }
        row_ptr.push_back(size);
    }

    void printRowPtr()
    {
        printRowVector<int>(row_ptr);
    }

    void printColInd()
    {
        printRowVector<int>(col_ind);
    }

    void printVals()
    {
        printRowVector<T>(val);
    }

    template <typename V>
    std::vector<V> operator *(const std::vector<V>& x)
    {
        int n = x.size();
        std::vector<V> y(n);

        for (int i = 0; i < n; i++)
        {
            y[i] = 0;
            for (int j = row_ptr[i]; j < row_ptr[i+1]; j++)
            {
                y[i] = y[i] + val[j] * x[col_ind[j]];
            }
        }
        return y;
    }

    template <typename V>
    std::vector<V> pow(const std::vector<V>& x,int power)
    {
        int n = x.size();
        std::vector<V> y(n,0);
        std::vector<V> temp;

        for (int i = 0; i < n; i++)
        {
            for (int j = row_ptr[i]; j < row_ptr[i+1]; j++)
            {
                y[i] = y[i] + val[j] * x[col_ind[j]];
            }
        }

        for (int k = 0; k < power-1; k++)
        {
            temp = y;
            for (int i = 0; i < n; i++)
            {
                y[i] = 0;
                for (int j = row_ptr[i]; j < row_ptr[i+1]; j++)
                {
                    y[i] = y[i] + val[j] * temp[col_ind[j]];
                }
            }
        }
        return y;
    }

    template <typename V>
    void printRowVector(const std::vector<V>& vect)
    {
        for (int i = 0; i < vect.size(); i++)
        {
            std::cout << vect.at(i) << ", ";
        }
        std::cout << std::endl;
    }

    std::vector<int> getColInd()
    {
        return col_ind;
    }

    std::vector<int> getRowPtr()
    {
        return row_ptr;
    }

protected:

    int m;
    int n;
    int size;

    std::vector<T> val;
    std::vector<int> col_ind;
    std::vector<int> row_ptr;
};

// Template specialization for pattern matrices/binary images
template <>
std::vector<Entry<bool>> SparseMatrix<bool>::read_lines(std::ifstream& ifs)
{
    std::string line;
    std::vector<Entry<bool>> row_order;
    for (int k = 0; k < size; k++)
    {
        int i;
        int j;
        bool val = 1;
        std::getline(ifs,line);
        std::stringstream linestream(line);
        linestream >> i;
        linestream >> j;

        // Push back as zero-index
        row_order.push_back({{i-1,j-1},val});
    }
    return row_order;
}
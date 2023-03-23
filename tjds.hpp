#include <sparse.hpp>

#ifndef TJDS_HPP
#define TJDS_HPP

template <typename T>
class TJDS
{
public:
    TJDS(std::string path)
    {
        std::ifstream ifs(path);
        Matrix mat = Sparse::get_dims(ifs);
        m = mat.m;
        n = mat.n;
        nnz = mat.nnz;

        // Get matrix elements from file
        // elements will be in the given order of the file
        // which is column order for the .mtx files used
        std::vector<Entry<T>> col_order = Sparse::get_lines<T>(ifs,nnz);
        std::vector<std::vector<Entry<T>>> seperated_cols = seperate_columns(col_order);
        sort_col_list(seperated_cols); 

        build_tjds(seperated_cols);
    }

    // Sorts columns in descending order of their size.
    // In case of a tie, sorts columns in ascending order of their indices.
    static void sort_col_list(std::vector<std::vector<Entry<T>>>& seperated_cols)
    {
        auto sorter = [](const std::vector<Entry<T>>& a, const std::vector<Entry<T>>& b)
        {   
            // If size is the same, sort in ascending order of col index
            if (a.size() == b.size())
                return a[0].first[1] < b[0].first[1];
            
            // Sort largest to smallest
            return a.size() > b.size();
        };
        std::sort(seperated_cols.begin(),seperated_cols.end(),sorter);
    }

    void build_tjds(std::vector<std::vector<Entry<T>>>& seperated_cols)
    {
        int num_rows = seperated_cols[0].size();
        int num_cols = seperated_cols.size();

        value_list.reserve(nnz);
        row_indices.reserve(nnz);
        start_position.reserve(num_rows+1);
        start_position.push_back(0);
        
        for (int i = 0; i < num_cols; i++)
        {
            permutation.emplace_back(seperated_cols[i][0].first[1]);
        }
        num_tjdiag = num_rows;

        for (int i = 0; i < num_rows; i++)
        {
            for (int j = 0; j < num_cols; j++)
            {
                if (i < seperated_cols[j].size())
                {
                    value_list.push_back(seperated_cols[j][i].second);
                    row_indices.push_back(seperated_cols[j][i].first[0]);
                }
                else
                {
                    num_cols-= (num_cols - j);
                }
            }
            start_position.push_back(start_position.back() + num_cols);
        }
    }

    // Multiplies vector by matrix
    // e.g., y = A^pow * x
    // Output type is same as input type
    // Multiplication operation must be defined on matrix and vector type
    // Will not throw error if this condition isn't met!
    template <typename V>
    std::vector<V> operator *(const std::vector<V>& x_in) const
    {
        std::vector<V> y(x_in.size());

        std::vector<V> x = get_permuted_vector(x_in);

        for (int i = 0; i < num_tjdiag; i++)
        {
            int k = 0;
            for (int j = start_position[i]; j < start_position[i+1]; j++)
            {
                int p = row_indices[j];
                y[p] = y[p] + value_list[j]*x[k];
                k++;
            }
        }
        return y;
    }

    // Multiplies vector by matrix to power "pow"
    // e.g., y = A^pow * x
    // Multiplication operation must be defined on matrix and vector type
    // Will not throw error if this condition isn't met!
    template <typename V>
    std::vector<V> pow(const std::vector<V>& x_in,int pow) const
    {
        std::vector<V> y = x_in; // copy x_in to y

        std::vector<V> x(x_in.size());
        for (int l = 0; l < pow; l++)
        {
            x = get_permuted_vector_fill(y);
            for (int i = 0; i < num_tjdiag; i++)
            {
                int k = 0;
                for (int j = start_position[i]; j < start_position[i+1]; j++)
                {
                    int p = row_indices[j];
                    y[p] = y[p] + value_list[j]*x[k];
                    k++;
                }
            }
        }

        return y;
    }

    // Permutes a vector according to TJDS column permutation.
    // Necessary for pow() function
    template <typename V>
    std::vector<V> get_permuted_vector(const std::vector<V>& x_in) const
    {
        std::vector<V> x(x_in.size());
        for (int i = 0; i < x_in.size(); i++)
        {
            x[i] = x_in[permutation[i]];
        }

        return x;
    }

    // Permutes a vector according to TJDS column permutation.
    // Necessary for pow() function
    // Also fills vector with zeros
    template <typename V>
    std::vector<V> get_permuted_vector_fill(std::vector<V>& x_in) const
    {
        std::vector<V> x(x_in.size());
        for (int i = 0; i < x_in.size(); i++)
        {
            x[i] = x_in[permutation[i]];
            x_in[permutation[i]] = 0;
        }

        return x;
    }

    // Seperate entries in the list of entries into a list of columns
    static std::vector<std::vector<Entry<T>>> seperate_columns(const std::vector<Entry<T>>& col_order)
    {
        std::vector<std::vector<Entry<T>>> columns;

        int last_col_idx = col_order[0].first[1];
        std::vector<Entry<T>> current_col;
        current_col.push_back(col_order[0]);

        for (int i = 1; i < col_order.size(); i++)
        {  
            int current_col_idx = col_order[i].first[1];

            if (current_col_idx == last_col_idx)
            {
                current_col.push_back(col_order[i]);
            }
            else
            {
                columns.emplace_back(std::move(current_col));
                current_col.clear();
                current_col.push_back(col_order[i]);
            }
            last_col_idx = current_col_idx;
        }
        columns.emplace_back(std::move(current_col));
        return columns;
    }

    int getN() const
    {
        return n;
    }

    int get_nnz() const
    {
        return nnz;
    }

    int m; // number of rows
    int n; // number of columns
    int nnz; // number of non-zeros
    int num_tjdiag;

    std::vector<T> value_list;
    std::vector<int> row_indices;
    std::vector<int> start_position;
    std::vector<int> permutation;
};

#endif
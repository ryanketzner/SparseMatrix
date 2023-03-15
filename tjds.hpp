#include <sparse.hpp>

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
        std::vector<std::array<int,2>> cols = count_cols(col_order);
        sort_cols(cols);

        std::vector<std::vector<Entry<T>>> seperated_cols = seperate_columns(col_order);
        sort_col_list(seperated_cols); 
        build_tjds(seperated_cols);
    }

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
        num_tjdiag = permutation.size() - 1;

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

    template <typename V>
    std::vector<V> operator *(const std::vector<V>& x_in)
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

    template <typename V>
    std::vector<V> pow(const std::vector<V>& x_in,int power) const
    {
        std::vector<V> y = x_in; // copy x_in to y

        for (int l = 0; l < power; l++)
        {
            std::vector<V> x = get_permuted_vector(y);
            std::fill(y.begin(),y.end(),0);

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

    template <typename V>
    std::vector<V> get_permuted_vector(const std::vector<V>& x_in) const
    {
        std::vector<V> x;
        x.reserve(x_in.size());

        for (int i = 0; i < x_in.size(); i++)
        {
            x.push_back(x_in[permutation[i]]);
        }

        return x;
    }

    // void build_tjds(std::vector<std::vector<Entry<T>>>& sep_cols)
    // {
    //     auto sorter = [](const std::array<int,2>& a, const std::array<int,2>& b)
    //     {
    //         if (a[0] == b[0])
    //             return a[1] < b[1];
            
    //         return a[0] > b[0];
    //     };


    // }

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

    static std::vector<std::array<int,2>> count_cols(const std::vector<Entry<T>>& col_order)
    {
        // list of column_index/size pairs
        std::vector<std::array<int,2>> cols;

        int col = col_order[0].first[1];
        int col_size = 1;

        int i = 1;
        while (i < col_order.size())
        {
            int next_col = col_order[i].first[1];

            if (next_col == col)
            {
                col_size++;
            }
            else
            {
                std::array<int,2> column({col_size,col});
                cols.push_back(column);

                col_size = 1;
                col = next_col;
            }
            i++;
        }
        std::array<int,2> column({col_size,col});
        cols.push_back(column);

        return cols;
    }

    static void sort_cols(std::vector<std::array<int,2>>& cols)
    {
        auto sorter = [](const std::array<int,2>& a, const std::array<int,2>& b)
        {
            if (a[0] == b[0])
                return a[1] < b[1];
            
            return a[0] > b[0];
        };
        std::sort(cols.begin(),cols.end(),sorter);
    }

    int m;
    int n;
    int nnz;
    int num_tjdiag;

    std::vector<T> value_list;
    std::vector<int> row_indices;
    std::vector<int> start_position;
    std::vector<int> permutation;
};
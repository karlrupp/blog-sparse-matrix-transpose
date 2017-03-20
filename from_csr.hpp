
#include <vector>
#include <map>

#include "nothing.hpp"

//
// CSR to map
//
template<typename IndexT, typename NumericT, typename RowT>
void run(std::vector<IndexT> const & A_rows, std::vector<IndexT> const & A_cols, std::vector<NumericT> const & A_values,
         std::vector<RowT> & B)
{
  std::size_t N = A_rows.size() - 1;
  B.resize(N);

  IndexT row_start = A_rows[0];
  for (std::size_t row = 0; row < N; ++row)
  {
    IndexT row_stop  = A_rows[row+1];

    for (IndexT nnz_index = row_start; nnz_index < row_stop; ++nnz_index)
      B[A_cols[nnz_index]][row] = A_values[nnz_index];

    row_start = row_stop;
  }

  do_nothing(B);
}


//
// CSR to CSR
//
template<typename IndexT, typename NumericT>
void run(std::vector<IndexT> const & A_rows, std::vector<IndexT> const & A_cols, std::vector<NumericT> const & A_values,
         std::vector<IndexT>       & B_rows, std::vector<IndexT>       & B_cols, std::vector<NumericT>       & B_values)
{
  B_cols.resize(A_cols.size());
  B_values.resize(A_values.size()); // note: initialization with zero not strictly required
  B_rows = std::vector<IndexT>(A_rows.size(), 0);

  std::size_t N = A_rows.size() - 1;

  //
  // Stage 1: Compute pattern for B
  //
  IndexT row_start = 0;
  for (std::size_t row = 0; row < N; ++row)
  {
    IndexT row_stop  = A_rows[row+1];

    for (IndexT nnz_index = row_start; nnz_index < row_stop; ++nnz_index)
      B_rows[A_cols[nnz_index]] += 1;

    row_start = row_stop;
  }

  // Bring row-start array in place using exclusive-scan:
  IndexT offset = 0;
  for (std::size_t row = 0; row < N; ++row)
  {
    IndexT tmp = B_rows[row];
    B_rows[row] = offset;
    offset += tmp;
  }
  B_rows[N] = offset;


  //
  // Stage 2: Fill with data
  //
  std::vector<IndexT> B_offsets(B_rows); // index of first unwritten element per row

  row_start = A_rows[0];
  for (std::size_t row = 0; row < N; ++row)
  {
    IndexT row_stop  = A_rows[row+1];

    for (IndexT nnz_index = row_start; nnz_index < row_stop; ++nnz_index)
    {
      IndexT col_in_A = A_cols[nnz_index];
      IndexT B_nnz_index = B_offsets[col_in_A];
      B_cols[B_nnz_index] = row;
      B_values[B_nnz_index] = A_values[nnz_index];
      B_offsets[col_in_A] += 1;
    }

    row_start = row_stop;
  }

  do_nothing(B_rows, B_cols, B_values);
}


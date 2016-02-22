
#include <vector>

#include "nothing.hpp"

//
// map to map, map to flat_map, flat_map to map, flat_map to flat_map
//
template<typename RowType1, typename RowType2>
void run(std::vector<RowType1> const & A,
         std::vector<RowType2> & B)
{
  B.resize(A.size());

  for (std::size_t i=0; i<A.size(); ++i)
    for (typename RowType1::const_iterator it = A[i].begin(); it != A[i].end(); ++it)
      B[it->first][i] = it->second;

  do_nothing(B);
}



//
// map to CSR
//
template<typename RowT, typename IndexT, typename NumericT>
void run(std::vector<RowT> const & A,
         std::vector<IndexT> & B_rows,
         std::vector<IndexT> & B_cols,
         std::vector<NumericT> & B_values)
{
  std::size_t B_nnz = 0;

  for (std::size_t i = 0; i < A.size(); ++i)
    B_nnz += A[i].size();

  // initialize datastructures for B:
  B_cols.resize(B_nnz);    // note: initialization with zero not strictly required
  B_values.resize(B_nnz);  // note: initialization with zero not strictly required
  B_rows.resize(A.size() + 1);

  //
  // Stage 1: Compute nonzero pattern for B
  //
  for (std::size_t row = 0; row < A.size(); ++row)
  {
    for (typename RowT::const_iterator it = A[row].begin(); it != A[row].end(); ++it)
      B_rows[it->first] += 1;
  }

  // Bring row-start array in place using exclusive-scan:
  IndexT offset = 0;
  for (std::size_t row = 0; row < A.size(); ++row)
  {
    IndexT tmp = B_rows[row];
    B_rows[row] = offset;
    offset += tmp;
  }
  B_rows[A.size()] = offset;


  //
  // Stage 2: Fill with data
  //
  std::vector<IndexT> B_offsets(B_rows); // index of first unwritten element per row

  for (std::size_t row = 0; row < A.size(); ++row)
  {
    for (typename RowT::const_iterator it = A[row].begin(); it != A[row].end(); ++it)
    {
      IndexT col_in_A = it->first;
      IndexT B_nnz_index = B_offsets[col_in_A];
      B_cols[B_nnz_index] = row;
      B_values[B_nnz_index] = it->second;
      B_offsets[col_in_A] += 1;
    }
  }

  do_nothing(B_rows, B_cols, B_values);
}


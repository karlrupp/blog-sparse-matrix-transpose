

#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

#include "from_csr.hpp"
#include "from_map.hpp"
#include "benchmark-utils.hpp"

#include <boost/interprocess/containers/flat_map.hpp>

void print_median(std::vector<double> & exec_times)
{
  std::sort(exec_times.begin(), exec_times.end());
  std::cout << exec_times[exec_times.size()/2] << "     ";
}


int main(int argc, char **argv)
{
  if (argc < 3)
  {
    std::cout << "Missing argument: Matrix-dimension, Nonzeros/row" << std::endl;
    return EXIT_FAILURE;
  }

  std::size_t runs = 10;
  std::size_t N = atoi(argv[1]);
  std::size_t nnz_per_row = atoi(argv[2]);
  std::vector<double> exec_times(runs);

  //
  // Matrix initialization
  //
  std::vector< std::map<unsigned int, double> > A_map(N);
  std::vector< boost::container::flat_map<unsigned int, double> > A_flatmap(N);
  std::vector< unsigned int > A_csr_rows(N+1);

  unsigned int total_nnz = 0;
  for (std::size_t row=0; row<N; ++row)
  {
    for (std::size_t j=0; j<nnz_per_row; ++j)
    {
      unsigned int col_idx = rand() % N;
      double value = 1.0 + double(rand()) / double(RAND_MAX);
      A_map[row][col_idx] = value;
      A_flatmap[row][col_idx] = value;
    }
    A_csr_rows[row] = total_nnz;
    total_nnz += A_map[row].size();
  }
  A_csr_rows[N] = total_nnz;

  std::vector<unsigned int> A_csr_cols(total_nnz);
  std::vector<double> A_csr_values(total_nnz);

  std::size_t index = 0;
  for (std::size_t row=0; row<N; ++row)
    for (std::map<unsigned int, double>::const_iterator it = A_map[row].begin(); it != A_map[row].end(); ++it, ++index)
    {
      A_csr_cols[index] = it->first;
      A_csr_values[index] = it->second;
    }


  //
  // Run benchmarks
  //
  //std::cout << "# Size  map->map  map->flatmap  mat->csr     flatmap->map  flatmap->flatmap  flatmap->csr      csr->map  csr->flatmap  csr->csr" << std::endl;
  std::cout << N << "    ";

  Timer timer;

  // map to map
  for (std::size_t i=0; i<runs; ++i)
  {
    timer.start();
    std::vector<std::map<unsigned int, double> > B;
    run(A_map, B);
    exec_times[i] = timer.get();
  }
  print_median(exec_times);


  // map to flatmap
  for (std::size_t i=0; i<runs; ++i)
  {
    timer.start();
    std::vector<boost::container::flat_map<unsigned int, double> > B(N);
    for (std::size_t j=0; j<N; ++j)
      B[j].reserve(2*nnz_per_row);
    run(A_map, B);
    exec_times[i] = timer.get();
  }
  print_median(exec_times);


  // map to csr
  for (std::size_t i=0; i<runs; ++i)
  {
    timer.start();
    std::vector<unsigned int> B_rows;
    std::vector<unsigned int> B_cols;
    std::vector<double> B_values;
    run(A_map, B_rows, B_cols, B_values);
    exec_times[i] = timer.get();
  }
  print_median(exec_times);

  std::cout << "     ";
  /////////

  // flatmap to map
  for (std::size_t i=0; i<runs; ++i)
  {
    timer.start();
    std::vector<std::map<unsigned int, double> > B;
    run(A_flatmap, B);
    exec_times[i] = timer.get();
  }
  print_median(exec_times);


  // flatmap to flatmap
  for (std::size_t i=0; i<runs; ++i)
  {
    timer.start();
    std::vector<boost::container::flat_map<unsigned int, double> > B(N);
    for (std::size_t j=0; j<N; ++j)
      B[j].reserve(2*nnz_per_row);
    run(A_flatmap, B);
    exec_times[i] = timer.get();
  }
  print_median(exec_times);


  // flatmap to csr
  for (std::size_t i=0; i<runs; ++i)
  {
    timer.start();
    std::vector<unsigned int> B_rows;
    std::vector<unsigned int> B_cols;
    std::vector<double> B_values;
    run(A_flatmap, B_rows, B_cols, B_values);
    exec_times[i] = timer.get();
  }
  print_median(exec_times);

  std::cout << "     ";
  /////////

  // csr to map
  for (std::size_t i=0; i<runs; ++i)
  {
    timer.start();
    std::vector<std::map<unsigned int, double> > B;
    run(A_csr_rows, A_csr_cols, A_csr_values, B);
    exec_times[i] = timer.get();
  }
  print_median(exec_times);

  // csr to flatmap
  for (std::size_t i=0; i<runs; ++i)
  {
    timer.start();
    std::vector<boost::container::flat_map<unsigned int, double> > B(N);
    for (std::size_t j=0; j<N; ++j)
      B[j].reserve(2*nnz_per_row);
    run(A_csr_rows, A_csr_cols, A_csr_values, B);
    exec_times[i] = timer.get();
  }
  print_median(exec_times);

  // csr to csr
  for (std::size_t i=0; i<runs; ++i)
  {
    timer.start();
    std::vector<unsigned int> B_rows;
    std::vector<unsigned int> B_cols;
    std::vector<double> B_values;
    run(A_csr_rows, A_csr_cols, A_csr_values, B_rows, B_cols, B_values);
    exec_times[i] = timer.get();
  }
  print_median(exec_times);

  std::cout << std::endl;

  return EXIT_SUCCESS;
}

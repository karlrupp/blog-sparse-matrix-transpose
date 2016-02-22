
#include <vector>
#include <map>
#include <boost/interprocess/containers/flat_map.hpp>

// do_nothing() is defined in a separate compilation unit so that the compiler cannot optimize away operations
// from the benchmark in the other compilation unit

void do_nothing(std::vector<unsigned int> & A_rows, std::vector<unsigned int> & A_cols, std::vector<double> & A_values) {}
void do_nothing(std::vector<std::map<unsigned int, double> > & A) {}
void do_nothing(std::vector<boost::container::flat_map<unsigned int, double> > & A) {}

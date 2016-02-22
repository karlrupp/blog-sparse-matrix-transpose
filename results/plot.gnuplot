set terminal postscript enhanced color eps

set style data lines
set style line 1  linetype -1 linewidth 3 lc rgb "#990000"
set style line 2  linetype -1 linewidth 3 lc rgb "#009900"
set style line 3  linetype -1 linewidth 3 lc rgb "#000099"
set style increment user

set size 0.75,0.75
set border lw 2

set key top right Left reverse invert
set grid
set ylabel "Million Nonzeros per Second"
#set logscale y
set logscale x
set xlabel "Matrix Size"
set xrange [1000:1e6]
set format x "10^{%L}"

#######

set output "sparse_matrix_transpose_10nnz.eps"
set title "Sparse Matrix Transposition, 10 Nonzeros per Row"
plot 'nnz10.txt'           using 1:(10*$1/$2/1e6 ) with linesp ls 1 pt  5 ps 1.5 title "vector< map<T, U> >", \
     'nnz10.txt'           using 1:(10*$1/$6/1e6 ) with linesp ls 2 pt  7 ps 1.5 title 'vector< flat\_map<T, U> >', \
     'nnz10.txt'           using 1:(10*$1/$10/1e6) with linesp ls 3 pt  9 ps 1.5 title "CSR, 3 arrays"

set output "sparse_matrix_transpose_100nnz.eps"
set title "Sparse Matrix Transposition, 100 Nonzeros per Row"
plot 'nnz100.txt'          using 1:(100*$1/$2/1e6 ) with linesp ls 1 pt  5 ps 1.5 title "vector< map<T, U> >", \
     'nnz100.txt'          using 1:(100*$1/$6/1e6 ) with linesp ls 2 pt  7 ps 1.5 title 'vector< flat\_map<T, U> >', \
     'nnz100.txt'          using 1:(100*$1/$10/1e6) with linesp ls 3 pt  9 ps 1.5 title "CSR, 3 arrays"



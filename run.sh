#!/bin/bash

g++ main.cpp nothing.cpp -I. -O3 -DNDEBUG -o transpose

echo "# 10 nonzeros per row" > nnz10.txt
echo "# size   map->map  map->flatmap  mat->csr     flatmap->map  flatmap->flatmap  flatmap->csr      csr->map  csr->flatmap  csr->csr" >> nnz10.txt
./transpose    1000 10 >> nnz10.txt
./transpose    3200 10 >> nnz10.txt
./transpose   10000 10 >> nnz10.txt 
./transpose   32000 10 >> nnz10.txt
./transpose  100000 10 >> nnz10.txt
./transpose  320000 10 >> nnz10.txt 
./transpose 1000000 10 >> nnz10.txt

echo "# 100 nonzeros per row" > nnz100.txt
echo "# size   map->map  map->flatmap  mat->csr     flatmap->map  flatmap->flatmap  flatmap->csr      csr->map  csr->flatmap  csr->csr" >> nnz100.txt
./transpose    1000 100 >> nnz100.txt
./transpose    3200 100 >> nnz100.txt
./transpose   10000 100 >> nnz100.txt 
./transpose   32000 100 >> nnz100.txt
./transpose  100000 100 >> nnz100.txt
./transpose  320000 100 >> nnz100.txt 






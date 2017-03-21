
# Sparse matrix transposition: Datastructure performance comparison

Supplements blog post by Karl Rupp:
https://www.karlrupp.net/2016/02/sparse-matrix-transposition-datastructure-performance-comparison

## Build

Assuming that Boost is installed on the system, issue e.g.
 $> g++ main.cpp nothing.cpp -I. -O3 -DNDEBUG -o transpose

To build using CMake:

~~~sh
mkdir build
cd build
cmake ..
~~~

then

`make transpose`

to build the executable, or

`make benchmark`

to build and run

## Run

To run with a certain matrix size (e.g. 1000) and nonzeros per row (e.g. 10), pass them as parameters:
 $> ./transpose 1000 10


## Plot

Have a look at the results/ folder, where the data and gnuplot commands are located.
Replot via
 $> gnuplot plot.gnuplot
(produces postscript plots)

Convert to .pdf via
 $> epstopdf FILENAME.eps
and to .png using ImageMagick, e.g.
 $> convert -density 300 FILENAME.eps -resize 1150x FILENAME.png



## License

The code is provided under a permissive MIT/X11-style license.
See file LICENSE.txt for details.

The results and plotting scripts in folder results/ are provided under the
Creative Commons Attribution 4.0 International (CC BY 4.0)
license, see results/LICENSE.txt


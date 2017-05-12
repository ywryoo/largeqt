# largeqt

## Installation
Building code in Ubuntu is recommended. ~~This project use clock_gettime() for benchmarking, which is not supported in OS X.~~ *Note. Not verified* Also, windows does not support now. pthread is used for multi threading, which can only be used in \*nix systems. It is possible to build in windows if some code is changed. However, that is not in a schedule.

### Linux(Ubuntu)
1. install qt5, gsl from apt
```bash
sudo apt-get install qtbase5-dev libgsl-dev libgsl0-dev libgsl0ldbl
```
2. [build and install qwt](http://qwt.sourceforge.net/qwtinstall.html). Don't forget to set QMAKEFEATURES.
3. set QWT_PATH in largeqt.pro if path is changed.
4. set LD_LIBRARY_PATH for qwt at ~/.bashrc
```bash
LD_LIBRARY_PATH="/usr/local/qwt-6.1.3:$LD_LIBRARY_PATH"
```
5. `qmake largeqt.pro`
6. `cd ./bin && ./scatterplot`

### Mac

1. install homebrew
2. install gsl, qwt, qt from brew
```bash
brew install gsl qwt qt
```
3. set QWT_PATH in largeqt.pro if path is changed.
4. [set QMAKEFEATURES](http://qwt.sourceforge.net/qwtinstall.html).
4. link libraries(see [this link](http://stackoverflow.com/questions/18588418/install-and-use-qwt-under-mac-os-x) if you encounter a problem)
5. change lseek64 to lseek in annoylib.h([link](https://github.com/lferry007/LargeVis)). 
6. `qmake largeqt.pro`
7. `cd ./bin/scatterplot.app/Conetents/MacOS && ./scatterplot`

## Usage
 - if you made .dat file from pixelsne matlab wrapper, you can use the data without parameter by using .dat extension as input file name. labels are single numbers, data should be formatted like LargeVis.
### Logs
If output option is provided(only cli available), Logs are generated.
 - \*_iter_n.log: N, D, Y, C(error) is written by binary. you can use this log as input to see the result.
 - \*_variables.txt: given variables
 - \*_time_label.txt: timestamps for iterations. first line is init time of vis, next line is iter 1, and so on.

## Acknowledgement
 This project uses ANNOY, LargeVis, PixelSNE, QT and QWT with corresponding documents and papers. Links will be added afterwords.

## License
 There are several licenses for each source code, which is noticed above in each source code. ANNOY and LargeVis takes Apache License 2.0, pixelsne has no License yet(this code is continuation of pixelsne on some part so there are no problem to use it), QT and QWT is LGPL or similar and others are LGPL by Ryangwook Ryoo.

 
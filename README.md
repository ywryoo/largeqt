# largeqt

## Installation

### Mac

1. install homebrew
2. install gsl, qwt, qt from brew
```bash
brew install gsl qwt qt
```
3. set QWT_PATH in largeqt.pro if path is changed.
4. link libraries(see [this link](http://stackoverflow.com/questions/18588418/install-and-use-qwt-under-mac-os-x) if you encounter a problem)
5. `qmake largeqt.pro`
6. `cd ./bin/scatterplot.app/Conetents/MacOS && ./scatterplot`

### Linux(Ubuntu)
1. install qt5, gsl and qwt
3. set QWT_PATH in largeqt.pro if path is changed.
5. `qmake largeqt.pro`
6. `cd ./bin && ./scatterplot`


## Usage
 - if you made .dat file from pixelsne matlab wrapper, you can use the data without parameter by using .dat extension as input file name. labels is single numbers, data should be formatted like LargeVis.

## Acknowledgement
 This project uses ANNOY, LargeVis, PixelSNE, QT and QWT with corresponding documents and papers. Links will be added afterwords.

## License
 There are several licenses for each source code, which is noticed above in each source code. ANNOY and LargeVis takes Apache License 2.0, pixelsne has no License yet(this code is continuation of pixelsne on some part so there are no problem to use it), QT and QWT is LGPL or similar and others are LGPL by Ryangwook Ryoo.

 
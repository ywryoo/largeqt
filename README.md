# largeqt

## Installation

### Mac

1. install brew
2. install gsl, qwt, qt from brew
```bash
brew install gsl qwt qt
```
3. set QWT_PATH in largeqt.pro if path is changed.
4. link libraries(see [this link](http://stackoverflow.com/questions/18588418/install-and-use-qwt-under-mac-os-x) if you encounter a problem)
5. `qmake largeqt.pro`
6. `./scatterplot -input ~/largeqt/LargeVis/Examples/CondMat/CondMat_network.txt -output out -fea 0`

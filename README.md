# largeqt

## Installation

### Mac

1. install brew
2. install gsl, qwt, qt from brew
```bash
brew install gsl qwt qt
```
3. set QWT_PATH in largeqt.pro if path is changed.
4. `qmake largeqt.pro`
5. `./scatterplot -input ~/largeqt/LargeVis/Examples/CondMat/CondMat_network.txt -output out -fea 0`

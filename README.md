# psne

## Installation
Building code in Ubuntu is recommended.

### Linux(Ubuntu)
1. Clone this repository - [psne]](https://github.com/ywryoo/psne)
2. Download [qwt 6.1.3](http://qwt.sourceforge.net/qwtinstall.html) and [nmslib 1.5.3](https://github.com/searchivarius/nmslib)
3. Install [QT 5](https://www.qt.io/download). Commercial license is not needed.
4. Install build tools and gsl library to compile qwt
```bash
sudo apt-get install build-essential libgl1-mesa-dev
```
5. Locate qwt source files to `/usr/local/qwt-6.1.3` and build it
```bash
cd /usr/local/qwt-6.1.3
make
``` 
6. set LD_LIBRARY_PATH for qwt at ~/.bashrc
```bash
LD_LIBRARY_PATH="/usr/local/qwt-6.1.3/lib:$LD_LIBRARY_PATH"
```
7. Install cmake, boost, libgsl0, libeigen3 to compile nmslib
```bash
sudo apt-get install cmake libgsl0-dev libeigen3-dev libboost-all
```
8. locate nmslib and build it by using command below - for setting release mode with fixed location
```bash
cmake \
 -DCMAKE_INSTALL_PREFIX=$HOME/NonMetrLibRelease \
 -DCMAKE_BUILD_TYPE=Release .
```
9. set qwt and nmslib path at `psne.pro` if location is changed.
10. `qmake psne.pro`
11. `cd ./bin && ./scatterplot`

- If you do not use GUI, install qt dev tools instead of QT5 to complie psne
```bash
sudo apt-get install qt5-default, libqt5svg5-dev
```

## Usage
 - if you made .dat file from pixelsne matlab wrapper, you can use the data without parameter by using .dat extension as input file name. labels are single numbers, data should be formatted like LargeVis.
 - detailed command is presented when executed.

### Logs
If output option is provided(option is availabled in cli only), logs are generated.
 - \*_iter_n.log: N, D, Y, C(error) is written by binary. you can use this log as input to see the result.
 - \*_variables.txt: given variables
 - \*_time_label.txt: timestamps for iterations. first line is init time of vis, next line is iter 1, and so on.

## Acknowledgement
 This project uses ANNOY, LargeVis, PixelSNE, QT and QWT with corresponding documents and papers.

## License
 There are diffrent licenses for each source code respectively. ANNOY and LargeVis takes Apache License 2.0, pixelsne has no License yet(This repository is continued work of pixelsne), QT and QWT is LGPL or similar and others are LGPL by Ryangwook Ryoo. 
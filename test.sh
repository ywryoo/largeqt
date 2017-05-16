#!/bin/bash
# pixelsne
# all on
./scatterplot -cli 1 -input data.txt -label label.txt -output mnist1 -rseed 15
# no neighbor exploring approximation
./scatterplot -cli 1 -input data.txt -label label.txt -output mnist2 -knnval 0 -rseed 15
# no skipping gradient descent
./scatterplot -cli 1 -input data.txt -label label.txt -output mnist3 -sleep 0 -rseed 15
# no neighbor exploring approximation & no skipping gradient descent
./scatterplot -cli 1 -input data.txt -label label.txt -output mnist4 -knnval 0 -sleep 0 -rseed 15

# no gradient descent threading
./scatterplot -cli 1 -input data.txt -label label.txt -output mnist5 -fthread 0 -rseed 15
# no gradient descent threading & no neighbor exploring approximation
./scatterplot -cli 1 -input data.txt -label label.txt -output mnist6 -fthread 0 -knnval 0 -rseed 15
# no gradient descent threading & no skipping gradient descent
./scatterplot -cli 1 -input data.txt -label label.txt -output mnist7 -fthread 0 -sleep 0 -rseed 15
# no gradient descent threading & no neighbor exploring approximation & no skipping gradient descent
./scatterplot -cli 1 -input data.txt -label label.txt -output mnist8 -fthread 0 -knnval 0 -sleep 0 -rseed 15

# no pipelining
./scatterplot -cli 1 -input data.txt -label label.txt -output mnist9 -pipelining 0 -rseed 15
# no pipelining & no neighbor exploring approximation
./scatterplot -cli 1 -input data.txt -label label.txt -output mnist10 -pipelining 0 -knnval 0 -rseed 15
# no pipelining & no skipping gradient descent
./scatterplot -cli 1 -input data.txt -label label.txt -output mnist11 -pipelining 0 -sleep 0 -rseed 15
# no pipelining & no neighbor exploring approximation & no skipping gradient descent
./scatterplot -cli 1 -input data.txt -label label.txt -output mnist12 -pipelining 0 -knnval 0 -sleep 0 -rseed 15

# no gradient descent threading & no pipelining
./scatterplot -cli 1 -input data.txt -label label.txt -output mnist15 -fthread 0 -pipelining 0 -rseed 15
# no gradient descent threading & no pipelining & no neighbor exploring approximation
./scatterplot -cli 1 -input data.txt -label label.txt -output mnist14 -fthread 0 -pipelining 0 -knnval 0 -rseed 15
# no gradient descent threading & no pipelining & no skipping gradient descent
./scatterplot -cli 1 -input data.txt -label label.txt -output mnist15 -fthread 0 -pipelining 0 -sleep 0 -rseed 15
# no gradient descent threading & no pipelining & no neighbor exploring approximation & no skipping gradient descent
./scatterplot -cli 1 -input data.txt -label label.txt -output mnist16 -fthread 0 -pipelining 0 -knnval 0 -sleep 0 -rseed 15

# bhsne(pixelsne bins 2048)
# all on
./scatterplot -cli 1 -input data.txt -label label.txt -output mnist17 -bins 2048 -rseed 15
# no neighbor exploring approximation
./scatterplot -cli 1 -input data.txt -label label.txt -output mnist18 -bins 2048 -knnval 0 -rseed 15
# no skipping gradient descent
./scatterplot -cli 1 -input data.txt -label label.txt -output mnist19 -bins 2048 -sleep 0 -rseed 15
# no neighbor exploring approximation & no skipping gradient descent
./scatterplot -cli 1 -input data.txt -label label.txt -output mnist20 -bins 2048 -knnval 0 -sleep 0 -rseed 15

# no gradient descent threading
./scatterplot -cli 1 -input data.txt -label label.txt -output mnist21 -bins 2048 -fthread 0 -rseed 15
# no gradient descent threading & no neighbor exploring approximation
./scatterplot -cli 1 -input data.txt -label label.txt -output mnist22 -bins 2048 -fthread 0 -knnval 0 -rseed 15
# no gradient descent threading & no skipping gradient descent
./scatterplot -cli 1 -input data.txt -label label.txt -output mnist23 -bins 2048 -fthread 0 -sleep 0 -rseed 15
# no gradient descent threading & no neighbor exploring approximation & no skipping gradient descent
./scatterplot -cli 1 -input data.txt -label label.txt -output mnist24 -bins 2048 -fthread 0 -knnval 0 -sleep 0 -rseed 15

# no pipelining
./scatterplot -cli 1 -input data.txt -label label.txt -output mnist25 -bins 2048 -pipelining 0 -rseed 15
# no pipelining & no neighbor exploring approximation
./scatterplot -cli 1 -input data.txt -label label.txt -output mnist26 -bins 2048 -pipelining 0 -knnval 0 -rseed 15
# no pipelining & no skipping gradient descent
./scatterplot -cli 1 -input data.txt -label label.txt -output mnist27 -bins 2048 -pipelining 0 -sleep 0 -rseed 15
# no pipelining & no neighbor exploring approximation & no skipping gradient descent
./scatterplot -cli 1 -input data.txt -label label.txt -output mnist28 -bins 2048 -pipelining 0 -knnval 0 -sleep 0 -rseed 15

# no gradient descent threading & no pipelining
./scatterplot -cli 1 -input data.txt -label label.txt -output mnist29 -bins 2048 -fthread 0 -pipelining 0 -rseed 15
# no gradient descent threading & no pipelining & no neighbor exploring approximation
./scatterplot -cli 1 -input data.txt -label label.txt -output mnist30 -bins 2048 -fthread 0 -pipelining 0 -knnval 0 -rseed 15
# no gradient descent threading & no pipelining & no skipping gradient descent
./scatterplot -cli 1 -input data.txt -label label.txt -output mnist31 -bins 2048 -fthread 0 -pipelining 0 -sleep 0 -rseed 15
# no gradient descent threading & no pipelining & no neighbor exploring approximation & no skipping gradient descent
./scatterplot -cli 1 -input data.txt -label label.txt -output mnist32 -bins 2048 -fthread 0 -pipelining 0 -knnval 0 -sleep 0 -rseed 15

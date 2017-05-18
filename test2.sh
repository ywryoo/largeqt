#!/bin/bash
# pp -> pipelined sne
# lb -> largevis + bhsne
# lp -> largevis + pixelsne
# rb -> rp trees + bhsne
# vb -> vp tree + bhsne
# number -> threads

# mnist_lb2
./scatterplot -cli 1 -input mnist.txt -label mnist_label.txt -output mnist_lb2 -bhsne 1 -pipelining 0 -knnval 0 -threads 2 -rseed 15 >> mnist_lb2.log
# mnist_lp2
./scatterplot -cli 1 -input mnist.txt -label mnist_label.txt -output mnist_lp2 -knnval 0 -pipelining 0 -sleep 0 -threads 2 -rseed 15 >> mnist_lp2.log
# mnist_rb2
./scatterplot -cli 1 -input mnist.txt -label mnist_label.txt -output mnist_rb2 -bhsne 1 -prop 0 -threads 2 -rseed 15 >> mnist_rb2.log
# mnist_vp2
./scatterplot -cli 1 -input mnist.txt -label mnist_label.txt -output mnist_vb2 -bhsne 1 -pmethod 1 -threads 2 -rseed 15 >> mnist_vp2.log


# mnist_lb4
./scatterplot -cli 1 -input mnist.txt -label mnist_label.txt -output mnist_lb4 -bhsne 1 -pipelining 0 -knnval 0 -threads 4 -rseed 15 >> mnist_lb4.log
# mnist_lp4
./scatterplot -cli 1 -input mnist.txt -label mnist_label.txt -output mnist_lp4 -knnval 0 -pipelining 0 -sleep 0 -threads 4 -rseed 15 >> mnist_lp4.log
# mnist_rb4
./scatterplot -cli 1 -input mnist.txt -label mnist_label.txt -output mnist_rb4 -bhsne 1 -prop 0 -threads 4 -rseed 15 >> mnist_rb4.log
# mnist_vp4
./scatterplot -cli 1 -input mnist.txt -label mnist_label.txt -output mnist_vb4 -bhsne 1 -pmethod 1 -threads 4 -rseed 15 >> mnist_vp4.log


# mnist_lb8
./scatterplot -cli 1 -input mnist.txt -label mnist_label.txt -output mnist_lb8 -bhsne 1 -pipelining 0 -knnval 0 -threads 8 -rseed 15 >> mnist_lb8.log
# mnist_lp8
./scatterplot -cli 1 -input mnist.txt -label mnist_label.txt -output mnist_lp8 -knnval 0 -pipelining 0 -sleep 0 -threads 8 -rseed 15 >> mnist_lp8.log
# mnist_rb8
./scatterplot -cli 1 -input mnist.txt -label mnist_label.txt -output mnist_rb8 -bhsne 1 -prop 0 -threads 8 -rseed 15 >> mnist_rb8.log
# mnist_vp8
./scatterplot -cli 1 -input mnist.txt -label mnist_label.txt -output mnist_vb8 -bhsne 1 -pmethod 1 -threads 8 -rseed 15 >> mnist_vp8.log


# mnist_lb16
./scatterplot -cli 1 -input mnist.txt -label mnist_label.txt -output mnist_lb16 -bhsne 1 -pipelining 0 -knnval 0 -threads 16 -rseed 15 >> mnist_lb16.log
# mnist_lp16
./scatterplot -cli 1 -input mnist.txt -label mnist_label.txt -output mnist_lp16 -knnval 0 -pipelining 0 -sleep 0 -threads 16 -rseed 15 >> mnist_lp16.log
# mnist_rb16
./scatterplot -cli 1 -input mnist.txt -label mnist_label.txt -output mnist_rb16 -bhsne 1 -prop 0 -threads 16 -rseed 15 >> mnist_rb16.log
# mnist_vp16
./scatterplot -cli 1 -input mnist.txt -label mnist_label.txt -output mnist_vb16 -bhsne 1 -pmethod 1 -threads 16 -rseed 15 >> mnist_vp16.log

# mnist_pp32
# ./scatterplot -cli 1 -input mnist.txt -label mnist_label.txt -output mnist_pp32 -threads 32 -rseed 15 >> mnist_pp32.log
# mnist_lb32
./scatterplot -cli 1 -input mnist.txt -label mnist_label.txt -output mnist_lb32 -bhsne 1 -pipelining 0 -knnval 0 -threads 32 -rseed 15 >> mnist_lb32.log
# mnist_lp32
./scatterplot -cli 1 -input mnist.txt -label mnist_label.txt -output mnist_lp32 -knnval 0 -pipelining 0 -sleep 0 -threads 32 -rseed 15 >> mnist_lp32.log
# mnist_rb32
./scatterplot -cli 1 -input mnist.txt -label mnist_label.txt -output mnist_rb32 -bhsne 1 -prop 0 -threads 32 -rseed 15 >> mnist_rb32.log
# mnist_vp32
./scatterplot -cli 1 -input mnist.txt -label mnist_label.txt -output mnist_vb32 -bhsne 1 -pmethod 1 -threads 32 -rseed 15 >> mnist_vp32.log

# 20news_pp32
./scatterplot -cli 1 -input 20news.dat -label 20news_label.txt -output 20news_pp32 -threads 32 -rseed 10 >> 20news_pp32.log
# 20news_lb32
./scatterplot -cli 1 -input 20news.dat -label 20news_label.txt -output 20news_lb32 -bhsne 1 -pipelining 0 -knnval 0 -threads 32 -rseed 10 >> 20news_lb32.log
# 20news_lp32
./scatterplot -cli 1 -input 20news.dat -label 20news_label.txt -output 20news_lp32 -knnval 0 -pipelining 0 -sleep 0 -threads 32 -rseed 10 >> 20news_lp32.log
# 20news_rb32
./scatterplot -cli 1 -input 20news.dat -label 20news_label.txt -output 20news_rb32 -bhsne 1 -prop 0 -threads 32 -rseed 10 >> 20news_rb32.log
# 20news_vp32
./scatterplot -cli 1 -input 20news.dat -label 20news_label.txt -output 20news_vb32 -bhsne 1 -pmethod 1 -threads 32 -rseed 10 >> 20news_vp32.log

# FE_pp32
./scatterplot -cli 1 -input FE.dat -label FE_label.dat -output FE_pp32 -threads 32 -rseed 17 >> FE_pp32.log
# FE_lb32
./scatterplot -cli 1 -input FE.dat -label FE_label.dat -output FE_lb32 -bhsne 1 -pipelining 0 -knnval 0 -threads 32 -rseed 17 >> FE_lb32.log
# FE_lp32
./scatterplot -cli 1 -input FE.dat -label FE_label.dat -output FE_lp32 -knnval 0 -pipelining 0 -sleep 0 -threads 32 -rseed 17 >> FE_lp32.log
# FE_rb32
./scatterplot -cli 1 -input FE.dat -label FE_label.dat -output FE_rb32 -bhsne 1 -prop 0 -threads 32 -rseed 17 >> FE_rb32.log
# FE_vp32
./scatterplot -cli 1 -input FE.dat -label FE_label.dat -output FE_vb32 -bhsne 1 -pmethod 1 -threads 32 -rseed 17 >> FE_vp32.log

# YELP1.1M_pp32
./scatterplot -cli 1 -input YELP1.1M.dat -label YELP1.1M_label.txt -output YELP1.1M_pp32 -bins 4096 -threads 32 -rseed 30 >> YELP1.1M_pp32.log
# YELP1.1M_lb32
./scatterplot -cli 1 -input YELP1.1M.dat -label YELP1.1M_label.txt -output YELP1.1M_lb32 -bhsne 1 -pipelining 0 -knnval 0 -threads 32 -rseed 30 >> YELP1.1M_lb32.log
# YELP1.1M_lp32
./scatterplot -cli 1 -input YELP1.1M.dat -label YELP1.1M_label.txt -output YELP1.1M_lp32 -bins 4096 -knnval 0 -pipelining 0 -sleep 0 -threads 32 -rseed 30 >> YELP1.1M_lp32.log
# YELP1.1M_rb32
./scatterplot -cli 1 -input YELP1.1M.dat -label YELP1.1M_label.txt -output YELP1.1M_rb32 -bhsne 1 -prop 0 -threads 32 -rseed 30 >> YELP1.1M_rb32.log
# YELP1.1M_vp32
./scatterplot -cli 1 -input YELP1.1M.dat -label YELP1.1M_label.txt -output YELP1.1M_vb32 -bhsne 1 -pmethod 1 -threads 32 -rseed 30 >> YELP1.1M_vp32.log

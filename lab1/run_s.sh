#!/bin/bash
#PBS -k eo
#PBS -m abe
#PBS -M cl2545@cornell.edu
#PBS -N ece5750_pa1_bksb_cl2545
#for n in {40000..50000..5000}; do for i in {1..10}; do /home/cl2545/pa1/bksb $n | head -n 1 >> /home/cl2545/pa1/bksb.stats; done; done
for i in {1..5}; do /home/cl2545/pa1/bksb 50000 | head -n 1 >> /home/cl2545/pa1/bksb.stats; done

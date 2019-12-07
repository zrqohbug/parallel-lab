#!/bin/bash
#PBS -k eo
#PBS -m abe
#PBS -M cl2545@cornell.edu
#PBS -N ece5750_pa1_pbksb_cl2545
for i in {1..10}; do echo "n = $n, p = $p, i = $i" && /home/cl2545/pa1/pbksb $n $p | head -n 1 >> /home/cl2545/pa1/pbksb.stat ; done
#for p in {1,2,4,8,12,16,20,30,40}; do for n in {5000,10000,15000,20000,25000,30000,35000,40000,45000,50000}; do for i in {1..10}; do echo "n = $n, p = $p, i = $i" && /home/cl2545/pa1/pbksb_zhu $n $p | head -n 1 >> /home/cl2545/pa1/pbksb.stat ; done; done; done
#for p in {1,2,4,8,12,16,20,30,40}; do for n in {5000,10000,15000,20000,25000,30000,35000,40000,45000,50000}; do for i in {1..10}; do echo "n = $n, p = $p, i = $i" >> /home/cl2545/pa1/pbksb.stat ; done; done; done

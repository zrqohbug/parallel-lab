#!/bin/bash
#PBS -k eo
#PBS -m abe
#PBS -M cl2545@cornell.edu
#PBS -N ece5750_getcpu_cl2545
# cat /proc/cpuinfo | grep processor
# cat /proc/cpuinfo | grep cache
lscpu               >  /home/cl2545/pa1/hw_config
cat /etc/os-release >> /home/cl2545/pa1/hw_config
lsb_release -a      >> /home/cl2545/pa1/hw_config
tail -n +1  /sys/devices/system/cpu/cpu0/cache/index2/* >> /home/cl2545/pa1/hw_config 
cat /proc/cpuinfo   >> /home/cl2545/pa1/hw_config

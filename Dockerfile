FROM catthehacker/ubuntu:runner-22.04

RUN sudo apt-get update && apt-get -y install \
gcc-aarch64-linux-gnu \
g++-aarch64-linux-gnu \
cmake

#RUN wget https://github.com/CostaMario/Freenove-robot-dog-software-rewrite/releases/download/dev-3/robot-server
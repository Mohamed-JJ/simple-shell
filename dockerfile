FROM debian:buster

RUN apt-get update && apt-get upgrade
RUN apt-get install -y valgrind
RUN apt-get install -y gcc
RUN apt-get install -y clang
RUN apt-get install -y make
RUN apt-get install -y git
RUN apt-get install -y vim
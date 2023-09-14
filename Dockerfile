FROM ubuntu:22.04
LABEL maintainer="lbbxsxlz@gmail.com"

RUN apt-get update
RUN apt-get -y install build-essential uuid-dev iasl nasm
RUN apt-get -y install gcc-riscv64-linux-gnu
RUN mkdir -p /opt/workspace
VOLUME /opt/workspace/
WORKDIR /opt/workspace/

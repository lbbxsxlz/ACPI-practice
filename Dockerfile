FROM ubuntu:22.04
LABEL maintainer="lbbxsxlz@gmail.com"

RUN apt-get update
RUN apt-get -y install build-essential uuid-dev iasl nasm

#! /bin/bash

if [ ! -d edk2 ]; then
    git clone https://github.com/tianocore/edk2.git
    cd edk2
    git submodule update --init
    cp ../CpuDxe.patch
    git apply CpuDxe.patch
    rm CpuDxe.patch
    cd -
fi

if [ ! -d edk2-platforms ]; then
    git clone https://github.com/tianocore/edk2-platforms.git
    cd edk2-platforms
    git submodule update --init
    cp ../U540.patch ./
    git apply U540.patch
    rm U540.patch
    cd -
fi

PWD=$(pwd)
export WORKSPACE=$PWD
export PACKAGES_PATH=$PWD/edk2:$PWD/edk2-platforms
export GCC5_RISCV64_PREFIX=/opt/riscv/bin/riscv64-unknown-linux-gnu-

if [ $1 = "CleanThenMake" ]; then
    source edk2/edksetup.sh
    make -C edk2/BaseTools clean
    make -C edk2/BaseTools
    make -C edk2/BaseTools/Source/C
    source edk2/edksetup.sh BaseTools
else
    source edk2/edksetup.sh
    make -C edk2/BaseTools
fi

rm Build -rf
build -a RISCV64 -b DEBUG -t GCC5 -p Platform/SiFive/U5SeriesPkg/FreedomU540HiFiveUnleashedBoard/U540.dsc

qemu-system-riscv64 -cpu sifive-u54 -machine sifive_u -bios Build/FreedomU540HiFiveUnleashed/DEBUG_GCC5/FV/U540.fd -m 2048 -nographic -smp cpus=5,maxcpus=5

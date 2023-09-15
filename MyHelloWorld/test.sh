#! /bin/bash

ROOT=$(dirname $(pwd))

cd $ROOT/edk2;
ln -sf ../MyHelloWorld/MyHelloWorldPkg MyHelloWorldPkg

source edksetup.sh
make -C BaseTools
build -a IA32 -a X64 -t GCC5 -p MyHelloWorldPkg/MyHelloWorldPkg.dsc -b DEBUG
cd $ROOT

cp -rf HelloWorld/ovmf ./
cp edk2/Build/MyHelloWorldPkg/DEBUG_GCC5/X64/MyHelloWorld.efi ovmf/esp/
sudo qemu-system-x86_64 -M q35,accel=kvm -cpu host -m 4096 -bios ovmf/OVMF.fd -drive format=raw,file=fat:rw:./ovmf/esp -net none -nographic -serial mon:stdio
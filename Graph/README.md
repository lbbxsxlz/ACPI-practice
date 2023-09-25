# Graph App
## build

    cd ../edk2;
    ln -sf ../Graph/GraphPkg GraphPkg

    source edksetup.sh
    make -C BaseTools
    build -a X64 -t GCC5 -p GraphPkg/GraphPkg.dsc -b DEBUG

 ## validate

    cd ../
    cp edk2/GraphPkg/Build/DEBUG_GCC5/X64/GraphApp.efi ./ovmf/esp/
    sudo qemu-system-x86_64 -M q35,accel=kvm -cpu host -m 4096 -bios ovmf/OVMF.fd -drive format=raw,file=fat:rw:./ovmf/esp -net none


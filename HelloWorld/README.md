# Hello World

## Build OVMF

    build -a X64 -t GCC5 -p OvmfPkg/OvmfPkgX64.dsc -b DEBUG

## Build MdeModulePkg

    build -a X64 -t GCC5 -p MdeModulePkg/MdeModulePkg.dsc -b DEBUG

## Build ESP partition

    mkdir -p ovmf
    mkdir -p ovmf/esp
    mkdir -p ovmf/esp/EFI
    cp ../edk2/Build/OvmfX64/DEBUG_GCC5/FV/OVMF_CODE.fd ovmf/
    cp ../edk2/Build/OvmfX64/DEBUG_GCC5/FV/OVMF_VARS.fd ovmf/
    cp ../edk2/Build/OvmfX64/DEBUG_GCC5/FV/OVMF.fd ovmf/
    cp ../edk2/Build/MdeModule/DEBUG_GCC5/X64/HelloWorld.efi ovmf/esp/


## Using QEMU to Launch the bios
### Output From Serial Port

    sudo qemu-system-x86_64 -M q35,accel=kvm -cpu host -m 4096 -bios ovmf/OVMF.fd -drive format=raw,file=fat:rw:./ovmf/esp -net none -nographic -serial mon:stdio

    UEFI Interactive Shell v2.2
    EDK II
    UEFI v2.70 (EDK II, 0x00010000)
    Mapping table
        FS0: Alias(s):HD0a65535a1:;BLK1:
            PciRoot(0x0)/Pci(0x1F,0x2)/Sata(0x0,0xFFFF,0x0)/HD(1,MBR,0xBE1AFDFA,0x3F,0xFBFC1)
        BLK0: Alias(s):
            PciRoot(0x0)/Pci(0x1F,0x2)/Sata(0x0,0xFFFF,0x0)
        BLK2: Alias(s):
            PciRoot(0x0)/Pci(0x1F,0x2)/Sata(0x2,0xFFFF,0x0)
    Press ESC in 3 seconds to skip startup.nsh or any other key to continue.
    Shell> fs0:
    FS0:\> ls
    Directory of: FS0:\
    07/28/2023  17:46 <DIR>         8,192  EFI
    07/28/2023  17:48               9,152  HelloWorld.efi
    07/28/2023  09:59              10,245  NvVars
            2 File(s)      19,397 bytes
            1 Dir(s)
    FS0:\> HelloWorld.efi
    UEFI Hello World!
    FS0:\> cd EFI
    FS0:\EFI\> ls
    Directory of: FS0:\EFI\
    07/28/2023  17:46 <DIR>         8,192  .
    07/28/2023  17:46 <DIR>             0  ..
            0 File(s)           0 bytes
            2 Dir(s)
    FS0:\EFI\>

### Output From the Graphic

    sudo qemu-system-x86_64 -M q35,accel=kvm -cpu host -m 4096 -drive if=pflash,format=raw,file=./ovmf/OVMF_CODE.fd,readonly=on -drive if=pflash,format=raw,file=./ovmf/OVMF_VARS.fd,readonly=on -drive format=raw,file=fat:rw:./ovmf/esp -net none

You may encounter the following errors(I use the MobaXterm to access the linux host):

    MoTTY X11 proxy: Unsupported authorisation protocol
    gtk initialization failed

Please use the following command to fix the error:

    sudo cp /home/$user/.Xauthority /root/
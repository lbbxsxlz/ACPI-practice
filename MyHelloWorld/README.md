# MyHelloWorld

## guid
[guid generate](https://guidgenerator.com/online-guid-generator.aspx)

## Building

    cd ../edk2;
    ln -sf ../MyHelloWorld/MyHelloWorldPkg MyHelloWorldPkg

    source edksetup.sh
    make -C BaseTools
    build -a IA32 -a X64 -t GCC5 -p MyHelloWorldPkg/MyHelloWorldPkg.dsc -b DEBUG
    cd ../

## Validation

    cp -rf HelloWorld/ovmf ./
    cp edk2/Build/MyHelloWorldPkg/DEBUG_GCC5/X64/MyHelloWorld.efi ovmf/esp/
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
    Press ESC in 2 seconds to skip startup.nsh or any other key to continue.
    Shell> fs0:
    FS0:\> ls
    Directory of: FS0:\
    08/03/2023  16:42               9,152  HelloWorld.efi
    08/03/2023  16:43               5,952  MyHelloWorld.efi
    08/03/2023  08:44              10,245  NvVars
            3 File(s)      25,349 bytes
            0 Dir(s)
    FS0:\> MyHelloWorld.efi
    Hello, World!
    Welcome to the New world of UEFI!
    FS0:\>

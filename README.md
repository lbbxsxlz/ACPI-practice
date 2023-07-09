# ACPI-practice

## Build environment
```bash
sudo apt install build-essential uuid-dev iasl
wget http://mirrors.kernel.org/ubuntu/pool/universe/n/nasm/nasm_2.15.05-1_amd64.deb
sudo dpkg -i nasm_2.15.05-1_amd64.deb
```
### using docker container as a build environment
![ref](Dockerfile)
```bash
docker build -t "ubuntu_acpi" .
sudo docker run -v $PWD:/opt/workspace --name acpi_test --privileged -it ubuntu_acpi
```

# Boilerplate: Pico Pimoroni & FreeRTOS

![](docs/demonstration.gif)

A boilerplate for a RP2040 pico project using Pimoroni hardware and FreeRTOS. This boilerplate is based on the project [pico-boilerplate](https://github.com/pimoroni/pico-boilerplate) done by Pimoroni with a couple of adjustments.

One of these adjustments is the usage of environment variables. This completely breaks the usage of local options, but I don't mind.

To use local versions, the `.cmake`-files need to be adjusted to use a variable instead of a enviornment variable (if you know CMake, it should be easy).

## Installation SDK & Pimoroni

1.  **Install [WSL](https://learn.microsoft.com/en-us/windows/wsl/install)**

```bash
wsl --install
```

> ### ⚠ WSL1 & WSL2 ⚠
>
> Depending on the performance, the WSL version might need to be changed
> 
> ```bash
> wsl --set-version <dist> 1 # for WSL 1 or... 
> wsl --set-version <dist> 2 # ...for WSL 2
> ``` 

2. **Install [Visual Studio Code](https://code.visualstudio.com/) & Extensions**
- [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
- [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)
- [Serial Monitor](https://marketplace.visualstudio.com/items?itemName=ms-vscode.vscode-serial-monitor) – Only **Local** (not WSL)
- [WSL](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-wsl)

3. **Installing Toolchain**
```bash
sudo apt update
sudo apt install git cmake gcc-arm-none-eabi libnewlib-arm-none-eabi build-essential libstdc++-arm-none-eabi-newlib
```

4. **Installing Pico SDK**

Important to note is when using WSL, make sure to install the stuff on a Linux storage (for example in the home directiony `~`), as else WSL will be extremely slow.

```bash
cd "~/"
mkdir pico
cd pico
git clone -b master https://github.com/raspberrypi/pico-sdk.git --recursive
```

5. **Downloading Additional Repos**

This installs the pico examples and the Pimoroni library & examples.

```bash
git clone -b master https://github.com/raspberrypi/pico-examples.git
git clone -b main https://github.com/pimoroni/pimoroni-pico.git --recursive
```

By now the folderstructure should look like following
- `pico`
	- `pico-sdk`
	- `pico-examples`
	- `pimoroni-pico`

6. **Configuring Environmental Variables in WSL**

```bash
sudo nano ~/.bashrc
```

At the end of the `.bashrc`-file add following block.

```bash
export PICO_SDK_PATH="/home/<USERNAME>/pico/pico-sdk/"
export PIMORONI_PICO_PATH="/home/<USERNAME>/pico/pimoroni-pico/"
```

Then `source` the `.bashrc`-file

```bash
source ~/.bashrc
```

7. **Build Examples** (optional)

Building Pico examples

```bash
cd ~/pico/pico-examples
mkdir build
cd build
cmake ..
make -j3 # use 3 processes (so far best trade off for my old pc)
```

And the same with the pimoroni examples - **This one takes a lot longer!**
```bash
cd ~/pico/pimoroni-pico
mkdir build
cd build
cmake ..
make -j3 # use 3 processes (so far best trade off for my old pc)
```

## Installation FreeRTOS

The installation of FreeRTOS is based on this guide: https://learnembeddedsystems.co.uk/freertos-on-rp2040-boards-pi-pico-etc-using-vscode

1. **Create Folder in the `pico` folder and enter it**

```bash
cd ~/pico/
mkdir freertos
cd freertos
```

2. **Clone the FreeRTOS-Repository**

```bash
git clone https://github.com/FreeRTOS/FreeRTOS-Kernel
```

3. **Create `CMakeLists.txt` with following content**

```bash
set(PICO_SDK_FREERTOS_SOURCE FreeRTOS-Kernel)

add_library(freertos
    ${PICO_SDK_FREERTOS_SOURCE}/event_groups.c
    ${PICO_SDK_FREERTOS_SOURCE}/list.c
    ${PICO_SDK_FREERTOS_SOURCE}/queue.c
    ${PICO_SDK_FREERTOS_SOURCE}/stream_buffer.c
    ${PICO_SDK_FREERTOS_SOURCE}/tasks.c
    ${PICO_SDK_FREERTOS_SOURCE}/timers.c
    ${PICO_SDK_FREERTOS_SOURCE}/portable/MemMang/heap_3.c
    ${PICO_SDK_FREERTOS_SOURCE}/portable/GCC/ARM_CM0/port.c
)

target_include_directories(freertos PUBLIC
    .
    ${PICO_SDK_FREERTOS_SOURCE}/include
    ${PICO_SDK_FREERTOS_SOURCE}/portable/GCC/ARM_CM0
)
```

4. **Configuring Environmental Variables in WSL**

```bash
sudo nano ~/.bashrc
```

At the end of the `.bashrc`-file add following block.

```bash
export FREERTOS_PATH="/home/<USERNAME>/pico/freertos/"
```

Then `source` the `.bashrc`-file

```bash
source ~/.bashrc
```

The folder structure should look like following:

- 📁 `pico`
  - 📁 `freertos`
    - 📁 `FreeRTOS-Kernel`
    - 📄 `CMakeLists.txt`
  - ...

## Things to consider before use:

The CMakeLists-files are based around following structure. If the guide above has been used, it should be exactly like shown.

- 📁`pico`
  - 📁 `freertos`
    - 📁 `FreeRTOS-Kernel`
  - 📁 `projects`
    - 📁 *`this boilerplate project`*
  - 📁 `pico-examples`
  - 📁 `pico-sdk`
  - 📁 `pimoroni-pico`

Following Environment Variables need to be set, so the `.cmake`-scripts work correctly.

- `PICO_SDK_PATH`: Path to the Pico SDK 
- `FREERTOS_PATH`: Path to the `freertos` folder
- `PIMORONI_PICO_PATH`: Path to the Pimoroni repo
# 04_esp-idf-arduino

There is no schematic for this example, it simply prints some output to the serial monitor at 115200.
This is more of a build system example for untethering yourself from the Arduino IDE.

To build this example you can run the following commands.

```bash
# See Dependencies section below for instructions.
source ~/path/to/esp-idf/export.sh

mkdir build
cd build
cmake ..
make -j $(nproc)

# Flash the example to the ESP.
make flash

# Check the serial monitor for 'Hello world!' output.
idf.py monitor -b 115200
```

To flash to your ESP or access the `idf.py menuconfig` menu from the ESP-IDF you can run the same commands with `make`.

```bash
make flash
make menuconfig
```

If Ninja is preferred:

```bash
mkdir build
cd build
cmake .. -G Nina
ninja
```

## Dependencies

Install the [ESP-IDF](https://github.com/espressif/esp-idf?tab=readme-ov-file#setup-build-environment)

```bash
# https://docs.espressif.com/projects/esp-idf/en/v5.3.2/esp32/get-started/linux-macos-setup.html#for-linux-users
sudo apt-get install -y git wget flex bison gperf python3 python3-pip python3-venv cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0

git clone -b v5.3.2 --recursive https://github.com/espressif/esp-idf
cd esp-idf
./install.sh
. ./export.sh
```

In CLion there is an official [Serial Monitor](https://plugins.jetbrains.com/plugin/8031-serial-port-monitor) plugin, or use ESP-IDF -

```bash
idf.py monitor -b 115200
```

## Starting Over

To set up this project from scratch the following commands were used

```bash
# My example project directory
cd ~/Code/klips/esp/cpp/04_esp-idf-arduino
idf.py set-target esp32
idf.py add-dependency "espressif/arduino-esp32^3.1.1"

# Autostart Arduino for use of `loop()` and `setup()` functions
# You can also use the esp-idf `app_main()` function if preferred
# https://docs.espressif.com/projects/arduino-esp32/en/latest/esp-idf_component.html#configuration
# You can alternatively do this in the GUI tool `idf.py menuconfig`
echo "CONFIG_AUTOSTART_ARDUINO=y" >> sdkconfig
sed -i -e 's/CONFIG_FREERTOS_HZ=100/CONFIG_FREERTOS_HZ=1000/' sdkconfig

# Build the project
idf.py build
```

To set this project up in CLion, see [JetBrains documentation](https://www.jetbrains.com/help/clion/esp-idf.html#env-vars).

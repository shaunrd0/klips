# esp-idf-std

This is an example of using ESP-IDF with std enabled in Rust
When flashed to a device, the application just adjusts the intensity of the on-board LED for visual verification that flashing works correctly.

Steps used to generate this project

```bash
cargo install cargo-generate
cargo generate --git https://github.com/esp-rs/esp-idf-template.git --name esp-idf-rust-std -d mcu=esp32 -d std=true
```

Steps to build and flash this project

```bash
# Install espflash if you don't have it already
cargo install espflash

# Export esp-idf build environment
. ~/export-esp.sh

# Build and flash to the device
cargo build
cargo run

# Check the serial monitor (optional)
sudo usermod -aG dialout $USER
newgrp dialout
espflash monitor
```

For more detailed information on setting up a development environment, see [the esp/rust README](/esp/rust/README.md)

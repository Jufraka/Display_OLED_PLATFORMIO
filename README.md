# OLED Control Example Heltec WiFi LoRa 32 V3

This example shows how to power and drive a 128×64 SSD1306 OLED display from an ESP32 board using the same methodology as the reference firmware in this repository. The display is powered through the Vext pin (GPIO 36 in this sketch) and rendered with the [U8g2](https://github.com/olikraus/u8g2) graphics library.

## Features
- Controls the OLED power rail through a dedicated GPIO so the module can be turned off in software.
- Initializes the U8g2 driver with hardware I²C and a helper that prints up to five quick status lines.
- Alternates two example screens every 1.5 s to demonstrate the refresh flow.
- Allows compiling the sketch without OLED support by setting `USE_DSPMSG` to `0`.

## Hardware Connections
| Signal | ESP32 Pin (macro) | Notes |
| ------ | ----------------- | ----- |
| SDA    | `SDA_OLED` (GPIO 17) | I²C data line.
| SCL    | `SCL_OLED` (GPIO 18) | I²C clock line.
| RST    | `RST_OLED` (GPIO 21) | Reset pin wired to the OLED module.
| Vext   | GPIO 36             | Drives the module power. `LOW` enables the display, `HIGH` disables it. |

> ⚠️ Double‑check that GPIO 36 in your board can sink enough current for Vext. Adjust the definitions at the top of `main.cpp` if your wiring differs.

## Software Setup
1. Install [PlatformIO](https://platformio.org/) or use the Arduino IDE with ESP32 support.
2. Ensure the `U8g2` library is available (PlatformIO will pull it automatically from `lib_deps` if it is declared in `platformio.ini`).
3. Copy `examples/oled_clean/main.cpp` into your project (or open it as a PlatformIO environment) and build/upload it to your board.

## How It Works
- `enableDisplayPower()` configures GPIO 36 as an output and drives it LOW, powering the OLED.
- After a short 10 ms delay, `u8g2.begin()` initializes the display and sets the contrast to maximum.
- `displayMessage()` clears the buffer, writes up to five strings, and submits the buffer to the OLED in a single call.
- The `loop()` toggles between two screens (`Modo A` and `Modo B`) every 1.5 seconds to illustrate updating the display.
- If you set `USE_DSPMSG` to `0`, the sketch falls back to blinking the built-in LED and omits all OLED code at compile time.

## Customization Tips
- Change the font by replacing `u8g2.setFont(u8g2_font_profont12_mf);` with any font included in U8g2.
- Modify the helper to accept dynamic line counts or different spacing if you need more flexibility.
- Wrap other parts of your application with the same `USE_DSPMSG` guard to keep a single compile-time switch for the OLED feature.

## License
This example follows the repository's default license. Refer to the root `LICENSE` file if present.

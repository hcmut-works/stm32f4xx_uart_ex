# stm32f4xx_uart_ex

A simple STM32F4 UART example project developed using Eclipse Embedded C (Eclipse CDT with Embedded extensions). This repository contains example code for using the UART peripheral on STM32F4-series microcontrollers. The project was developed with the Eclipse Embedded C environment in mind and can be built, flashed and debugged from Eclipse or via command-line toolchains.

## Overview

- Purpose: Demonstrate UART initialization and basic TX/RX operations on an STM32F4 MCU.
- Developed with: Eclipse Embedded C (Eclipse CDT / Embedded plugins) and GNU Arm Embedded Toolchain.
- Typical use: Education, quick prototyping, and as an example to integrate UART code into other projects.

## Prerequisites

Make sure you have the following installed on your host machine:

- Eclipse IDE for C/C++ Developers with Embedded CDT or Eclipse Embedded C plugin
- GNU Arm Embedded Toolchain (arm-none-eabi-gcc)
- OpenOCD and/or STM32CubeProgrammer (for flashing and debugging)
- ST-Link USB driver and/or ST-Link Utility (or equivalent programmer)
- Optional: STM32CubeF4 (HAL) libraries or the STM32 Standard Peripheral Library if used by the project
- Serial terminal program: PuTTY, minicom, screen, or similar

Minimum tested versions (examples):
- Eclipse 2020-12 or later
- GNU Arm Embedded Toolchain 9/10/11+
- OpenOCD 0.10+

## Supported Hardware

- STM32F4 series microcontrollers (e.g., STM32F407, STM32F429)
- Target board: any development board with an STM32F4 and an ST-LINK/V2 interface (e.g., STM32F4Discovery, Nucleo-F4)

Adjust pins and clock configuration in the project sources according to your exact MCU and board.

## Project structure (example)

The actual layout in your repo may vary. Typical folders in an STM32/Eclipse project:

- Core/ or Src/ — application source files (main.c, uart.c)
- Inc/ — headers (main.h, uart.h)
- Drivers/ — MCU peripheral drivers (HAL or StdPeriph)
- Project Settings — Eclipse project files (.project, .cproject)
- Makefile or build scripts (if command-line build supported)

If your repository uses a different structure, adapt the import/build instructions below.

## Importing into Eclipse Embedded C

1. Start Eclipse and choose a workspace.
2. Install Embedded CDT plugin or use Eclipse Embedded C distribution.
3. Import the project:
   - File → Import → General → Existing Projects into Workspace
   - Select repository root (or the `project` folder) and import.
   - Alternatively, create a new C/C++ Project and copy source files in.
4. Configure toolchain path:
   - Project → Properties → C/C++ Build → Settings
   - Ensure the GCC ARM toolchain paths point to your `arm-none-eabi-*` binaries.
5. Adjust include paths and symbols under: Project → Properties → C/C++ General → Paths and Symbols.

## Building

### From Eclipse
- Right click project → Build Project
- Fix any include/path issues if build fails.

### From command line (if Makefile provided)
Open a terminal in the project root and run:
```bash
make clean
make all
```
Or:
```bash
make
```
(Adjust commands to the repository's Makefile targets.)

## Flashing

You can flash the built ELF or BIN using STM32CubeProgrammer, OpenOCD, or st-flash.

### STM32CubeProgrammer (GUI or CLI)
Example CLI:
```bash
STM32_Programmer_CLI -c port=SWD -d build/your_project.bin 0x08000000
```

### OpenOCD + arm-none-eabi-gdb
Start OpenOCD with your interface/target config:
```bash
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg
```
Then in another terminal:
```bash
arm-none-eabi-gdb build/your_project.elf
(gdb) target remote :3333
(gdb) monitor reset init
(gdb) load
(gdb) monitor reset run
```

### st-flash (from stlink-tools)
```bash
st-flash write build/your_project.bin 0x8000000
```

Adjust addresses and tool parameters for your board.

## Running and Verifying UART

1. Connect the board via ST-LINK (for debug/flash) and a serial adapter (if UART pins are routed to USB-to-UART).
2. Open a serial terminal:
   - Baud rate: commonly 115200
   - Data bits: 8, Parity: None, Stop bits: 1 (115200 8N1)
3. Reset or start the MCU and observe UART output or send data to MCU.

Example: If the demo prints a startup message, you should see something like:
```
STM32F4 UART example
Hello from UART
```

## Debugging in Eclipse

1. Create a Debug Configuration:
   - Run → Debug Configurations → GDB OpenOCD Debugging (or use the ST-Link debug plugin)
   - Point to the project ELF and configure OpenOCD interface/target.
2. Start the debug session and use breakpoints, step-through and variable watches as usual.

## Troubleshooting

- Build errors:
  - Verify include paths and macro definitions (MCU/board macro).
  - Ensure the correct compiler toolchain is selected.
- Flashing failures:
  - Check ST-Link connection, board power, and cable.
  - Try resetting the target or using different programmer options.
- No serial output:
  - Check UART pin mapping and alternate function configuration.
  - Confirm the correct UART peripheral (USART1, USART2, etc.) and pins for your board.
  - Use an oscilloscope or logic analyzer to confirm TX activity.

## Contribution

Contributions are welcome. Typical ways to contribute:
- Open an issue describing the bug or enhancement.
- Submit a pull request with clear description and change list.
- If you want me to open a PR adding this README to the repository, I can prepare that for you.

Please follow repository coding and commit message conventions.

## License

See the LICENSE file in the repository for license terms. If no license is present, contact the repository maintainers to clarify usage permissions.

## References

- ARM GNU Toolchain: https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm
- STM32CubeProgrammer: https://www.st.com/en/development-tools/stm32cubeprog.html
- OpenOCD: http://openocd.org/

---
Repository: hcmut-works/stm32f4xx_uart_ex
Developed with: Eclipse Embedded C (Eclipse CDT + Embedded plugins)

# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build commands

This is an STM32CubeIDE managed makefile project for `STM32F407VGTx`. The generated Debug build files live under `Debug/`.

```bash
make -C Debug
make -C Debug clean
```

The Debug build produces `Driver_stm32_f4.elf`, `Driver_stm32_f4.hex`, `Driver_stm32_f4.map`, and `Driver_stm32_f4.list` from the generated makefile. The project expects the STM32 GNU ARM toolchain commands such as `arm-none-eabi-gcc`, `arm-none-eabi-size`, `arm-none-eabi-objdump`, and `arm-none-eabi-objcopy` to be available.

No repository-level test runner, lint command, or single-test command was found. Validate changes by building the relevant CubeIDE configuration.

## Project structure

- `Src/main.c` is the application entry point. It enables the FPU, initializes SysTick, configures GPIO pins, sets up USART1 directly through registers, runs DSP calculations, and streams formatted signal data over UART.
- `Driver/Core` contains custom bare-metal STM32 peripheral drivers. Headers are in `Driver/Core/Inc`; sources are in `Driver/Core/Src`. The common `system.h` header pulls in STM32 register definitions plus GPIO, RCC, SPI, and SYSCFG driver interfaces.
- `Driver/CSMIS` contains CMSIS/CMSIS-DSP headers and the linked DSP library. The Debug linker uses `Driver/CSMIS/DSP/build` and links `arm_cortexM4lf_math` with Cortex-M4 hard-float settings.
- `DSP/Day1` contains signal-processing exercises and helpers for basic statistics, convolution, running sum, and UART plotting. It depends on CMSIS-DSP types from `arm_math.h`.
- `DSP/Day2` contains ECG signal-processing code. `ecg.h` defines a 512-sample ECG excerpt, one-sided DFT constants, and `dft_real_one_sided_f32()`.
- `Peripheral` contains ST7735 display and font support. Related initialization code exists in `Src/main.c`, but much of the display setup is currently commented out.
- `Startup/startup_stm32f407vgtx.s` and `STM32F407VGTX_FLASH.ld` / `STM32F407VGTX_RAM.ld` are target-specific startup and linker files.

## Build configuration notes

The CubeIDE metadata in `.project` and `.cproject` is part of the build definition. Keep source folder, include path, MCU, FPU, float ABI, preprocessor symbol, library path, and linker script changes in sync with those files when adding modules.

Important Debug configuration details observed in the project metadata:

- MCU: `STM32F407VGTx`
- CPU/FPU: Cortex-M4, `fpv4-sp-d16`, hard-float ABI
- Defines include `DEBUG`, `ARM_MATH_CM4`, `STM32`, `STM32F4`, and `STM32F407VGTx`
- Linker script: `STM32F407VGTX_FLASH.ld`
- DSP library path: `Driver/CSMIS/DSP/build`
- DSP library: `arm_cortexM4lf_math`
- Float printf/scanf support is enabled in the Debug linker flags

## Collaboration workflow

This project is a bare-metal STM32F407 Discovery learning project based on a Udemy course. Keep the custom driver style close to HAL/OOP patterns: use handle structs, config structs, and clear peripheral APIs rather than unrelated abstractions.

When changing a topic or module, maintain topic documentation under `document/`. For example, SPI work should update or create a markdown file explaining SPI concepts, register flow, and how the project code uses it.

When adding or rewriting functions, add concise function documentation in code that explains purpose, parameters, return value when applicable, and any hardware/register assumptions that are not obvious from the function name.

The assistant's role in this repository is to fix code and guide the user through rewriting the drivers and DSP examples, not only to provide final code.

## Internal rules (local only)

If `.claude/` folder exists in the repo, it contains detailed workflow/token rules not committed to git:
- `.claude/workflow.md` — session strategy, code style, driver patterns
- `.claude/token-rules.md` — token budget, reading strategy
- `.claude/session-template.md` — template for starting each session

These files are excluded via `.gitignore` and serve as personal workflow reference.

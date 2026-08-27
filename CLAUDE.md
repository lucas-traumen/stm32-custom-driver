# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build commands

At present, I'm using cubeide debug,constraint be built and debug

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

When adding or rewriting functions, add concise function documentation in code that explains purpose, parameters, return value when applicable, and any hardware/register assumptions that are not obvious from the function name (Doxygen standard, coding convention).

Detailed role, per-peripheral documentation rule, and session workflow live in `.claude/workflow.md` (see below) — do not duplicate them here.

## Internal rules (local only)

If `.claude/` folder exists in the repo, it contains detailed workflow/token rules not committed to git:
- `.claude/OVERVIEW.md` — index of the files below, plus implementation memory
- `.claude/workflow.md` — session strategy, code style, driver patterns, assistant role, doc format
- `.claude/token-rules.md` — token budget, reading strategy
- `.claude/session-template.md` — template for starting each session

These files are excluded via `.gitignore` and serve as personal workflow reference.

<!-- gitnexus:start -->
# GitNexus — Code Intelligence

This project is indexed by GitNexus as **stm32-custom-driver** (35002 symbols, 38965 relationships, 153 execution flows). Use the GitNexus MCP tools to understand code, assess impact, and navigate safely.

> Index stale? Run `node .gitnexus/run.cjs analyze` from the project root — it auto-selects an available runner. No `.gitnexus/run.cjs` yet? `npx gitnexus analyze` (npm 11 crash → `npm i -g gitnexus`; #1939).

## Always Do

- **MUST run impact analysis before editing any symbol.** Before modifying a function, class, or method, run `impact({target: "symbolName", direction: "upstream"})` and report the blast radius (direct callers, affected processes, risk level) to the user.
- **MUST run `detect_changes()` before committing** to verify your changes only affect expected symbols and execution flows. For regression review, compare against the default branch: `detect_changes({scope: "compare", base_ref: "stm32F4-cubeide"})`.
- **MUST warn the user** if impact analysis returns HIGH or CRITICAL risk before proceeding with edits.
- When exploring unfamiliar code, use `query({search_query: "concept"})` to find execution flows instead of grepping. It returns process-grouped results ranked by relevance.
- When you need full context on a specific symbol — callers, callees, which execution flows it participates in — use `context({name: "symbolName"})`.
- For security review, `explain({target: "fileOrSymbol"})` lists taint findings (source→sink flows; needs `analyze --pdg`).

## Never Do

- NEVER edit a function, class, or method without first running `impact` on it.
- NEVER ignore HIGH or CRITICAL risk warnings from impact analysis.
- NEVER rename symbols with find-and-replace — use `rename` which understands the call graph.
- NEVER commit changes without running `detect_changes()` to check affected scope.

## Resources

| Resource | Use for |
|----------|---------|
| `gitnexus://repo/stm32-custom-driver/context` | Codebase overview, check index freshness |
| `gitnexus://repo/stm32-custom-driver/clusters` | All functional areas |
| `gitnexus://repo/stm32-custom-driver/processes` | All execution flows |
| `gitnexus://repo/stm32-custom-driver/process/{name}` | Step-by-step execution trace |

## CLI

| Task | Read this skill file |
|------|---------------------|
| Understand architecture / "How does X work?" | `.claude/skills/gitnexus/gitnexus-exploring/SKILL.md` |
| Blast radius / "What breaks if I change X?" | `.claude/skills/gitnexus/gitnexus-impact-analysis/SKILL.md` |
| Trace bugs / "Why is X failing?" | `.claude/skills/gitnexus/gitnexus-debugging/SKILL.md` |
| Rename / extract / split / refactor | `.claude/skills/gitnexus/gitnexus-refactoring/SKILL.md` |
| Tools, resources, schema reference | `.claude/skills/gitnexus/gitnexus-guide/SKILL.md` |
| Index, status, clean, wiki CLI commands | `.claude/skills/gitnexus/gitnexus-cli/SKILL.md` |

<!-- gitnexus:end -->

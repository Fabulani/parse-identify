# 🔍 ParseIdentify

`ParseIdentify` is a parser for binary files containing the SATA disk's response for the `ATA IDENTIFY` command.

Specifically, it'll print the following to the command line:

- Model number.
- Highest supported Ultra DMA mode.
- SMART self-test support.

**Table of contents:**

- [🔍 ParseIdentify](#-parseidentify)
  - [Install](#install)
  - [Usage](#usage)
  - [Data](#data)
  - [Building on Windows](#building-on-windows)
  - [Building on Linux](#building-on-linux)
  - [Output examples](#output-examples)

## Install

Installers for Windows (`.msi`) and Linux (`.deb`, `.tar.gz`) are available in the [Releases](https://github.com/Fabulani/parse-identify/releases) section of this repo.

On Windows, download the installer, open it and follow its instructions.

On Linux, run:

```sh
dpkg -i ParseIdentify-2.0-Linux.deb
```

## Usage

`ParseIdentify` expects a single command line argument: the path to the binary file containing the `ATA IDENTIFY` response. See the [Data](#data) section for more details regarding the expected data structure.

On Windows:

```cmd
.\ParseIdentify.exe path\to\file.bin
```

On Linux:

```sh
ParseIdentify path/to/file.bin
```

Running `ParseIdentify` without arguments, with `-h`or with `--help` will print usage instructions:

```txt
Usage: ParseIdentify file_path
```

## Data

Example input files are located inside the `data` folder. Each binary file contains 256 words of 2 bytes each.

The file contents are described in pages 90-116 of the AT Attachment 8 - ATA/ATAPI Command Set (ATA8-ACS), found in [docs/D1699r3f-ATA8-ACS.pdf](docs/D1699r3f-ATA8-ACS.pdf). They consist of the SATA disk's response for the `ATA IDENTIFY` command. Of interest to this project are:

- words 27-46: Model number as 40 ASCII characters.
- word 88, bits 0-6: Ultra DMA modes support. For bit `x`, if `x=1`, then Ultra DMA Mode `x` and below are supported.
- word 87, bit 1: if `1`, SMART self-test is supported.

> [!NOTE]
> 16-bit parameters are big-endian, while 32-bit parameters are little-endian.
>
> Source: page 90, section `7.16.2 Description` of the ATA8-ACS.

## Building on Windows

Pre-requisites:

- CMake >= `3.30` (tested on `4.0.2`).
- Visual Studio (tested on `17 2022`) with `C++ CMake tools for Windows` and `C++ build tools`.
- Ninja (tested on `1.11.1.git.kitware.jobserver-1`).
- Wix command-line tool and UI extension (tested on `4.0.4`).

Launch either the `x64 Native Tools Command Prompt for VS 2022` or the `Developer Command Prompt for VS 2022` and run:

```cmd
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

A `ParseIdentify.exe` executable is now added to the `build` folder.

For the `.msi` installer, simply run:

```cmd
cmake --build build --target package
```

The `ParseIdentify-<VERSION>-win<32/64>.msi` installer can now be found in the `build` folder.

> [!NOTE]
>
> `Command Prompt for VS 2022` sets up the MSVC environment such that `cl.exe` is usable by CMake and Ninja. Using regular Powershell and cmd results in `ninja: fatal: CreateProcess: Access is denied.`, as CMake tries to use `cc` from Cygwin, which causes a mismatch. To avoid replacing Cygwin with MinGW, we stick with VS command prompts.

## Building on Linux

Pre-requisites:

- CMake >= `3.30` (tested on `4.0.2`).
- g++ (tested on `11.4.0`).
- ninja (tested on `1.10.1`)

Build with CMake and ninja:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -G Ninja && cmake --build build
```

The `ParseIdentify` binary is created in the `build` folder.

For the `.deb` and `.tar.gz` installers, run:

```sh
cmake --build build --target package
```

`ParseIdentify-<version>-Linux.<deb/tar.gz>` can be found in the `build` folder.

## Output examples

> [!NOTE]
>
> Outputs are colorized: red for falsy, green for truthy, cyan for header and divs, and white for the rest.
>
> Colors might not work on Windows Powershell and CMD. I tested on mine, and it only failed to work in the `Developer Command Prompt for VS 2022`.

`identify1.bin`:

```txt
============================================================
                    ATA IDENTIFY RESULTS
============================================================
File                          : ..\data\identify1.bin
Status                        : Successfully opened
------------------------------------------------------------
Model Number                  : FUJITSU MJA2320BH G2
Supported Ultra DMA Modes     : 5 and below
SMART Self-Test Support       : Yes
------------------------------------------------------------
```

`identify2.bin`:

```txt
============================================================
                    ATA IDENTIFY RESULTS
============================================================
File                          : ..\data\identify2.bin
Status                        : Successfully opened
------------------------------------------------------------
Model Number                  : WDC WD2500AAJS-60Z0A0
------------------------------------------------------------
```

`identify3.bin`:

```txt
============================================================
                    ATA IDENTIFY RESULTS
============================================================
File                          : ..\data\identify3.bin
Status                        : Successfully opened
------------------------------------------------------------
Model Number                  : WDC WD5002AALX-00J37A0
Supported Ultra DMA Modes     : 6 and below
SMART Self-Test Support       : Yes
------------------------------------------------------------
```

# 🔍 ParseIdentify

`ParserIdentify` is a parser for binary files containing the SATA disk's response for the `ATA IDENTIFY` command.

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

A Windows binary is provided in the `Releases` section of the repository.

For Linux, see [Building on Linux](#building-on-linux).

## Usage

`ParseIdentify` expects a single command line argument: the path to the binary file containing the `ATA IDENTIFY` response. See the [Data](#data) section for more details regarding the expected data structure.

```sh
# Windows
.\ParseIdentify.exe path\to\file.bin

# Linux
./ParseIdentify path/to/file.bin
```

> [!NOTE]
>
> On Windows, the built executable is in `build\Release`. On Linux, it is inside `build`.

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
- Visual Studio (tested on `17 2022`). `C++11` or higher.
- Wix command-line tool and UI extension (tested on `4.0.4`).

Create a `build` directory and `cd` into it:

```ps
mkdir build
cd build
```

Build the project with:

```ps
cmake .. -G "Visual Studio 17 2022" 
cmake --build . --config Release
```

A `ParseIdentify.exe` executable is now added to the `build\Release` folder. To build the `.msi` installer, simply run:

```ps
cpack
```

The `ParseIdentify-<VERSION>-win64.msi` installer can now be found in the `build` folder.

## Building on Linux

Pre-requisites:

- CMake >= `3.30` (tested on `4.0.2`).
- g++ (tested on `11.4.0`).

Create the `build` directory:

```sh
mkdir build && cd build
```

Build with CMake:

```sh
cmake .. && make
```

The `ParseIdentify` binary is created in the `build` folder.

## Output examples

> [!NOTE]
>
> Outputs are colorized: red for falsy, green for truthy, cyan for header and divs, and white for the rest.

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

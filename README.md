# brancco

Parser and pretty printer for binary files containing the SATA disk's response for the `ATA IDENTIFY` command.

Specifically, it'll print the following to the command line:

- Model number.
- Highest supported Ultra DMA mode.
- SMART self-test support.

## Setup

For development, it is recommended to use VS Code dev containers.

## Usage

Command:

```sh
./main <input_file>
```

where `<input_file>` is a 512-byte binary file containing the SATA disk's response for the `ATA IDENTIFY` command.

## Data

Input files are located inside the `data` folder. Each binary file contains 256 words of 2 bytes each.

The file contents are described in pages 90-116 of the AT Attachment 8 - ATA/ATAPI Command Set (ATA8-ACS), found in [docs/D1699r3f-ATA8-ACS.pdf](docs/D1699r3f-ATA8-ACS.pdf). Of interest to this project are:

- words 27-46: Model number as 40 ASCII characters.
- word 88, bits 0-6: Ultra DMA modes support. For bit `x`, if `x=1`, then Ultra DMA Mode `x` and below are supported.
- word 87, bit 1: if `1`, SMART self-test is supported.

> [!NOTE]
> 16-bit parameters are big-endian, while 32-bit parameters are little-endian.
>
> Source: page 90, section `7.16.2 Description` of the ATA8-ACS.

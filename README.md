# GigaCell

**GigaCell** is a transistor-level automatic standard-cell layout generator.

This repository currently implements **1D transistor placement** for standard-cell layout generation. Routing is not included at this stage.

## Features

- Transistor-level standard-cell layout generation
- 1D transistor placement
- Netlist-based cell selection
- Command-line flow through `GigaPlace`

## Requirements

- CMake
- Make
- C/C++ compiler

## Build

Initialize and update submodules:

```bash
git submodule update --init --recursive
```

Build the project:

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

Run `GigaPlace` with an input netlist and a target cell name:

```bash
./GigaPlace -n <path/to/netlist> -c <cell_name>
```

## Arguments

| Argument | Description |
|---|---|
| `-n <path/to/netlist>` | Path to the input transistor-level netlist |
| `-c <cell_name>` | Name of the target standard cell |

## Example

```bash
./GigaPlace -n ../examples/cells.spi -c AN2D2
```

## Current Status

GigaCell currently supports **1D transistor placement only**.

The following features are not included yet:

- In-cell routing
- DRC/LVS verification
- GDS generation
- Complete standard-cell layout generation flow

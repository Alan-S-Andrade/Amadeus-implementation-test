# Amadeus - Implementation Developer Test

## Description
This command-line utility processes data in XML and JSON formats, calculates the average salary, identifies the highest paid employee, and sorts the employees by ID.

## Requirements
- C++ compiler (g++)
- `tinyxml2` library
- `nlohmann/json` library

## Installation
To install the XML and JSON libs in Ubuntu run:

```sh
sudo apt-get update
sudo apt-get install -y libtinyxml2-dev nlohmann-json3-dev
```

For macos installation:
```sh
brew install tinyxml2 nlohmann-json
```

## Compiling and Executing

run:

```sh
./run.sh <xml|json> <input_filename>
```

Example:

```sh
./run.sh json testing/employees1.json
```

# LSB Steganography

LSB Steganography is a C program that allows users to hide and retrieve secret messages within image files using the Least Significant Bit (LSB) method.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Introduction

The LSB Steganography project provides a simple and effective way to hide and extract messages within image files. It uses the Least Significant Bit (LSB) method, which involves manipulating the least significant bit of each pixel to encode binary data. This can be used for secure communication and data hiding purposes.

## Features

- Hide secret messages within image files.
- Extract hidden messages from image files.
- Support for various image formats.

## Getting Started

### Prerequisites

- GCC (GNU Compiler Collection)

### Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/your-username/LSB-Steganography.git
    cd LSB-Steganography
    ```

2. Compile the program:

    ```bash
   gcc *.c
    ```

3. Run the program:

    ```bash
    ./a.out
    ```

## Usage

1. Choose the operation type: encoding or decoding.
2. Provide the source image file and, if applicable, the message file.
3. Follow the on-screen instructions to complete the process.

## Contributing

Contributions are welcome! If you find a bug, have a feature request, or want to contribute in any other way, please open an issue or submit a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

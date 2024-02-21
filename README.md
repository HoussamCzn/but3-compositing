# Compositing app

- [Compositing app](#compositing-app)
  - [Overview](#overview)
  - [Features](#features)
  - [Dependencies](#dependencies)
  - [Installation](#installation)
    - [Prerequisites](#prerequisites)
    - [Setup](#setup)
    - [Compilation](#compilation)
  - [Usage](#usage)
    - [Key Shortcuts](#key-shortcuts)
  - [License](#license)

## Overview

This application is a small tool designed for compositing images using PPM files. It allows users to load a directory of PPM images, adjust their composite weights in a user-friendly UI, and save the outcome in either ASCII or binary PPM format.

> **Note** : The binary format might results in unexpected bugs (noticed on Windows). This will be fixed at a later date.

## Features

- Load a directory of PPM images for compositing.
- Adjust the weight of each image contributing to the composite.
- Save the composite image in ASCII or binary PPM format.
- User-friendly interface with support for key shortcuts for efficient navigation and operations.

## Dependencies

- Qt6 for the graphical user interface.
- CMake for building the application.
- A C++ compiler with C++17 support.

## Installation

### Prerequisites

Ensure you have the following installed:
- Qt6
- CMake (version 3.14 or later)
- A C++ compiler (with support for at least C++20)

### Setup

The application's dependencies are managed via CMake, simplifying the setup process. For detailed instructions, refer to the compilation section.

### Compilation

1. Clone the repository to your local machine.
2. Navigate to the project directory.

Following the steps in the [BUILDING](BUILDING.md) file will compile the application and produce an executable.

## Usage

Launch the application, then use the menu or the following key shortcuts to navigate:

### Key Shortcuts

- `Ctrl+O`: Open a directory containing PPM images.
- `Ctrl+S`: Save the composite image.
- `Ctrl+R`: Reset the composite to remove all images.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE.md) file for details.

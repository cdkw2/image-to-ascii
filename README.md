# ASCII Image Converter

This project is a C program that converts images into ASCII art and displays them in the terminal. The ASCII representation is scaled to fit the terminal window while preserving the original image's aspect ratio.

## Features

- Converts various image formats to ASCII art
- Automatically scales the output to fit the terminal window
- Preserves the original image's aspect ratio
- Centers the ASCII art in the terminal

## Requirements

- A C compiler (e.g., gcc)
- The `stb_image.h` library (included in the project)

## Usage

Run the program with an image file as an argument:

```
./ascii path/to/your/image.jpg
```

The ASCII art representation of the image will be displayed in your terminal.

## Supported Image Formats

This program supports various image formats, including:

- JPEG
- PNG
- BMP
- GIF

## Limitations

- The quality of the ASCII art depends on the terminal size and the complexity of the original image.
- Very small terminal windows may result in loss of detail.
- The program assumes a terminal with a dark background and light text for best results.

## Acknowledgements

This project uses the `stb_image.h` library by Sean Barrett, which is in the public domain.

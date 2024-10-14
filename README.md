# Get Next Line (GNL)

![C](https://img.shields.io/badge/language-C-blue.svg)

A C function that reads a line from a file descriptor, designed to work with multiple file descriptors efficiently.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Function Prototype](#function-prototype)
- [How It Works](#how-it-works)
- [Installation](#installation)
- [Usage](#usage)
- [Implementation Details](#implementation-details)
- [Bonus Features](#bonus-features)
- [Challenges and Solutions](#challenges-and-solutions)
- [Performance Considerations](#performance-considerations)
- [Contributing](#contributing)
- [License](#license)

## Overview

Get Next Line (GNL) is a programming project that challenges you to create a function that reads a line from a file descriptor. This project is part of the 42 school curriculum and focuses on important concepts such as static variables, memory management, and file I/O operations in C.

## Features

- Read lines from any file descriptor (including standard input)
- Handle multiple file descriptors simultaneously
- Efficient memory management
- Customizable buffer size via compilation flag
- Robust error handling

## Function Prototype

```c
char *get_next_line(int fd);
```

## How It Works

1. The function reads from the file descriptor into a buffer.
2. It accumulates the read content in a "stash" until a newline is found.
3. When a newline is encountered, it extracts the line and updates the stash for the next call.
4. If the end of the file is reached, it returns the remaining content.

## Installation

1. Clone the repository:
   ```
   git clone https://github.com/g-garibotti/get_next_line.git
   ```
2. Include the header in your C file:
   ```c
   #include "get_next_line.h"
   ```

## Usage

Compile your program with the Get Next Line source files and specify the buffer size:

```
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 your_program.c get_next_line.c get_next_line_utils.c
```

Example usage in your C program:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main()
{
    int fd = open("example.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return 0;
}
```

## Implementation Details

- `get_next_line.c`: Main function implementation
- `get_next_line.h`: Header file with function prototypes and necessary includes
- `get_next_line_utils.c`: Utility functions for string manipulation

Key functions:
- `initialize_stash`: Prepares the stash for reading
- `read_and_fill`: Reads from the file descriptor and fills the stash
- `line_update_buffer`: Extracts a line from the stash and updates the buffer

## Bonus Features

- Handles multiple file descriptors without losing the reading thread on each of them
- Uses only one static variable
- Manages input from both files and standard input seamlessly

## Challenges and Solutions

1. **Challenge**: Efficient memory management
   **Solution**: Careful allocation and deallocation of memory, using a static variable to maintain state between function calls

2. **Challenge**: Handling various buffer sizes
   **Solution**: Implemented a flexible reading mechanism that works with any positive buffer size

3. **Challenge**: Ensuring no memory leaks
   **Solution**: Thorough testing with valgrind and careful review of all memory allocation paths

## Performance Considerations

- The function is optimized to read from the file descriptor only when necessary
- Large buffer sizes may improve performance for large files, but increase memory usage
- Small buffer sizes are more memory-efficient but may require more system calls


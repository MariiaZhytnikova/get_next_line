## Get next line

### Reading a line from a fd is way too tedious

This repository contains a custom implementation of the get_next_line function in C. It reads a file descriptor (e.g., a file or standard input) line by line, returning each line separately. It handles memory management efficiently and ensures that large files or multiple calls can be handled without reading the entire file into memory at once.
Features

  Reads a file descriptor line by line.
  Returns each line as a dynamically allocated string.
  Bonus handles multiple calls efficiently, with the ability to maintain the position of the read pointer.
  Works with standard input, files, or any valid file descriptor.


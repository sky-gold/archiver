# Archiver

Implementation of the archiver based on [Huffman algorithm](https://en.wikipedia.org/wiki/Huffman_coding ).

The archiver program has the following command line interface:
* `archiver -c archive_name file1 [file2 ...]` - compress the files `file1, file2, ...` and save the result to the file `archive_name`.
* `archiver -d archive_name` - compress decompress files from the archive `archive_name` and put them in the current directory.
* `archiver -h` - output help on using the program.
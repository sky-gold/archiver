#pragma once

#include <string>
#include "symbol.h"

const std::string HELP_TEXT =
    "archiver -c archive_name file1 [file2 ...] - archive the files and save the result to the archive_name\n"
    "archiver -d archive_name - unarchive files from the archive_name  and put in the current directory\n"
    "archiver -h - outputs this text\n";

const Symbol FILENAME_END = Symbol(256);
const Symbol ONE_MORE_FILE = Symbol(257);
const Symbol ARCHIVE_END = Symbol(258);

const size_t BIT_IN_BYTE = 8;
const size_t SYMBOL_LENGTH = 9;

const int ERROR_CODE = 111;

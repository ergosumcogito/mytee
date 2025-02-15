# Tee Command
**C version 17**

## How to build project:
1. Do `make` in root folder
2. Execute your command.

Example `echo 'Hello, World!' | ./mytee output.txt`

## How to run tests:
- `make test` - run both unit and integrations tests
- `make test-unit` - run only unit tests
- `make test-integration` - run only integratoin tests

In addition: `make clean` - removes not only buid files, but **also** .txt for tests.

## Features
- supports multiple files
- one thread for console, dedicated thread for each file

## Supported flags
- `-a or --append` : enable append to file
- `-i or --ignore-interrupts` : signore interrupts, such as Ctrl+C
- `--output-error=warn or --output-error=exit`
  - `warn` : show error, files with error, complete remaning program
  - `exit` : show error and terminate program
- `--help` : show usage info

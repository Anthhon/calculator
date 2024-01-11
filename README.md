# Calculator

`Calculator` is a terminal based calculator implemented entirely in C.

## Usage

```bash
calc <formula>
```

## Installing

```bash
git clone git@github.com:Anthhon/calculator.git
cd calculator
make build-linux # or make build-windows
./build/calc -t
```

After using these commands above, you should see a sequence of successful messages on your screen, signalizing that the application is working correctly. After that, the program can be installed automatically into your Linux system by using this command:

```bash
make install-linux
```

## Project Roadmap

- [X] Arguments parsing
- [X] Implement lexer to tokenize input
- [X] Implement formula interpreter
- [X] Create test script

## Features

- [X] Handle 4 basic operations (+, -, *, /)
- [X] Handle number powering (^)
- [X] Negative number operations
- [X] Float number operations
- [X] Handle {[()]} symbols
- [ ] Handle logarithmic

## Contact

If you have any questions, suggestions, or need assistance, feel free to reach out to the project maintainers by [opening an issue](https://github.com/Anthhon/calculator/issues).

Also, don't forget to check the [project roadmap section](https://github.com/Anthhon/calculator#project-roadmap) and see if anything interest you.

We appreciate your interest in contributing to `calculator` and look forward to your contributions!

### References

- [How to write an interpreter from scratch](https://www.toptal.com/scala/writing-an-interpreter)

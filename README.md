# Triangles

## Introduction

This project is an implementation of the geometry figures and interaction them each other.
The main program is output triangle id's, which intersect.

## Build and Run

If you want to build the project, write this in the project directory:
```
cmake -S . -B build
cmake --build build
```

After that, you can run main target program:

```
./build/src/main
```

## Tests
### Unit

If you want to run unit tests, generate Makefiles with the WITH_UNIT_TEST flag:
```
cmake [...] -DWITH_UNIT_TEST=1
```

Then build `unit_test` target:
```
cmake --build build --target unit_test
```

After that, run:
```
./build/tests/unit_test
```

### Benchmarks

Also you can compare the performance of triangle intersection finding with and without octotry technology.

Generate Makefiles with the WITH_BENCHMARKS flag:
```
cmake [...] -DWITH_BENCHMARKS=1
```

Then build `benchs` target:
```
cmake --build build --target unit_test
```

Finally, run the program:
```
./build/tests/benchs
```

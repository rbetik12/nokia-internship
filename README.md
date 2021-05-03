# CSV Excel Parser

Application that parses primitive excel-like formulas. This app is able to evaluate formulas recursively, so cell formulas
can refer to cells with formulas.

Supports following operations (ARG can be a number or cell address):
- ARG1 + ARG2
- ARG1 - ARG2
- ARG1 * ARG2
- ARG1 / ARG2

## Testing

1. Evaluator can checks for **loop** in formulas. Consider the example file:

    ```bash
    ,A,B
    1,=B1+A1,3
    2,2,=B1+A1
    30,0,1
    ```

    The output will be:

    ```bash
            A       B
    1       #ERROR  3
    2       2       #ERROR
    30      0       1
    ```

2. Also it checks for **zero division**.

    ```bash
    #input file
    ,A,B
    1,1,3
    2,2,1
    30,0,=A1/0
    ```

    The output will be:

    ```bash
            A       B
    1       1       3
    2       2       1
    30      0       #ERROR
    ```
3. **Incorrect address** handling.
    ```bash
    #input file
    ,A,B
    1,1,3
    2,=A1/С1,1
    30,0,1
    ```

    The output will be:

    ```bash
            A       B
    1       1       3
    2       #ERROR  1
    30      0       1
    ```
4. Parser also can check for **table row length**
    ```bash
    #input file
    ,A,B
    1,1
    2,=A1/С1,1
    30,0,1
    ```

    The output will be:

    ```bash
    Invalid row length. At row 1
    ```
5. Parser checks **cell values** to be a formula or a number
    ```bash
    #input file
    ,A,B
    1,1,kek
    2,=A1/С1,1
    30,0,1
    ```

    The output will be:

    ```bash
    Invalid cell value. At row 1 col 2
    ```

All the exceptions should be handled by the caller code.

## Building

Application is written in C++ 11 and uses only cross-platform standard library functions, so it should compile on any modern
OS with compiler that supports C++ 11. It uses CMake for building.

Was tested on `Windows 19041 with Visual Studio 2019 (16.8.4) MSVC v142 (14.28)`

Build process is pretty simple. First of all run:

```bash
cmake .
```
That will create all the necessary files for your OS-native build system. Next steps depends on a OS you are using.
For windows you should use Visual Studio GUI.

To run the application:

```bash
./CSVParser <filename>
```



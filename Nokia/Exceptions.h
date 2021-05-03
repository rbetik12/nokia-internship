#include <string>

class InvalidRowLengthException : public std::exception {
public:
    InvalidRowLengthException(int row) {
        whatStr = "Invalid row length. At row " + std::to_string(row);
    }

    const char* what() const throw () {
        return whatStr.c_str();
    }
private:
    std::string whatStr;
};

class InvalidCellValueException : public std::exception {
public:
    InvalidCellValueException(int row, int col) {
        whatStr = "Invalid cell value. At row " + std::to_string(row) + " col " + std::to_string(col);
    }

    const char* what() const throw () {
        return whatStr.c_str();
    }

private:
    std::string whatStr;
};

class InvalidCellAddressException : public std::exception {
public:
    InvalidCellAddressException(std::string cell) {
        whatStr = "Invalid cell address. Cell " + cell + " doesn't exist";
    }

    const char* what() const throw () {
        return whatStr.c_str();
    }

private:
    std::string whatStr;
};

class FormulaLoopException : public std::exception {
public:
    FormulaLoopException(std::string formula) {
        whatStr = "Formula " + formula + " appears in solution tree multiple times";
    }

    const char* what() const throw () {
        return whatStr.c_str();
    }

private:
    std::string whatStr;
};

class ZeroDivisionException : public std::exception {
public:
    const char* what() const throw () {
        return "Zero division!";
    }
};
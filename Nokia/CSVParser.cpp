#include "CSVParser.h"
#include <fstream>
#include <iostream>
#include "Exceptions.h"

CSVParser::CSVParser() {}

CSVParser::~CSVParser() {
    Clear();
}

void CSVParser::PrintTable() {
    std::string rowDel = "\t";
    int result;
    std::vector<std::string> errorsList;

    std::cout << rowDel;
    for (auto col : colNames) {
        std::cout << col << rowDel;
    }
    std::cout << std::endl;

    for (int row = 0; row < rowNames.size(); row++) {
        std::cout << rowNames[row] << rowDel;
        for (int col = 0; col < colNames.size(); col++) {
            std::string el = rowColMap[rowNames[row]][colNames[col]];
            if (el[0] == '=') {
                usedFormulas.clear();
                try {
                    result = CalculateFormula(el);
                    std::cout << result << rowDel;
                }
                catch (std::exception& e) {
                    std::cout << "#ERROR" << rowDel;
                }
            }
            else {
                std::cout << el << rowDel;
            }
        }
        std::cout << std::endl;
    }
}

void CSVParser::ParseFile(std::string filename, std::string delimiter) {
    Clear();
    std::ifstream inputStream(filename);

    for (std::string line; std::getline(inputStream, line);) {
        rawLines.push_back(line);
    }

    ParseCSVLines(delimiter);
}

void CSVParser::ParseCSVLines(std::string delimiter) {
    std::vector<std::string> splittedRow;
    std::vector<std::string> formulaArgs;
    std::string formulaOp;
    std::string currentRow;
    uint64_t colNum;
    int rowLength = 0;
    int rowNum = 1;

    colNames = Split(rawLines[0], delimiter);
    colNames.erase(colNames.begin());
    rawLines.erase(rawLines.begin());

    rowLength = colNames.size();

    for (auto row : rawLines) {
        splittedRow = Split(row, delimiter);
        currentRow = splittedRow[0];
        rowNames.push_back(currentRow);
        splittedRow.erase(splittedRow.begin());
        colNum = 0;

        if (splittedRow.size() != rowLength) {
            throw InvalidRowLengthException(rowNum);
        }

        for (auto value : splittedRow) {
            if (!ValidateCellValue(value)) {
                throw InvalidCellValueException(rowNum, colNum + 1);
            }

            if (value[0] == '=') {
                formulas[value] = nullptr;
            }
            colRowSearchMap[colNames[colNum] + currentRow] = value;
            rowColMap[currentRow][colNames[colNum]] = value;
            colNum += 1;
        }
        rowNum += 1;
    }
}

int CSVParser::CalculateFormula(std::string formula) {
    if (usedFormulas.find(formula) != usedFormulas.end()) {
        throw FormulaLoopException(formula);
    }
    else {
        usedFormulas[formula] = formula;
    }

    if (formulas[formula] != nullptr) {
        return *formulas[formula];
    }
    std::string op = GetOp(formula);

    if (op.empty()) {
        throw InvalidCellAddressException(formula);
    }

    int arg0, arg1, result;
    formula.erase(formula.begin());
    std::vector<std::string> args = Split(formula, op);

    std::string arg0Str = colRowSearchMap[args[0]] == "" ? args[0] : colRowSearchMap[args[0]];
    std::string arg1Str = colRowSearchMap[args[1]] == "" ? args[1] : colRowSearchMap[args[1]];

    if (!ValidateCellValue(arg0Str)) {
        throw InvalidCellAddressException(arg0Str);
    }
    if (!ValidateCellValue(arg1Str)) {
        throw InvalidCellAddressException(arg1Str);
    }
    arg0 = CalcArg(arg0Str);
    arg1 = CalcArg(arg1Str);
    
    switch (op[0]) {
    case '-':
        result = arg0 - arg1;
        break;
    case '+':
        result = arg0 + arg1;
        break;
    case '/':
        if (arg1 == 0) {
            throw ZeroDivisionException();
        }
        result = arg0 / arg1;
        break;
    case '*':
        result = arg0 * arg1;
        break;
    }

    formulas["=" + formula] = new int;
    std::memcpy(formulas["=" + formula], &result, sizeof(result));
    return result;
}

int CSVParser::CalcArg(std::string& argStr) {
    int res;

    if (argStr[0] == '=') {
        if (formulas[argStr] == nullptr) {
            res = CalculateFormula(argStr);
            SaveResult(&formulas[argStr], res);
        }
        else {
            res = *formulas[argStr];
        }
    }
    else {
        res = std::stoi(argStr);
    }

    return res;
}

void CSVParser::SaveResult(int** dest, int result) {
    *dest = new int;
    std::memcpy(*dest, &result, sizeof(result));
}

bool CSVParser::ValidateCellValue(std::string value) {
    if (value[0] == '=') return true;
    if (value.size() == 0) return false;

    for (auto el : value) {
        if (el < '0' || el > '9') {
            return false;
        }
    }
    return true;
}

void CSVParser::Clear() {
    colNames.clear();
    rowNames.clear();
    rawLines.clear();
    colRowSearchMap.clear();
    for (auto entry0 : rowColMap) {
        entry0.second.clear();
    }
    rowColMap.clear();
    for (auto formula : formulas) {
        delete formula.second;
    }
    formulas.clear();
}

std::string CSVParser::GetOp(std::string formula) {
    for (uint64_t i = 0; i < formula.size(); i++) {
        switch (formula[i]) {
        case '-':
            return "-";
        case '+':
            return "+";
        case '/':
            return "/";
        case '*':
            return "*";
        }
    }
    return "";
}

std::vector<std::string> CSVParser::Split(std::string str, std::string delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    uint64_t pos;

    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        tokens.push_back(token);
        str.erase(0, pos + delimiter.length());
    }

    tokens.push_back(str);

    return tokens;
}

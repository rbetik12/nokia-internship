#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

// Parses file line by line.
std::vector<std::string> ParseFile(std::string& filename) {
    std::ifstream inputStream(filename);
    std::vector<std::string> rows;

    for (std::string line; std::getline(inputStream, line);) {
        rows.push_back(line);
    }

    return rows;
}

std::vector<std::string> Split(std::string& str, std::string& delimiter) {
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

// Parses CSV file lines. Returns list of formulas to calculate.
std::vector<std::string> ParseCSVLines(std::vector<std::string> rows,
                                       // ColRow -> value
                                       std::unordered_map<std::string, std::string>& colRowSearchMap,
                                       // Row -> Col -> value
                                       std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& rowColMap) {
    std::vector<std::string> splittedRow;
    std::vector<std::string> headerRow;
    std::vector<std::string> formulas;
    uint64_t colNum = 0;
    std::string delimiter = ",";
    std::string rowName;

    headerRow = Split(rows[0], delimiter);
    headerRow.erase(headerRow.begin());
    rows.erase(rows.begin());

    for (auto row : rows) {
        splittedRow = Split(row, delimiter);
        rowName = splittedRow[0];
        splittedRow.erase(splittedRow.begin());
        colNum = 0;

        for (auto value : splittedRow) {
            if (value[0] == '=') {
                formulas.push_back(value);
            }
            colRowSearchMap[headerRow[colNum] + rowName] = value;
            rowColMap[rowName][headerRow[colNum]] = value;
            colNum += 1;
        }
    }

    return formulas;
}

std::string GetOp(std::string formula) {
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
}

int CalculateFormula(std::unordered_map<std::string, std::string> colRowSearchMap, std::string formula) {
    std::string op = GetOp(formula);
    int arg0, arg1;
    formula.erase(formula.begin());
    std::vector<std::string> args = Split(formula, op);

    arg0 = std::stoi(colRowSearchMap[args[0]]);
    arg1 = std::stoi(colRowSearchMap[args[1]]);

    switch (op[0]) {
    case '-':
        return arg0 - arg1;
    case '+':
        return arg0 + arg1;
    case '/':
        return arg0 / arg1;
    case '*':
        return arg0 * arg1;
    }
}

void PrintTable(std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& colRowMap) {
    for (auto& col : colRowMap) {
        for (auto& row : col.second) {
            std::cout << row.second << ",";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::string filename = "file1.csv";
    std::unordered_map<std::string, std::string> colRowSearchMap;
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> rowColMap;

    std::vector<std::string> lines = ParseFile(filename);
    std::vector<std::string> formulas = ParseCSVLines(lines, colRowSearchMap, rowColMap);

    for (auto formula : formulas) {
        std::cout << formula << " " << CalculateFormula(colRowSearchMap, formula) << std::endl;
    }

    return 0;
}

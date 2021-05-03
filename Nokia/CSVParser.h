#include <vector>
#include <string>
#include <unordered_map>

class CSVParser {
public:
    CSVParser();
    ~CSVParser();

    void PrintTable();
    void ParseFile(std::string filename, std::string delimiter);
private:
    static std::string GetOp(std::string formula);
    static std::vector<std::string> Split(std::string str, std::string delimiter);
    void ParseCSVLines(std::string delimiter);
    int CalculateFormula(std::string formula);
    int CalcArg(std::string& argStr);
    void SaveResult(int** dest, int result);
    bool ValidateCellValue(std::string value);
    void Clear();

private:
    std::vector<std::string> colNames;
    std::vector<std::string> rowNames;
    std::vector<std::string> rawLines;
    std::unordered_map<std::string, std::string> usedFormulas;
    std::unordered_map<std::string, std::string> colRowSearchMap;
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> rowColMap;
    std::unordered_map<std::string, int*> formulas;
};
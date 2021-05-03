#include <vector>
#include <string>
#include <unordered_map>

class CSVParser {
public: 
    CSVParser();
    ~CSVParser();

    std::vector<std::string> GetParsedTable();
private:
    void ParseFile(std::string& filename);
    void ParseCSVLines();
    int CalculateFormula(std::string formula);
    void SaveResult(int** dest, int result);
    std::vector<std::string> lines;
    std::unordered_map<std::string, std::string> colRowSearchMap;
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> rowColMap;
    std::unordered_map<std::string, int*> formulas;
};
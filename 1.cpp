#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

bool endsWith(const std::string& str, const std::string& suffix) {
    if (str.length() >= suffix.length()) {
        return (0 == str.compare(str.length() - suffix.length(), suffix.length(), suffix));
    }
    return false;
}

int main() {
    std::string inputFile;
    std::string outputFile;

    std::cout << "Введите имя входного файла (с расширением .txt): ";
    std::getline(std::cin, inputFile);

    std::cout << "Введите имя выходного файла (с расширением .csv): ";
    std::getline(std::cin, outputFile);

    if (!endsWith(outputFile, ".csv")) {
        if (endsWith(outputFile, ".txt") || outputFile.find('.') == std::string::npos) {
            outputFile += ".csv";
        } else {
            std::cerr << "Некорректный тип файла. Должен быть .csv." << std::endl;
            return 1;
        }
    }

    std::ifstream inFile(inputFile);
    if (!inFile.is_open()) {
        std::cerr << "Не удалось открыть входной файл: " << inputFile << std::endl;
        return 1;
    }

    std::ofstream outFile(outputFile);
    if (!outFile.is_open()) {
        std::cerr << "Не удалось открыть выходной файл: " << outputFile << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string token;
        bool first = true;

        while (std::getline(iss, token, '\t')) {
            if (!first) {
                outFile << ',';
            }
            outFile << token;
            first = false;
        }
        outFile << '\n';
    }

    inFile.close();
    outFile.close();

    std::cout << "Файл " << inputFile << " успешно конвертирован в " << outputFile << std::endl;

    return 0;
}

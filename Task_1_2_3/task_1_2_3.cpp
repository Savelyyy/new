#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <unordered_set>
#include <string>
#include <vector>
#include <sstream>
#include <compareVandR.cpp>

using json = nlohmann::json;

int main() {
    // Открываем и читаем первый JSON-файл
    std::ifstream file1("p10.json");
    if (!file1.is_open()) {
        std::cerr << "Не удалось открыть файл p10.json." << std::endl;
        return 1;
    }
    json json1;
    file1 >> json1;
    file1.close();

    // Открываем и читаем второй JSON-файл
    std::ifstream file2("p9.json");
    if (!file2.is_open()) {
        std::cerr << "Не удалось открыть файл p9.json." << std::endl;
        return 1;
    }
    json json2;
    file2 >> json2;
    file2.close();

    // Создаем unordered_set для хранения значений "name" из второго файла
    std::unordered_set<std::string> names_set;
    for (const auto& item : json2["packages"]) {
        names_set.insert(item["name"].get<std::string>());
    }


    // Создаем JSON-структуру для различий
    json difference1;

    // Проходим по элементам первого файла и сравниваем по полю "name"
    for (const auto& item1 : json1["packages"]) {
        const std::string& name = item1["name"];
        if (names_set.find(name) == names_set.end()) {
            difference1["packages"].push_back(item1);
        }
    }

    // Открываем и записываем JSON-файл для записи различий
    std::ofstream output_file1("difference1.json");
    if (!output_file1.is_open()) {
        std::cerr << "Не удалось открыть файл для записи различий." << std::endl;
        return 1;
    }

    // Записываем JSON-структуру различий в файл
    output_file1 << difference1.dump(4); // Запись с отступами для удобного чтения
    output_file1.close();

    std::cout << "Различия успешно записаны в файл difference1.json." << std::endl;

    // Создаем unordered_set для хранения значений "name" из первого файла
    std::unordered_set<std::string> names_set2;
    for (const auto& item : json1["packages"]) {
    names_set2.insert(item["name"].get<std::string>());
    }

    json difference2;

    // Проходим по элементам второго файла и сравниваем по полю "name"
    for (const auto& item2 : json2["packages"]) {
        const std::string& name = item2["name"];
        if (names_set2.find(name) == names_set2.end()) {
            difference2["packages"].push_back(item2);
        }
    }

    // Открываем и записываем JSON-файл для записи различий
    std::ofstream output_file2("difference2.json"); // Изменено имя переменной
    if (!output_file2.is_open()) {
        std::cerr << "Не удалось открыть файл для записи различий." << std::endl;
        return 1;
    }

    // Записываем JSON-структуру различий в файл
    output_file2 << difference2.dump(4); // Запись с отступами для удобного чтения
    output_file2.close();

    std::cout << "Различия успешно записаны в файл difference2.json." << std::endl;

    // Создаем unordered_map для хранения версий и release "name" из второго файла
    std::unordered_map<std::string, std::pair<std::string, std::string>> versions_map;

    // Проходим по элементам второго файла и сохраняем версии и release
    for (const auto& item : json2["packages"]) {
        const std::string& name = item["name"];
        const std::string& version = item["version"];
        const std::string& release = item["release"];
        versions_map[name] = std::make_pair(version, release);
    }

    // Создаем JSON-структуру для различий (новых версий)
    json difference3;

    // Проходим по элементам первого файла и сравниваем по полю "name"
    for (const auto& item1 : json1["packages"]) {
        const std::string& name = item1["name"];
        const std::string& version1 = item1["version"];
        const std::string& release1 = item1["release"];
        // Проверяем, есть ли такая запись во втором файле
        if (versions_map.find(name) != versions_map.end()) {
            const auto& version_release2 = versions_map[name];
            const std::string& version2 = version_release2.first;
            const std::string& release2 = version_release2.second;
            // Если версия во втором файле новее, или версии совпадают и release новее, добавляем в различия
            if (compareVersionsAndRelease(version1, version2, release1, release2)) {
                difference3["packages"].push_back(item1);
            }
        }
    }

    // Открываем и записываем JSON-файл для записи различий
    std::ofstream output_file("difference3.json");
    if (!output_file.is_open()) {
        std::cerr << "Не удалось открыть файл для записи различий." << std::endl;
        return 1;
    }

    // Записываем JSON-структуру различий в файл
    output_file << difference3.dump(4); // Запись с отступами для удобного чтения
    output_file.close();

    std::cout << "Различия успешно записаны в файл difference3.json." << std::endl;

    return 0;
}

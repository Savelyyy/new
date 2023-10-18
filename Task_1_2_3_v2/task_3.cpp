#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <unordered_set>
#include <compareVAndR.cpp>

using json = nlohmann::json;


void Task_3(const std::vector<std::string>& input_json1_arry, const std::vector<std::string>& input_json2_arry) {
    for (size_t i = 0; i < input_json1_arry.size(); ++i) {
        const std::string& json1_file = input_json1_arry[i];
        const std::string& json2_file = input_json2_arry[i];

        // Открываем и читаем JSON-файлы
        std::ifstream file1(json1_file);
        std::ifstream file2(json2_file);

        if (!file1.is_open() || !file2.is_open()) {
            std::cerr << "Ошибка при открытии JSON файлов." << std::endl;
            continue;
        }

        json json1;
        json json2;
        file1 >> json1;
        file2 >> json2;
        file1.close();
        file2.close();

        // Создаем unordered_map для хранения версий и release "name" из второго файла
        std::unordered_map<std::string, std::pair<std::string, std::string>> versions_map;

        // Проходим по элементам второго файла и сохраняем версии и release
        for (const auto& item : json2["packages"]) {
            const std::string& name = item["name"];
            const std::string& version = item["version"];
            const std::string& release = item["release"];
            versions_map[name] = std::make_pair(version, release);
        }

        // Создаем JSON-структуру для различий
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
                if (compareVAndR(version1, version2, release1, release2)) {
                    difference3["packages"].push_back(item1);
                }
            }
        }

        // Открываем и записываем JSON-файл для записи различий
        std::ofstream output_file("Task_3/" + json1_file + "_difference3.json");
        if (!output_file.is_open()) {
            std::cerr << "Не удалось открыть файл для записи различий." << std::endl;
            continue;
        }

        // Записываем JSON-структуру различий в файл
        output_file << difference3.dump(4); // Запись с отступами для удобного чтения
        output_file.close();

        std::cout << "Различия успешно записаны в файл " << json1_file + "_difference3.json." << std::endl;
    }
}


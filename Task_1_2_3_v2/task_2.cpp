#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <unordered_set>

using json = nlohmann::json;


void Task_2(const std::vector<std::string>& input_json1_arry, const std::vector<std::string>& input_json2_arry) {
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

        // Создаем unordered_set для хранения значений "name" из первого файла
        std::unordered_set<std::string> names_set;
        for (const auto& item : json1["packages"]) {
            names_set.insert(item["name"].get<std::string>());
        }

        // Создаем JSON-структуру для различий
        json difference2;

        // Проходим по элементам второго файла и сравниваем по полю "name"
        for (const auto& item2 : json2["packages"]) {
            const std::string& name = item2["name"];
            if (names_set.find(name) == names_set.end()) {
                difference2["packages"].push_back(item2);
            }
        }

        // Открываем и записываем JSON-файл для записи различий
        std::ofstream output_file2("Task_2/" +json2_file + "_difference2.json");
        if (!output_file2.is_open()) {
            std::cerr << "Не удалось открыть файл для записи различий." << std::endl;
            continue;
        }

        // Записываем JSON-структуру различий в файл
        output_file2 << difference2.dump(4); // Запись с отступами для удобного чтения
        output_file2.close();

        std::cout << "Различия успешно записаны в файл " << json2_file + "_difference2.json." << std::endl;
    }
}

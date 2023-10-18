#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <task_1.cpp>
#include <task_2.cpp>
#include <task_3.cpp>

int main() {
    // Здесь вы можете ввести URL для загрузки в командной строке
    std::string branch1;
    std::string branch2;
    std::cout << "1 branch = ";
    std::cin >> branch1;

    std::cout << "2 branch = ";
    std::cin >> branch2;

    std::vector<std::string> arch = {"x86_64", "i586", "noarch", "aarch64", "armh", "ppc64le"};

    std::string url_base = "https://rdb.altlinux.org/api/export/branch_binary_packages/";
    std::string branch_url1 = url_base + branch1 + "?arch=";
    std::string branch_url2 = url_base + branch2 + "?arch=";

    std::vector<std::string> input_json1_arry;
    std::vector<std::string> input_json2_arry;

    for (const std::string& arch_val : arch) {
        std::string url1 = branch_url1 + arch_val;
        std::string url2 = branch_url2 + arch_val;

        // Создаем команду curl
        std::string query_to_perform1 = "curl -o " + arch_val + "_" + branch1 + ".json " + url1; // -o сохраняет файл с указанным именем
        std::string query_to_perform2 = "curl -o " + arch_val + "_" + branch2 + ".json " + url2; // -o сохраняет файл с указанным именем

        // Выполняем команду curl
        int result1 = system(query_to_perform1.c_str());
        int result2 = system(query_to_perform2.c_str());

        input_json1_arry.push_back(arch_val + "_" + branch1 + ".json");
        input_json2_arry.push_back(arch_val + "_" + branch2 + ".json");


        if (result1 == 0) {
            std::cout << "Файл успешно загружен для " + branch1 + " архитектуры " << arch_val << "." << std::endl;
        } else {
            std::cout << "Файл успешно загружен для " + branch1 + " архитектуры " << arch_val << "." << std::endl;
        }

        if (result2 == 0) {
            std::cout << "Файл успешно загружен для " + branch2 + " архитектуры " << arch_val << "." << std::endl;
        } else {
            std::cout << "Файл успешно загружен для " + branch2 + " архитектуры " << arch_val << "." << std::endl;
        }
    }

    // Вызываем функцию для обработки JSON файлов
    Task_1(input_json1_arry, input_json2_arry);
    Task_2(input_json1_arry, input_json2_arry);
    Task_3(input_json1_arry, input_json2_arry);

    return 0;
}

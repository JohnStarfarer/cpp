// main.cpp, ЧЕИ
// Description: lab6, var6
#include "UnorderedList.hpp"
#include "Dictionary.hpp"
#include "Guns.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <locale>

/**
 * @brief Структура меломана и его музыкальные предпочтения
 */
struct Meloman {
    std::string name;
    UnorderedList<std::string> likedMusic;
};

/**
 * @brief Функция для выполнения задания 1 (HashSet)
 */
void task1() {
    try {
        // все музыкальные произведения
        UnorderedList<std::string> allMusic;
        allMusic.Add("LudoWic - Chemical Brew");
        allMusic.Add("Invader 303 - Greate Escape");
        allMusic.Add("The Toxic Avenger - Road Rage");
        allMusic.Add("Martha & the Vandellas - Nowhere To Run");
        allMusic.Add("Jose Pavil - World On Fire");
        allMusic.Add("Xtrullor - Precinct");
        allMusic.Add("Lothyde - Emergence");

        std::cout << "Все музыкальные произведения: ";
        allMusic.Print();
        std::cout << std::endl;

        // создаем меломанов и их предпочтения
        const int meloN = 4;
        Meloman melomans[meloN];

        melomans[0].name = "Анна";
        melomans[0].likedMusic.Add("LudoWic - Chemical Brew");
        melomans[0].likedMusic.Add("Invader 303 - Greate Escape");
        melomans[0].likedMusic.Add("The Toxic Avenger - Road Rage");

        melomans[1].name = "Борис";
        melomans[1].likedMusic.Add("LudoWic - Chemical Brew");
        melomans[1].likedMusic.Add("Martha & the Vandellas - Nowhere To Run");
        melomans[1].likedMusic.Add("The Toxic Avenger - Road Rage");

        melomans[2].name = "Виктор";
        melomans[2].likedMusic.Add("Invader 303 - Greate Escape");
        melomans[2].likedMusic.Add("The Toxic Avenger - Road Rage");
        melomans[2].likedMusic.Add("Jose Pavil - World On Fire");

        melomans[3].name = "Галина";
        melomans[3].likedMusic.Add("The Toxic Avenger - Road Rage");
        melomans[3].likedMusic.Add("Xtrullor - Precinct");

        // выводим предпочтения каждого
        for (int i = 0; i < meloN; i++) {
            std::cout << melomans[i].name << " нравятся: ";
            melomans[i].likedMusic.Print();
        }
        std::cout << std::endl;

        // произведения, которые нравятся хотя бы одному
        UnorderedList<std::string> atLeastOneLiked;
        for (int i = 0; i < meloN; i++) {
            atLeastOneLiked = atLeastOneLiked.Union(melomans[i].likedMusic);
        }

        // произведения, которые нравятся всем
        UnorderedList<std::string> allLiked = melomans[0].likedMusic;
        for (int i = 1; i < meloN; i++) {
            allLiked = allLiked.Intersect(melomans[i].likedMusic);
        }

        // произведения, которые не нравятся никому
        UnorderedList<std::string> noneLiked = allMusic.Except(atLeastOneLiked);
        
        // произведения, которые нравятся некоторым
        UnorderedList<std::string> someLiked = atLeastOneLiked.Except(allLiked);

        std::cout << "\n1. Произведения, которые нравятся ВСЕМ " << meloN << " меломанам:\n";
        if (allLiked.count() > 0) {
            allLiked.Print();
        } else {
            std::cout << "Нет таких произведений\n";
        }

        std::cout << "\n2. Произведения, которые нравятся НЕКОТОРЫМ меломанам:\n";
        if (someLiked.count() > 0) {
            someLiked.Print();
        } else {
            std::cout << "Нет таких произведений\n";
        }

        std::cout << "\n3. Произведения, которые НИКОМУ не нравятся:\n";
        if (noneLiked.count() > 0) {
            noneLiked.Print();
        } else {
            std::cout << "Нет таких произведений\n";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

/**
 * @brief Функция для выполнения задания 2 (Dictionary)
 */
void task2() {
    try {
        std::string filename = "students.txt";
        std::ifstream file(filename);
        
        Dictionary<int, SchoolStats> schoolData;
        std::vector<Student> students;
        std::string line;
        
        // чтение данных
        std::string lastName, firstName;
        int schoolNumber, score;
            
        while (file >> lastName >> firstName >> schoolNumber >> score) {
            Student student(lastName, firstName, schoolNumber, score);
            students.push_back(student);
            
            // если уже есть такая школа в словаре, то прибавляем балл к общей сумме статистики этой школы
            if (schoolData.ContainsKey(schoolNumber)) {
                SchoolStats* stats = schoolData.Get(schoolNumber);
                stats->addScore(score);
            // иначе, создаем новую структуру этой школы, добавляем балл и добавляем эту школу в словарь
            } else {
                SchoolStats stats;
                stats.addScore(score);
                schoolData.Add(schoolNumber, stats);
            }
        }
        file.close();
        
        // вычисляем общий средний балл по району
        double totalScore = 0;
        int totalStudents = 0;
        
        for (int i = 0; i < students.size(); i++) {
            totalScore += students[i].score;
            totalStudents++;
        }
        
        // средний балл
        double districtAverage;
        if (totalStudents > 0) {
            districtAverage = (double)totalScore / totalStudents;
        } else {
            districtAverage = 0;
        }

        std::cout << "Всего учеников: " << totalStudents << std::endl;
        std::cout << "Средний балл по району: " << std::fixed << std::setprecision(2) 
                  << districtAverage << std::endl;
        std::cout << "\nСтатистика по школам:\n";
        
        // школы с баллом выше среднего по району
        std::vector<int> schoolsAboveAverage;
        std::vector<double> schoolAverages;
        
        // проходимся по всем школам в словаре
        for (int i = 1; i <= 99; i++) {
            if (schoolData.ContainsKey(i)) {
                SchoolStats* stats = schoolData.Get(i);
                double schoolAvg = stats->averageScore();
                
                std::cout << "Школа №" << i << ": " << stats->studentCount 
                         << " учеников, средний балл: " << std::fixed << std::setprecision(2) 
                         << schoolAvg << std::endl;
                
                if (schoolAvg > districtAverage) {
                    schoolsAboveAverage.push_back(i);
                    schoolAverages.push_back(schoolAvg);
                }
            }
        }
        
        if (schoolsAboveAverage.empty()) {
            std::cout << "Нет школ со средним баллом выше среднего по району.\n";
        } else if (schoolsAboveAverage.size() == 1) {
            std::cout << schoolsAboveAverage[0] << std::endl;
            std::cout << "Средний балл = " << std::fixed << std::setprecision(0) 
                     << schoolAverages[0] << std::endl;
        } else {
            for (size_t i = 0; i < schoolsAboveAverage.size(); i++) {
                std::cout << schoolsAboveAverage[i];
                if (i < schoolsAboveAverage.size() - 1) {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

/**
 * @brief Функция для выполнения задания 3 (Наследование)
 */
void task3() {
    std::cout << "\nКЛАСС PISTOL ==================\\n";
    
    Pistol pistol1;
    pistol1.setModel("ПМ");
    pistol1.GetInfo();
    pistol1.Shoot();
    pistol1.GetInfo();
    pistol1.ShootMultiple(3);
    pistol1.Reload();
    pistol1.GetInfo();
    
    std::cout << "\nКЛАСС AUTOPISTOL ==================\\n";
    
    std::cout << "\na) Конструктор без параметров ==================\n";
    AutomaticPistol autoPistol1;
    autoPistol1.GetInfo();
    autoPistol1.Shoot();
    autoPistol1.GetInfo();

    std::cout << "\nb) Конструктор с вместимостью 30 ==================\\n";
    AutomaticPistol autoPistol2(60);
    autoPistol2.setModel("AK-74");
    autoPistol2.GetInfo();
    autoPistol2.Shoot();
    autoPistol2.GetInfo();
    
    std::cout << "\nc) Конструктор с вместимостью 30 и скорострельностью 10 ==================\\n";
    AutomaticPistol autoPistol3(30, 10);
    autoPistol3.setModel("M4A1");
    autoPistol3.GetInfo();
    
    std::cout << "\nСтрельба на протяжении 2 секунд ==================\\n";
    autoPistol3.Reload();
    autoPistol3.GetInfo();
    autoPistol3.ShootSeconds(2);
    autoPistol3.GetInfo();
    
    std::cout << "\nd) Доп. полный конструктор (для удобства создания) ==================\\n";
    AutomaticPistol autoPistol4(100, 25, "Minigun");
    autoPistol4.GetInfo();
    autoPistol4.ShootSeconds(1);
    autoPistol4.GetInfo();

    std::cout << "\nПОЛИМОРФИЗМА ==================\\n";
    
    Pistol* weapons[3];
    
    std::cout << "Оружие 1:\n";
    weapons[0] = new Pistol(6, "Кольт 1873");
    std::cout << "Оружие 2:\n";
    weapons[1] = new AutomaticPistol(71, 6, "ППШ");
    std::cout << "Оружие 3:\n";
    weapons[2] = new AutomaticPistol(30, 3, "MP5");
    
    for (int i = 0; i < 3; i++) {
        std::cout << "\nОружие " << i + 1 << ":\n";
        weapons[i]->GetInfo();
        weapons[i]->Shoot();
        weapons[i]->GetInfo();
        delete weapons[i];
    }
}

/**
 * @brief Меню выбора задания и вызов функций.
 * 
 * @return int Код завершения программы (0 - успешно)
 */
int main() {
    setlocale(LC_ALL, "RU");

    std::cout << "КОЛЛЕКЦИИ И НАСЛЕДОВАНИЕ" << std::endl;
    std::cout << "Задания:\n\tЗадание 1. HashSet (Музыкальные произведения);\n\tЗадание 2. Dictionary (Экзамены);\n\tЗадание 3. Наследование (Автомат);" << std::endl;
    bool userInput = true;
    while (userInput) {
        int action = 0;
        std::cout << "\nВыберите задание 1, 2, 3 (или -1 для выхода):\n > ";
        
        // проверка на корректность выбора задания
        if (!(std::cin >> action)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Ошибка: введите число!" << std::endl;
            continue;
        }
        
        if (action == -1) { 
            userInput = false; 
            break; 
        }
        
        switch (action) {
        case 1:
            std::cout << "\n# МУЗЫКАЛЬНЫЕ ПРОИЗВЕДЕНИЯ\n";
            task1();
            break;
            
        case 2:
            std::cout << "\n# СЛОВАРЬ (ЭКЗАМЕНЫ)\n";
            task2();
            break;
            
        case 3:
            std::cout << "\n# НАСЛЕДОВАНИЕ (АВТОМАТ)\n";
            task3();
            break;
            
        default:
            std::cout << "Такого задания нет!" << std::endl;
            break;
        }
    }
    
    return 0;
}
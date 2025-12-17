// main.cpp, ЧЕИ
// Description: lab6, var6

#include "UnorderedList.hpp"
#include <iostream>

struct Meloman {
    std::string name;
    UnorderedList<std::string> likedMusic;
};

void task1() {
    try {
        // Список всех музыкальных произведений
        UnorderedList<std::string> allMusic;
        allMusic.Add("Бетховен - Симфония №5");
        allMusic.Add("Моцарт - Реквием");
        allMusic.Add("Чайковский - Лебединое озеро");
        allMusic.Add("Вивальди - Времена года");
        allMusic.Add("Бах - Токката и фуга ре минор");
        allMusic.Add("Шопен - Ноктюрн №20");
        allMusic.Add("Рахманинов - Концерт №2");

        std::cout << "Все музыкальные произведения: ";
        allMusic.Print();
        std::cout << std::endl;

        // Создаем меломанов с их предпочтениями
        const int n = 4;
        Meloman melomans[n];

        melomans[0].name = "Анна";
        melomans[0].likedMusic.Add("Бетховен - Симфония №5");
        melomans[0].likedMusic.Add("Моцарт - Реквием");
        melomans[0].likedMusic.Add("Чайковский - Лебединое озеро");

        melomans[1].name = "Борис";
        melomans[1].likedMusic.Add("Бетховен - Симфония №5");
        melomans[1].likedMusic.Add("Вивальди - Времена года");
        melomans[1].likedMusic.Add("Чайковский - Лебединое озеро");

        melomans[2].name = "Виктор";
        melomans[2].likedMusic.Add("Моцарт - Реквием");
        melomans[2].likedMusic.Add("Чайковский - Лебединое озеро");
        melomans[2].likedMusic.Add("Бах - Токката и фуга ре минор");

        melomans[3].name = "Галина";
        melomans[3].likedMusic.Add("Чайковский - Лебединое озеро");
        melomans[3].likedMusic.Add("Шопен - Ноктюрн №20");

        // Выводим предпочтения каждого меломана
        for (int i = 0; i < n; i++) {
            std::cout << melomans[i].name << " нравятся: ";
            melomans[i].likedMusic.Print();
        }
        std::cout << std::endl;

        // Вычисляем произведения, которые нравятся хотя бы одному меломану
        UnorderedList<std::string> atLeastOneLiked;
        for (int i = 0; i < n; i++) {
            atLeastOneLiked = atLeastOneLiked.Union(melomans[i].likedMusic);
        }

        // Вычисляем произведения, которые нравятся всем меломанам
        UnorderedList<std::string> allLiked = melomans[0].likedMusic;
        for (int i = 1; i < n; i++) {
            allLiked = allLiked.Intersect(melomans[i].likedMusic);
        }

        // Вычисляем произведения, которые не нравятся никому
        UnorderedList<std::string> noneLiked = allMusic.Except(atLeastOneLiked);
        
        // Вычисляем произведения, которые нравятся некоторым (но не всем)
        UnorderedList<std::string> someLiked = atLeastOneLiked.Except(allLiked);

        std::cout << "=== РЕЗУЛЬТАТЫ ===\n";

        std::cout << "\n1. Произведения, которые нравятся ВСЕМ " << n << " меломанам:\n";
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

int main() {
    setlocale(LC_ALL, "Rus");
    
    bool flag = true;
    while (flag) {
        int action = 0;
        std::cout << "\n==============================" << std::endl;
        std::cout << "Выберите задание (1, 2, 3) или -1 для выхода: ";
        std::cin >> action;
        
        if (action == -1) { 
            flag = false; 
            break; 
        }
        
        switch (action) {
        case 1:
            std::cout << "\n=== ЗАДАНИЕ 1: МУЗЫКАЛЬНЫЕ ПРОИЗВЕДЕНИЯ ===\n";
            task1();
            break;
            
        case 2:
            std::cout << "\n=== ЗАДАНИЕ 2: СЛОВАРЬ ===\n";
            break;
            
        case 3:
            std::cout << "\n=== ЗАДАНИЕ 3: НАСЛЕДОВАНИЕ ===\n";
            break;
            
        default:
            std::cout << "Такого задания нет" << std::endl;
            break;
        }
    }
    
    return 0;
}
// Guns.hpp, ЧЕИ
// Description: lab6, var6
#ifndef GUNS_HPP
#define GUNS_HPP

#include <iostream>
#include <string>

/**
 * @class Pistol
 * @brief Базовый класс, представляющий пистолет
 * 
 * Класс реализует базовый функционал пистолета: стрельбу, перезарядку,
 * получение информации о состоянии.
 */
class Pistol {
protected:
    int magazineCapacity;
    int bullets;
    std::string model;
    
public:
    // конструктор по умолчанию
    Pistol() : magazineCapacity(10), bullets(10), model("Пистолет") {
        std::cout << "Создан пистолет с ёмкостью: " << magazineCapacity << std::endl;
    }
    
    // конструктор с параметром
    Pistol(int capacity) : magazineCapacity(capacity), bullets(capacity), model("Пистолет") {
        std::cout << "Создан пистолет с ёмкостью: " << magazineCapacity << std::endl;
    }
    
    // конструктор с полными параметрами
    Pistol(int capacity, const std::string& modelName) : magazineCapacity(capacity), bullets(capacity), model(modelName) {
        std::cout << "Создан пистолет '" << model << "' с ёмкостью: " << magazineCapacity << std::endl;
    }
    
    // деструктор
    virtual ~Pistol() {
        std::cout << "Пистолет " << model << " разобран" << std::endl;
    }
    
    // один выстрел
    virtual void Shoot() {
        if (bullets > 0) {
            std::cout << model << ": Бам!" << std::endl;
            bullets--;
        } else {
            std::cout << model << ": Клик! (закончились патроны)" << std::endl;
        }
    }
    
    void ShootMultiple(int times) {
        std::cout << "Стреляем " << times << " раз:" << std::endl;
        for (int i = 0; i < times && bullets > 0; i++) {
            Shoot();
        }
    }
    
    void Reload() {
        bullets = magazineCapacity;
        std::cout << model << ": Перезарядка. Патронов: " << bullets << std::endl;
    }
    
    virtual void GetInfo() const {
        std::cout << "Модель пистолета: " << model 
                  << " | Ёмкость: " << magazineCapacity 
                  << " | Патронов: " << bullets << std::endl;
    }
    
    int getBullets() const { return bullets; }
    int getCapacity() const { return magazineCapacity; }
    std::string getModel() const { return model; }
    
    void setModel(const std::string& newModel) { model = newModel; }
};

/**
 * @class AutomaticPistol
 * @brief Производный класс, представляющий автомат
 * 
 * Наследуется от класса Pistol. Добавляет функционал скорострельности
 * и возможность стрельбы в течение нескольких секунд.
 */
class AutomaticPistol : public Pistol {
public:
    // a) конструктор без параметров
    AutomaticPistol() : Pistol(30, "Автомат"), fireRate(30) {
        std::cout << "Создан автомат со скорострельностью: " << fireRate << std::endl;
    }
    
    // b) конструктор максимального числа патронов
    AutomaticPistol(int maxBullets) : Pistol(maxBullets, "Автомат"), fireRate(maxBullets / 2) {
        std::cout << "Создан автомат со скорострельностью: " << fireRate << std::endl;
    }
    
    // c) конструктор с вместимостью и скорострельностью
    AutomaticPistol(int capacity, int rate) : Pistol(capacity, "Автомат"), fireRate(rate) {
        if (fireRate <= 0) {
            fireRate = 1;
        }
        std::cout << "Создан автомат со скорострельностью: " << fireRate << std::endl;
    }
    
    // d) доп конструктор с полными параметрами
    AutomaticPistol(int capacity, int rate, const std::string& modelName) : Pistol(capacity, modelName), fireRate(rate) {
        if (fireRate <= 0) {
            fireRate = 1;
        }
        std::cout << "Создан автомат '" << model << "' со скорострельностью: " << fireRate << std::endl;
    }

    // один выстрел
    void Shoot() override {
        if (bullets <= 0) {
            std::cout << model << ": Клик! (закончились патроны)" << std::endl;
            return;
        }
        
        int shots = std::min(fireRate, bullets);
        std::cout << model << ": Стреляем " << shots << " раз:" << std::endl;
        
        for (int i = 0; i < shots; i++) {
            std::cout << "Туф!" << std::endl;
        }
        
        bullets -= shots;
    }
    
    // стрельбы N секунд
    void ShootSeconds(int seconds) {
        if (seconds <= 0) {
            std::cout << "Время должно быть больше нуля!" << std::endl;
            return;
        }
        
        int totalShots = seconds * fireRate;
        std::cout << model << ": Стреляем " << seconds << " секунд (всего " << totalShots << " раз)..." << std::endl;
        
        for (int i = 0; i < totalShots && bullets > 0; i++) {
            if (bullets > 0) {
                std::cout << "Та!" << std::endl;
                bullets--;
            }
        }
        
        if (bullets == 0) {
            std::cout << model << ": Клик! (закончились патроны)" << std::endl;
        }
    }
    
    void GetInfo() const override {
        std::cout << "Модель автомата: " << model 
                  << " | Ёмкость: " << magazineCapacity 
                  << " | Патронов: " << bullets 
                  << " | Скорострельность: " << fireRate << "/сек" << std::endl;
    }
    
    int getFireRate() const { return fireRate; }
    
    void setFireRate(int rate) {
        if (rate > 0) {
            fireRate = rate;
        }
    }

private:
    int fireRate;  // выстрелов в секунду
};

#endif
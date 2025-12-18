// Guns.hpp, ЧЕИ
// Description: lab6, var6
#ifndef GUNS_HPP
#define GUNS_HPP

#include <iostream>
#include <string>

/// <summary>
/// Базовый класс, представляющий пистолет.
/// </summary>
/// <remarks>
/// Класс реализует базовый функционал пистолета: стрельбу, перезарядку,
/// получение информации о состоянии.
/// </remarks>
class Pistol {
protected:
    int magazineCapacity;
    int bullets;
    std::string model;
    
public:
    /// <summary>
    /// Инициализирует новый экземпляр класса <see cref="Pistol"/> с вместимостью 10 патронов.
    /// </summary>
    Pistol() : magazineCapacity(10), bullets(10), model("Пистолет") {
        std::cout << "Создан пистолет с ёмкостью: " << magazineCapacity << std::endl;
    }
    
    /// <summary>
    /// Инициализирует новый экземпляр класса <see cref="Pistol"/> с указанной вместимостью.
    /// </summary>
    /// <param name="capacity">Вместимость магазина.</param>
    Pistol(int capacity) : magazineCapacity(capacity), bullets(capacity), model("Пистолет") {
        std::cout << "Создан пистолет с ёмкостью: " << magazineCapacity << std::endl;
    }
    
    /// <summary>
    /// Инициализирует новый экземпляр класса <see cref="Pistol"/> с указанной вместимостью и названием модели.
    /// </summary>
    /// <param name="capacity">Вместимость магазина.</param>
    /// <param name="modelName">Название модели.</param>
    Pistol(int capacity, const std::string& modelName) : magazineCapacity(capacity), bullets(capacity), model(modelName) {
        std::cout << "Создан пистолет '" << model << "' с ёмкостью: " << magazineCapacity << std::endl;
    }
    
    /// <summary>
    /// Освобождает все ресурсы, используемые классом <see cref="Pistol"/>.
    /// </summary>
    virtual ~Pistol() {
        std::cout << "Пистолет " << model << " разобран" << std::endl;
    }
    
    /// <summary>
    /// Совершает один выстрел.
    /// </summary>
    /// <remarks>
    /// Если патроны есть, уменьшает их количество на 1.
    /// </remarks>
    virtual void Shoot() {
        if (bullets > 0) {
            std::cout << model << ": Бам!" << std::endl;
            bullets--;
        } else {
            std::cout << model << ": Клик! (закончились патроны)" << std::endl;
        }
    }
    
    /// <summary>
    /// Совершает несколько выстрелов.
    /// </summary>
    /// <param name="times">Количество выстрелов.</param>
    void ShootMultiple(int times) {
        std::cout << "Стреляем " << times << " раз:" << std::endl;
        for (int i = 0; i < times && bullets > 0; i++) {
            Shoot();
        }
    }
    
    /// <summary>
    /// Перезаряжает пистолет.
    /// </summary>
    /// <remarks>
    /// Восстанавливает количество патронов до максимальной вместимости.
    /// </remarks>
    void Reload() {
        bullets = magazineCapacity;
        std::cout << model << ": Перезарядка. Патронов: " << bullets << std::endl;
    }
    
    /// <summary>
    /// Выводит информацию о пистолете.
    /// </summary>
    virtual void GetInfo() const {
        std::cout << "Модель пистолета: " << model 
                  << " | Ёмкость: " << magazineCapacity 
                  << " | Патронов: " << bullets << std::endl;
    }
    
    /// <summary>
    /// Возвращает текущее количество патронов.
    /// </summary>
    /// <returns>Количество патронов.</returns>
    int getBullets() const { return bullets; }
    
    /// <summary>
    /// Возвращает вместимость магазина.
    /// </summary>
    /// <returns>Вместимость магазина.</returns>
    int getCapacity() const { return magazineCapacity; }
    
    /// <summary>
    /// Возвращает модель пистолета.
    /// </summary>
    /// <returns>Название модели.</returns>
    std::string getModel() const { return model; }
    
    /// <summary>
    /// Устанавливает модель пистолета.
    /// </summary>
    /// <param name="newModel">Новое название модели.</param>
    void setModel(const std::string& newModel) { model = newModel; }
};

/// <summary>
/// Производный класс, представляющий автомат.
/// </summary>
/// <remarks>
/// Наследуется от класса Pistol. Добавляет функционал скорострельности
/// и возможность стрельбы в течение нескольких секунд.
/// </remarks>
class AutomaticPistol : public Pistol {
public:
    /// <summary>
    /// Инициализирует новый экземпляр класса <see cref="AutomaticPistol"/> с вместимостью 30 и скорострельностью 30.
    /// </summary>
    AutomaticPistol() : Pistol(30, "Автомат"), fireRate(30) {
        std::cout << "Создан автомат со скорострельностью: " << fireRate << std::endl;
    }
    
    /// <summary>
    /// Инициализирует новый экземпляр класса <see cref="AutomaticPistol"/> с указанной вместимостью.
    /// </summary>
    /// <param name="maxBullets">Вместимость магазина.</param>
    /// <remarks>
    /// Скорострельность устанавливается равной половине вместимости.
    /// </remarks>
    AutomaticPistol(int maxBullets) : Pistol(maxBullets, "Автомат"), fireRate(maxBullets / 2) {
        std::cout << "Создан автомат со скорострельностью: " << fireRate << std::endl;
    }
    
    /// <summary>
    /// Инициализирует новый экземпляр класса <see cref="AutomaticPistol"/> с указанной вместимостью и скорострельностью.
    /// </summary>
    /// <param name="capacity">Вместимость магазина.</param>
    /// <param name="rate">Скорострельность (выстрелов в секунду).</param>
    AutomaticPistol(int capacity, int rate) : Pistol(capacity, "Автомат"), fireRate(rate) {
        if (fireRate <= 0) {
            fireRate = 1;
        }
        std::cout << "Создан автомат со скорострельностью: " << fireRate << std::endl;
    }
    
    /// <summary>
    /// Инициализирует новый экземпляр класса <see cref="AutomaticPistol"/> с указанными характеристиками.
    /// </summary>
    /// <param name="capacity">Вместимость магазина.</param>
    /// <param name="rate">Скорострельность (выстрелов в секунду).</param>
    /// <param name="modelName">Название модели.</param>
    AutomaticPistol(int capacity, int rate, const std::string& modelName) : Pistol(capacity, modelName), fireRate(rate) {
        if (fireRate <= 0) {
            fireRate = 1;
        }
        std::cout << "Создан автомат '" << model << "' со скорострельностью: " << fireRate << std::endl;
    }

    /// <summary>
    /// Совершает выстрел с учетом скорострельности.
    /// </summary>
    /// <remarks>
    /// Совершает количество выстрелов, равное текущей скорострельности,
    /// но не более доступного количества патронов.
    /// </remarks>
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
    
    /// <summary>
    /// Стреляет в течение указанного времени.
    /// </summary>
    /// <param name="seconds">Время стрельбы в секундах.</param>
    /// <remarks>
    /// Совершает количество выстрелов, равное произведению времени на скорострельность.
    /// </remarks>
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
    
    /// <summary>
    /// Выводит информацию об автомате.
    /// </summary>
    /// <remarks>
    /// Добавляет информацию о скорострельности.
    /// </remarks>
    void GetInfo() const override {
        std::cout << "Модель автомата: " << model 
                  << " | Ёмкость: " << magazineCapacity 
                  << " | Патронов: " << bullets 
                  << " | Скорострельность: " << fireRate << "/сек" << std::endl;
    }
    
    /// <summary>
    /// Возвращает текущую скорострельность.
    /// </summary>
    /// <returns>Скорострельность (выстрелов в секунду).</returns>
    int getFireRate() const { return fireRate; }
    
    /// <summary>
    /// Устанавливает скорострельность.
    /// </summary>
    /// <param name="rate">Новая скорострельность.</param>
    /// <remarks>
    /// Скорострельность должна быть положительной.
    /// </remarks>
    void setFireRate(int rate) {
        if (rate > 0) {
            fireRate = rate;
        }
    }

private:
    int fireRate;
};

#endif
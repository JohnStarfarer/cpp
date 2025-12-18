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
    Pistol();
    
    /// <summary>
    /// Инициализирует новый экземпляр класса <see cref="Pistol"/> с указанной вместимостью.
    /// </summary>
    /// <param name="capacity">Вместимость магазина.</param>
    Pistol(int capacity);
    
    /// <summary>
    /// Инициализирует новый экземпляр класса <see cref="Pistol"/> с указанной вместимостью и названием модели.
    /// </summary>
    /// <param name="capacity">Вместимость магазина.</param>
    /// <param name="modelName">Название модели.</param>
    Pistol(int capacity, const std::string& modelName);
    
    /// <summary>
    /// Освобождает все ресурсы, используемые классом <see cref="Pistol"/>.
    /// </summary>
    virtual ~Pistol();
    
    /// <summary>
    /// Совершает один выстрел.
    /// </summary>
    /// <remarks>
    /// Если патроны есть, уменьшает их количество на 1.
    /// </remarks>
    virtual void Shoot();
    
    /// <summary>
    /// Совершает несколько выстрелов.
    /// </summary>
    /// <param name="times">Количество выстрелов.</param>
    void ShootMultiple(int times);
    
    /// <summary>
    /// Перезаряжает пистолет.
    /// </summary>
    /// <remarks>
    /// Восстанавливает количество патронов до максимальной вместимости.
    /// </remarks>
    void Reload();
    
    /// <summary>
    /// Выводит информацию о пистолете.
    /// </summary>
    virtual void GetInfo() const;
    
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
    AutomaticPistol();
    
    /// <summary>
    /// Инициализирует новый экземпляр класса <see cref="AutomaticPistol"/> с указанной вместимостью.
    /// </summary>
    /// <param name="maxBullets">Вместимость магазина.</param>
    /// <remarks>
    /// Скорострельность устанавливается равной половине вместимости.
    /// </remarks>
    AutomaticPistol(int maxBullets);
    
    /// <summary>
    /// Инициализирует новый экземпляр класса <see cref="AutomaticPistol"/> с указанной вместимостью и скорострельностью.
    /// </summary>
    /// <param name="capacity">Вместимость магазина.</param>
    /// <param name="rate">Скорострельность (выстрелов в секунду).</param>
    AutomaticPistol(int capacity, int rate);
    
    /// <summary>
    /// Инициализирует новый экземпляр класса <see cref="AutomaticPistol"/> с указанными характеристиками.
    /// </summary>
    /// <param name="capacity">Вместимость магазина.</param>
    /// <param name="rate">Скорострельность (выстрелов в секунду).</param>
    /// <param name="modelName">Название модели.</param>
    AutomaticPistol(int capacity, int rate, const std::string& modelName);

    /// <summary>
    /// Совершает выстрел с учетом скорострельности.
    /// </summary>
    /// <remarks>
    /// Совершает количество выстрелов, равное текущей скорострельности,
    /// но не более доступного количества патронов.
    /// </remarks>
    void Shoot() override;
    
    /// <summary>
    /// Стреляет в течение указанного времени.
    /// </summary>
    /// <param name="seconds">Время стрельбы в секундах.</param>
    /// <remarks>
    /// Совершает количество выстрелов, равное произведению времени на скорострельность.
    /// </remarks>
    void ShootSeconds(int seconds);
    
    /// <summary>
    /// Выводит информацию об автомате.
    /// </summary>
    /// <remarks>
    /// Добавляет информацию о скорострельности.
    /// </remarks>
    void GetInfo() const override;
    
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
    void setFireRate(int rate);

private:
    int fireRate;
};

#endif
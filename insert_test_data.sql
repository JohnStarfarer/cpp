-- ========================================================
-- Заполнение тестовыми данными
-- ========================================================

-- Типы вагонов
INSERT INTO wagon_types (name, capacity, description) VALUES
('Плацкарт', 54, 'Открытые купе'),
('Купе', 36, 'Закрытые купе'),
('СВ', 18, 'Спальный вагон'),
('Люкс', 8, 'Вагон люкс');

-- Поезда
INSERT INTO trains (name, status, total_seats) VALUES
('Сапсан-001', 'active', 600),
('Ласточка-101', 'active', 450),
('Стриж-201', 'maintenance', 550),
('Красная стрела', 'active', 580);

-- Маршруты
INSERT INTO routes (departure_city, arrival_city, distance_km, base_price, status) VALUES
('Москва', 'Санкт-Петербург', 650, 2500.00, 'active'),
('Санкт-Петербург', 'Москва', 650, 2500.00, 'active'),
('Москва', 'Нижний Новгород', 420, 1800.00, 'active'),
('Москва', 'Сочи', 1620, 4500.00, 'active'),
('Казань', 'Москва', 820, 3200.00, 'active');

-- Пассажиры
INSERT INTO passengers (last_name, first_name, middle_name, birth_date, gender, document_type, document_number, phone, email) VALUES
('Иванов', 'Иван', 'Иванович', '1985-05-15', 'М', 'паспорт', '4510123456', '+79161234567', 'ivanov@mail.ru'),
('Петрова', 'Мария', 'Сергеевна', '1990-08-22', 'Ж', 'паспорт', '4511123456', '+79162345678', 'petrova@gmail.com'),
('Сидоров', 'Алексей', NULL, '1978-12-03', 'М', 'паспорт', '4512123456', '+79163456789', 'sidorov@yandex.ru'),
('Козлова', 'Елена', 'Владимировна', '1995-03-18', 'Ж', 'паспорт', '4513123456', '+79164567890', 'kozlova@mail.ru');

-- Расписание
INSERT INTO schedule (route_id, train_id, wagon_type_id, departure_date, departure_time, arrival_date, arrival_time, available_seats, price, status) VALUES
(1, 1, 1, '2024-12-20', '08:00:00', '2024-12-20', '12:30:00', 50, 2800.00, 'scheduled'),
(1, 1, 2, '2024-12-20', '08:00:00', '2024-12-20', '12:30:00', 30, 3800.00, 'scheduled'),
(2, 2, 1, '2024-12-21', '10:00:00', '2024-12-21', '14:45:00', 40, 1800.00, 'scheduled'),
(4, 1, 3, '2024-12-23', '22:00:00', '2024-12-24', '14:00:00', 15, 5200.00, 'scheduled');

-- Билеты
INSERT INTO tickets (schedule_id, passenger_id, wagon_number, seat_number, price, status) VALUES
(1, 1, 1, 10, 2800.00, 'active'),
(1, 2, 1, 11, 2800.00, 'active'),
(2, 3, 2, 5, 3800.00, 'active'),
(3, 4, 1, 20, 1800.00, 'cancelled');

-- ========================================================
-- Вывод информации о созданных данных
-- ========================================================

SELECT 'Типы вагонов: ' || COUNT(*) FROM wagon_types
UNION ALL
SELECT 'Поезда: ' || COUNT(*) FROM trains
UNION ALL
SELECT 'Маршруты: ' || COUNT(*) FROM routes
UNION ALL
SELECT 'Пассажиры: ' || COUNT(*) FROM passengers
UNION ALL
SELECT 'Рейсы в расписании: ' || COUNT(*) FROM schedule
UNION ALL
SELECT 'Билеты: ' || COUNT(*) FROM tickets
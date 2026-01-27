-- Таблица поездов
CREATE TABLE IF NOT EXISTS trains (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL UNIQUE,
    status VARCHAR(20) DEFAULT 'active',
    total_seats INTEGER NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Таблица типов вагонов
CREATE TABLE IF NOT EXISTS wagon_types (
    id SERIAL PRIMARY KEY,
    name VARCHAR(50) NOT NULL UNIQUE,
    capacity INTEGER NOT NULL,
    description TEXT
);

-- Таблица маршрутов
CREATE TABLE IF NOT EXISTS routes (
    id SERIAL PRIMARY KEY,
    departure_city VARCHAR(100) NOT NULL,
    arrival_city VARCHAR(100) NOT NULL,
    distance_km INTEGER,
    base_price DECIMAL(10,2) NOT NULL,
    status VARCHAR(20) DEFAULT 'active',
    UNIQUE(departure_city, arrival_city)
);

-- Таблица пассажиров
CREATE TABLE IF NOT EXISTS passengers (
    id SERIAL PRIMARY KEY,
    last_name VARCHAR(100) NOT NULL,
    first_name VARCHAR(100) NOT NULL,
    middle_name VARCHAR(100),
    birth_date DATE NOT NULL,
    gender CHAR(1) CHECK (gender IN ('М', 'Ж')),
    document_type VARCHAR(50) NOT NULL,
    document_number VARCHAR(50) NOT NULL UNIQUE,
    phone VARCHAR(20),
    email VARCHAR(100),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Таблица расписания рейсов
CREATE TABLE IF NOT EXISTS schedule (
    id SERIAL PRIMARY KEY,
    route_id INTEGER REFERENCES routes(id) ON DELETE CASCADE,
    train_id INTEGER REFERENCES trains(id) ON DELETE CASCADE,
    wagon_type_id INTEGER REFERENCES wagon_types(id) ON DELETE CASCADE,
    departure_date DATE NOT NULL,
    departure_time TIME NOT NULL,
    arrival_date DATE NOT NULL,
    arrival_time TIME NOT NULL,
    available_seats INTEGER NOT NULL,
    price DECIMAL(10,2) NOT NULL,
    status VARCHAR(20) DEFAULT 'scheduled'
);

-- Таблица билетов
CREATE TABLE IF NOT EXISTS tickets (
    id SERIAL PRIMARY KEY,
    ticket_number VARCHAR(50) UNIQUE DEFAULT NULL,
    schedule_id INTEGER REFERENCES schedule(id) ON DELETE CASCADE,
    passenger_id INTEGER REFERENCES passengers(id) ON DELETE CASCADE,
    wagon_number INTEGER NOT NULL,
    seat_number INTEGER NOT NULL,
    purchase_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    price DECIMAL(10,2) NOT NULL,
    status VARCHAR(20) DEFAULT 'active',
    UNIQUE(schedule_id, wagon_number, seat_number)
);

-- Индексы для ускорения запросов

CREATE INDEX idx_schedule_dates ON schedule(departure_date, arrival_date);
CREATE INDEX idx_tickets_schedule ON tickets(schedule_id);
CREATE INDEX idx_tickets_passenger ON tickets(passenger_id);
CREATE INDEX idx_passengers_document ON passengers(document_number);
CREATE INDEX idx_tickets_number ON tickets(ticket_number);
CREATE INDEX idx_schedule_route_train ON schedule(route_id, train_id);

-- Функция для генерации номера билета

CREATE OR REPLACE FUNCTION generate_ticket_number()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.ticket_number IS NULL THEN
        NEW.ticket_number := 'TK-' || 
                            TO_CHAR(NEW.purchase_date, 'YYYYMMDD') || '-' || 
                            LPAD(NEW.id::text, 6, '0');
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER set_ticket_number
BEFORE INSERT ON tickets
FOR EACH ROW
EXECUTE FUNCTION generate_ticket_number();

-- Функция для обновления доступных мест

CREATE OR REPLACE FUNCTION update_available_seats()
RETURNS TRIGGER AS $$
BEGIN
    IF TG_OP = 'INSERT' AND NEW.status = 'active' THEN
        UPDATE schedule 
        SET available_seats = available_seats - 1
        WHERE id = NEW.schedule_id;
    ELSIF TG_OP = 'UPDATE' THEN
        -- Если статус меняется с active на cancelled
        IF OLD.status = 'active' AND NEW.status = 'cancelled' THEN
            UPDATE schedule 
            SET available_seats = available_seats + 1
            WHERE id = NEW.schedule_id;
        -- Если статус меняется с cancelled на active
        ELSIF OLD.status = 'cancelled' AND NEW.status = 'active' THEN
            UPDATE schedule 
            SET available_seats = available_seats - 1
            WHERE id = NEW.schedule_id;
        END IF;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER update_seats_on_ticket
AFTER INSERT OR UPDATE ON tickets
FOR EACH ROW
EXECUTE FUNCTION update_available_seats();

-- Представления для удобства

-- Представление для полного расписания
CREATE OR REPLACE VIEW v_full_schedule AS
SELECT 
    s.id,
    r.departure_city || ' - ' || r.arrival_city AS route,
    t.name AS train,
    wt.name AS wagon_type,
    s.departure_date,
    s.departure_time,
    s.arrival_date,
    s.arrival_time,
    s.available_seats,
    s.price,
    s.status
FROM schedule s
JOIN routes r ON s.route_id = r.id
JOIN trains t ON s.train_id = t.id
JOIN wagon_types wt ON s.wagon_type_id = wt.id;

-- Представление для билетов с деталями
CREATE OR REPLACE VIEW v_ticket_details AS
SELECT 
    tk.id,
    tk.ticket_number,
    p.last_name || ' ' || p.first_name || COALESCE(' ' || p.middle_name, '') AS passenger_name,
    fs.route,
    fs.train,
    fs.wagon_type,
    tk.wagon_number,
    tk.seat_number,
    tk.price,
    tk.status AS ticket_status,
    tk.purchase_date
FROM tickets tk
JOIN passengers p ON tk.passenger_id = p.id
JOIN v_full_schedule fs ON tk.schedule_id = fs.id;

-- Представление для статистики
CREATE OR REPLACE VIEW v_simple_stats AS
SELECT 
    r.departure_city || ' - ' || r.arrival_city AS route,
    COUNT(tk.id) AS tickets_sold,
    SUM(tk.price) AS total_revenue,
    AVG(tk.price) AS avg_price
FROM tickets tk
JOIN schedule s ON tk.schedule_id = s.id
JOIN routes r ON s.route_id = r.id
WHERE tk.status = 'active'
GROUP BY r.departure_city, r.arrival_city;
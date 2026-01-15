DROP TABLE IF EXISTS order_items CASCADE;
DROP TABLE IF EXISTS products CASCADE;
DROP TABLE IF EXISTS couriers CASCADE;

CREATE TABLE couriers (
    courier_id SERIAL PRIMARY KEY,
    last_name VARCHAR(50) NOT NULL,
    first_name VARCHAR(50) NOT NULL,
    patronymic VARCHAR(50),
    phone VARCHAR(20) UNIQUE NOT NULL,
    vehicle_type VARCHAR(50),
    vehicle_plate VARCHAR(20),
    is_active BOOLEAN DEFAULT TRUE,
    registration_date DATE DEFAULT CURRENT_DATE,
    
    CONSTRAINT valid_phone CHECK (phone ~ '^\+7\d{10}$'),
    CONSTRAINT valid_plate CHECK (
        vehicle_plate IS NULL OR 
        vehicle_plate ~ '^[А-ЯA-Z]\d{3}[А-ЯA-Z]{2}\d{2,3}$'
    )
);

CREATE TABLE products (
    product_id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    description TEXT,
    sku VARCHAR(50) UNIQUE,
    quantity INTEGER NOT NULL DEFAULT 0,
    unit VARCHAR(20) DEFAULT 'шт.',
    location VARCHAR(50),
    reorder_level INTEGER DEFAULT 5,
    price DECIMAL(10, 2) DEFAULT 0.00,
    
    CONSTRAINT positive_quantity CHECK (quantity >= 0),
    CONSTRAINT positive_reorder CHECK (reorder_level >= 0),
    CONSTRAINT positive_price CHECK (price >= 0)
);

CREATE TABLE order_items (
    order_id SERIAL PRIMARY KEY,
    customer_name VARCHAR(100) NOT NULL,
    customer_phone VARCHAR(20) NOT NULL,
    customer_address TEXT NOT NULL,
    product_id INTEGER NOT NULL REFERENCES products(product_id) ON DELETE RESTRICT,
    quantity INTEGER NOT NULL CHECK (quantity > 0),
    price DECIMAL(10, 2) NOT NULL,
    status VARCHAR(30) NOT NULL DEFAULT 'новый',
    assigned_courier_id INTEGER REFERENCES couriers(courier_id) ON DELETE SET NULL,
    total_cost DECIMAL(10, 2) DEFAULT 0.00,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    dispatch_time TIMESTAMP,
    delivery_notes TEXT,
    
    CONSTRAINT valid_customer_phone CHECK (customer_phone ~ '^\+7\d{10}$'),
    CONSTRAINT valid_status CHECK (
        status IN ('новый', 'в обработке', 'собирается', 'готов к отправке', 
                  'в пути', 'доставлен', 'отменен')
    )
);

CREATE OR REPLACE FUNCTION update_updated_at_column()
RETURNS TRIGGER AS $$
BEGIN
    NEW.updated_at = CURRENT_TIMESTAMP;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER update_order_items_updated_at 
    BEFORE UPDATE ON order_items 
    FOR EACH ROW 
    EXECUTE FUNCTION update_updated_at_column();

CREATE OR REPLACE FUNCTION update_order_total_cost()
RETURNS TRIGGER AS $$
BEGIN
    NEW.total_cost = NEW.quantity * NEW.price;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER update_order_total_before_insert_update
    BEFORE INSERT OR UPDATE ON order_items
    FOR EACH ROW
    EXECUTE FUNCTION update_order_total_cost();

DO $$ 
BEGIN
    IF NOT EXISTS (SELECT FROM pg_catalog.pg_user WHERE usename = 'courier_user') THEN
        CREATE USER courier_user WITH PASSWORD 'password123';
    END IF;
END $$;

GRANT SELECT, INSERT, UPDATE, DELETE ON TABLE 
    couriers, products, order_items 
TO courier_user;

GRANT USAGE, SELECT ON ALL SEQUENCES IN SCHEMA public TO courier_user;

-- ТЕСТОВЫЕ ДАННЫЕ
INSERT INTO couriers (last_name, first_name, patronymic, phone, vehicle_type, vehicle_plate) VALUES
('Иванов', 'Иван', 'Иванович', '+79161234567', 'Автомобиль', 'А123ВС77'),
('Петрова', 'Мария', NULL, '+79167654321', 'Велосипед', NULL),
('Сидоров', 'Алексей', 'Петрович', '+79169876543', 'Мотоцикл', 'В456ОР99'),
('Кузнецова', 'Анна', 'Сергеевна', '+79161112233', 'Пеший', NULL);

INSERT INTO products (name, description, sku, quantity, unit, location, price) VALUES
('Смартфон XYZ Pro', 'Флагманский смартфон с 256 ГБ памяти', 'SM-XYZ-256', 15, 'шт.', 'Стеллаж A-12', 89999.99),
('Ноутбук Gamer Plus', 'Игровой ноутбук с RTX 4070', 'NT-GAMER-4070', 8, 'шт.', 'Стеллаж B-05', 129999.99),
('Наушники Wireless Pro', 'Беспроводные наушники с шумоподавлением', 'HP-WLP-2024', 25, 'шт.', 'Ящик C-03', 14999.50),
('Монитор 27" 4K', 'Монитор с разрешением 4K и частотой 144 Гц', 'MON-27-4K', 12, 'шт.', 'Стеллаж D-07', 45999.00),
('Клавиатура Mechanical', 'Механическая клавиатура с RGB подсветкой', 'KB-MECH-RGB', 30, 'шт.', 'Ящик E-12', 7999.99);

INSERT INTO order_items (customer_name, customer_phone, customer_address, product_id, quantity, price, status) VALUES
('Смирнов Олег Викторович', '+79165554433', 'ул. Ленина, д. 10, кв. 25', 1, 1, 89999.99, 'новый'),
('Ковалева Елена Дмитриевна', '+79167778899', 'пр. Победы, д. 45, кв. 12', 2, 1, 129999.99, 'в обработке'),
('Николаев Денис Игоревич', '+79168889900', 'ул. Садовая, д. 33, кв. 7', 5, 2, 7999.99, 'собирается');

-- функция для получения статистики по курьеру
CREATE OR REPLACE FUNCTION get_courier_stats(courier_id_param INTEGER)
RETURNS TABLE(
    total_deliveries BIGINT,
    completed_deliveries BIGINT,
    pending_deliveries BIGINT,
    avg_delivery_time INTERVAL
) AS $$
BEGIN
    RETURN QUERY
    SELECT 
        COUNT(*) as total_deliveries,
        COUNT(CASE WHEN oi.status = 'доставлен' THEN 1 END) as completed_deliveries,
        COUNT(CASE WHEN oi.status IN ('новый', 'в обработке', 'собирается', 'готов к отправке', 'в пути') THEN 1 END) as pending_deliveries,
        AVG(oi.dispatch_time - oi.created_at) as avg_delivery_time
    FROM order_items oi
    WHERE oi.assigned_courier_id = courier_id_param
    AND oi.dispatch_time IS NOT NULL;
END;
$$ LANGUAGE plpgsql;

-- функция для проверки остатков на складе
CREATE OR REPLACE FUNCTION check_inventory()
RETURNS TABLE(
    product_id INTEGER,
    product_name VARCHAR,
    current_quantity INTEGER,
    reorder_level INTEGER,
    needs_restock BOOLEAN
) AS $$
BEGIN
    RETURN QUERY
    SELECT 
        p.product_id,
        p.name,
        p.quantity,
        p.reorder_level,
        (p.quantity <= p.reorder_level) as needs_restock
    FROM products p
    ORDER BY needs_restock DESC, p.quantity ASC;
END;
$$ LANGUAGE plpgsql;

SELECT 'База данных успешно создана!' as message;

SELECT 
    (SELECT COUNT(*) FROM couriers) as total_couriers,
    (SELECT COUNT(*) FROM products) as total_products,
    (SELECT COUNT(*) FROM order_items) as total_orders;

-- Показать активных курьеров
SELECT courier_id, last_name, first_name, phone, vehicle_type 
FROM couriers 
WHERE is_active = TRUE 
ORDER BY last_name;

-- Показать товары с низким остатком
SELECT name, quantity, reorder_level 
FROM products 
WHERE quantity <= reorder_level 
ORDER BY quantity ASC;
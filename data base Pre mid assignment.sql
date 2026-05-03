DROP DATABASE IF EXISTS RetailDB;-- using only create command was giving error 
CREATE DATABASE IF NOT EXISTS RetailDB;
USE RetailDB;-- Customers Table
CREATE TABLE Customers (
    customer_id INT PRIMARY KEY,
    customer_name VARCHAR(100) NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    city VARCHAR(100),
    gender CHAR(1),
    registration_date DATE NOT NULL DEFAULT (CURRENT_DATE),
    CHECK (gender IN ('M', 'F') OR gender IS NULL)
);

-- Suppliers Table
CREATE TABLE Suppliers (
    supplier_id INT PRIMARY KEY,
    supplier_name VARCHAR(100) NOT NULL,
    contact_email VARCHAR(100) UNIQUE,
    city VARCHAR(100),
    phone_number VARCHAR(20),
    registration_date DATE NOT NULL DEFAULT (CURRENT_DATE)
);

-- Products Table
CREATE TABLE Products (
    product_id INT PRIMARY KEY,
    product_name VARCHAR(100) NOT NULL,
    category VARCHAR(100) NOT NULL,
    price DECIMAL(10,2) NOT NULL CHECK (price >= 0),
    stock_quantity INT NOT NULL DEFAULT 0 CHECK (stock_quantity >= 0),
    is_active BOOLEAN DEFAULT TRUE,
    supplier_id INT,
    FOREIGN KEY (supplier_id) REFERENCES Suppliers(supplier_id)
);

-- Sales Table
CREATE TABLE Sales (
    sale_id INT PRIMARY KEY,
    customer_id INT NOT NULL,
    product_id INT NOT NULL,
    quantity INT NOT NULL CHECK (quantity > 0),
    sale_date DATE NOT NULL DEFAULT (CURRENT_DATE),
    FOREIGN KEY (customer_id) REFERENCES Customers(customer_id),
    FOREIGN KEY (product_id) REFERENCES Products(product_id)
);
-- Insert Customers
INSERT INTO Customers (customer_id, customer_name, email, city, gender, registration_date) VALUES
(1,  'Ali',    'ali@example.com',    'Karachi',    'M', '2024-06-15'),
(2,  'Sara',   'sara@example.com',   'Lahore',     'F', '2025-01-10'),
(3,  'Ahmed',  'ahmed@example.com',  'Karachi',    'M', '2025-02-20'),
(4,  'Zara',   'zara@example.com',   'Islamabad',  'F', '2024-11-05'),
(5,  'Ayesha', 'ayesha@example.com', 'Lahore',     'F', '2024-03-12'),
(6,  'Usman',  'usman@example.com',  'Islamabad',  'M', '2024-12-08'),
(7,  'Hassan', 'hassan@example.com', 'Multan',     'M', '2024-02-01'),
(8,  'Fatima', 'fatima@example.com', 'Karachi',    'F', '2024-09-20'),
(9,  'Bilal',  'bilal@example.com',  'Lahore',     'M', '2025-01-25'),
(10, 'Maryam', 'maryam@example.com', 'Faisalabad', 'F', '2024-08-30'),
(11, 'Omar',   'omar@example.com',   'Islamabad',  'M', '2024-02-14'),
(12, 'Amina',  'amina@example.com',  'Multan',     'F', '2024-10-11'),
(13, 'Tariq',  'tariq@example.com',  'Karachi',    'M', '2024-03-05'),
(14, 'Hina',   'hina@example.com',   'Faisalabad', 'F', '2025-01-18'),
(15, 'Sami',   'sami@example.com',   'Lahore',     'M', '2024-07-22');

-- Insert Suppliers
INSERT INTO Suppliers (supplier_id, supplier_name, contact_email, city, phone_number, registration_date) VALUES
(1,  'Nishat',            'info@nishat.com',          'Lahore',     '03001234501', '2024-01-05'),
(2,  'Sapphire',          'contact@sapphire.com',     'Lahore',     '03001234502', '2024-02-10'),
(3,  'Khaadi',            'info@khaadi.com',           'Karachi',    '03001234503', '2024-03-15'),
(4,  'SheGlam Pakistan',  'info@sheglam.pk',           'Karachi',    '03001234504', '2024-04-20'),
(5,  'Rivaj Cosmetics',   'contact@rivaj.com',         'Islamabad',  '03001234505', '2024-05-25'),
(6,  'Medora Beauty',     'info@medora.pk',            'Karachi',    '03001234506', '2024-06-30'),
(7,  'Samsung Pakistan',  'support@samsung.com',       'Karachi',    '03001234507', '2024-07-05'),
(8,  'LG Pakistan',       'info@lg.com',               'Islamabad',  '03001234508', '2024-08-10'),
(9,  'Apple Pakistan',    'support@apple.com',         'Karachi',    '03001234509', '2024-09-15'),
(10, 'Metro Cash & Carry','contact@metro.com',         'Lahore',     '03001234510', '2024-10-20'),
(11, 'Imtiaz Super Market','support@imtiaz.com',       'Karachi',    '03001234511', '2024-11-25'),
(12, 'Al-Fatah',          'info@alfatah.com',          'Islamabad',  '03001234512', '2024-12-30'),
(13, 'HomePlus',          'info@homeplus.com',         'Faisalabad', '03001234513', '2025-01-05'),
(14, 'Daraz',             'support@daraz.com',         'Karachi',    '03001234514', '2025-02-10'),
(15, 'Fashion Street',    'contact@fashionstreet.com', 'Lahore',     '03001234515', '2025-03-15');

-- Insert Products
INSERT INTO Products (product_id, product_name, category, price, stock_quantity, is_active, supplier_id) VALUES
(1,  'Nishat Shirt',           'Clothing',     3500.00,  25, TRUE, 1),
(2,  'Sapphire Dress',         'Clothing',     5000.00,  15, TRUE, 2),
(3,  'Khaadi Kurta',           'Clothing',     4000.00,  20, TRUE, 3),
(4,  'SheGlam Lipstick',       'Makeup',       2500.00,  20, TRUE, 4),
(5,  'Rivaj Eyeshadow Palette','Makeup',       4500.00,  10, TRUE, 5),
(6,  'Medora Nail Polish',     'Makeup',       1200.00,  30, TRUE, 6),
(7,  'Samsung TV',             'Electronics',  80000.00,  5, TRUE, 7),
(8,  'LG Fridge',              'Electronics',  90000.00,  4, TRUE, 8),
(9,  'Apple iPhone',           'Electronics', 150000.00, 10, TRUE, 9),
(10, 'Rice 5kg',               'Grocery',      3000.00,  50, TRUE, 10),
(11, 'Dalda Oil 1L',           'Grocery',      1500.00,  25, TRUE, 11),
(12, 'Cooking Spices Set',     'Grocery',      2000.00,  30, TRUE, 12),
(13, 'Microwave Oven',         'Electronics',  20000.00,  8, TRUE, 13),
(14, 'Daraz Beauty Mascara',   'Makeup',       1500.00,  25, TRUE, 14),
(15, 'Fashion Street Jeans',   'Clothing',     2500.00,  25, TRUE, 15);

-- Insert Sales
INSERT INTO Sales (sale_id, customer_id, product_id, quantity, sale_date) VALUES
(1,  1,  3,  2, '2020-03-02'),
(2,  2,  5,  3, '2025-01-06'),
(3,  3,  1,  3, '2022-06-14'),
(4,  4,  2,  2, '2025-01-14'),
(5,  5,  4,  5, '2022-09-20'),
(6,  6,  6,  4, '2025-02-10'),
(7,  7,  7,  2, '2023-01-11'),
(8,  8,  8,  4, '2023-02-07'),
(9,  9,  9,  2, '2023-02-08'),
(10, 10, 10, 3, '2023-03-01'),
(11, 11, 11, 1, '2023-03-02'),
(12, 12, 12, 2, '2023-03-03'),
(13, 13, 13, 5, '2023-04-05'),
(14, 14, 14, 3, '2025-02-25'),
(15, 15, 15, 2, '2025-05-10');

-- QUES 1
SELECT DISTINCT city, gender
FROM Customers
ORDER BY city, gender;

-- QUES 2
SELECT product_name,
       category,
       price AS original_price,
       price * 0.9 AS discounted_price
FROM Products
WHERE is_active = 1
  AND price > 1000
ORDER BY discounted_price DESC;

-- QUES 3
SELECT *
FROM Sales
WHERE quantity > 1
  AND DAYOFWEEK(sale_date) BETWEEN 2 AND 4
ORDER BY sale_date DESC, quantity ASC;
-- QUES 4
SELECT category,
       COUNT(*) AS total_products,
       SUM(stock_quantity) AS total_stock
FROM Products
GROUP BY category
HAVING COUNT(*) > 2
ORDER BY total_products DESC;

-- QUES 5
SELECT category,
       AVG(price) AS avg_price,
       MAX(price) AS max_price
FROM Products
GROUP BY category
HAVING AVG(price) > 1000
ORDER BY avg_price DESC;

-- QUES 6
SELECT customer_id,
       SUM(quantity) AS total_quantity,
       COUNT(*) AS total_orders
FROM Sales
WHERE quantity > 0
GROUP BY customer_id
ORDER BY total_quantity DESC;

-- QUES 7
SELECT category,
       MIN(price) AS min_price,
       MAX(price) AS max_price,
       AVG(price) AS avg_price
FROM Products
GROUP BY category
HAVING MIN(price) < 5000
ORDER BY avg_price DESC;

-- QUES 8
SELECT product_id,
       SUM(quantity) AS total_quantity,
       COUNT(DISTINCT customer_id) AS distinct_customers
FROM Sales
GROUP BY product_id
HAVING SUM(quantity) > 2
ORDER BY total_quantity DESC;

-- QUES 9
SELECT product_id,
       SUM(quantity) AS total_units_sold,
       AVG(quantity) AS avg_quantity
FROM Sales
GROUP BY product_id
HAVING SUM(quantity) > 1
ORDER BY total_units_sold DESC, avg_quantity ASC;

-- QUES 10
SELECT sale_id, customer_id, product_id, quantity, sale_date
FROM Sales
WHERE quantity > 1
  AND sale_id % 2 = 0
  AND sale_date BETWEEN '2025-01-01' AND '2025-03-01'
ORDER BY sale_date DESC, quantity ASC;


-- QUES 11
SELECT category,
       SUM(stock_quantity) AS total_stock,
       COUNT(product_id) AS total_products
FROM Products
GROUP BY category
HAVING SUM(stock_quantity) > 20
ORDER BY total_stock DESC;

-- QUES 12
SELECT
    CONCAT(UPPER(LEFT(customer_name, 1)), LOWER(SUBSTRING(customer_name, 2))) AS formatted_name,
    DATE_FORMAT(registration_date, '%b-%Y') AS registration_month_year
FROM Customers
WHERE registration_date < CURDATE()
ORDER BY registration_date DESC;
CREATE TABLE players(id INT AUTO_INCREMENT PRIMARY KEY, name VARCHAR(255), login_time DATETIME, device INT);

INSERT INTO players(name, login_time, device) VALUES ('Mary', '2025-07-22 19:30:35', 11);
INSERT INTO players(name, login_time, device) VALUES ('Mathew', '2025-07-22 19:30:35', 12);
INSERT INTO players(name, login_time, device) VALUES ('Laura', '2025-07-21 19:30:35', 11);
INSERT INTO players(name, login_time, device) VALUES ('John', '2025-07-21 19:30:35', 11);
INSERT INTO players(name, login_time, device) VALUES ('Glen', '2025-07-20 19:30:35', 11);
INSERT INTO players(name, login_time, device) VALUES ('Joyce', '2025-07-18 19:30:35', 13);
INSERT INTO players(name, login_time, device) VALUES ('Clyde', '2025-07-15 19:30:35', 13);
INSERT INTO players(name, login_time, device) VALUES ('Maureen', '2025-07-15 19:30:35', 11);
INSERT INTO players(name, login_time, device) VALUES ('Maureen', '2025-07-15 19:30:35', 11);
INSERT INTO players(name, login_time, device) VALUES ('Chester', '2025-07-11 19:30:35', 11);
INSERT INTO players(name, login_time, device) VALUES ('Heather', '2025-07-11 19:30:35', 11);
INSERT INTO players(name, login_time, device) VALUES ('Clark', '2025-07-11 19:30:35', 13);

SELECT device, COUNT(id) AS login_count
FROM players
GROUP BY device
ORDER BY login_count DESC
LIMIT 5;

SELECT AVG(daily_logins) AS avg_logins_per_day
FROM (
    SELECT DATE(login_time) AS login_date, COUNT(id) AS daily_logins
    FROM players
    WHERE login_time >= DATE_SUB(CURRENT_DATE(), INTERVAL 7 DAY)
    GROUP BY DATE(login_time)
) AS daily_counts;
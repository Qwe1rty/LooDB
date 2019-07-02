CREATE TABLE collection (
    id INTEGER NOT NULL,
    name TEXT NOT NULL,
    space TEXT,
    num REAL NOT NULL,
    thing TEXT
);

INSERT INTO collection
VALUES
    (111, "hello", "world", 1234, "there"),
    (222, "hello", "world", 2345, "here");

INSERT INTO collection(id, name, space, num)
VALUES
    (333, "goodbye", "world", 3456);

SELECT * FROM collection;
CREATE TABLE collection (
    item INTEGER
);

INSERT INTO collection
VALUES
    (5),
    (6),
    (7);

SELECT * FROM collection;

EXPLAIN SELECT * FROM collection
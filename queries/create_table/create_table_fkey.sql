CREATE TABLE account (
    user_id INTEGER PRIMARY KEY,
    username TEXT NOT NULL,
    email TEXT NOT NULL
);

EXPLAIN CREATE TABLE credit_card (
    card_id INTEGER PRIMARY KEY,
    card_name TEXT NOT NULL,
    account_id INTEGER NOT NULL,
    FOREIGN KEY (account_id) REFERENCES account(user_id)
)
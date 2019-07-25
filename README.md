# LooDB

LooDB is a lightweight SQL database based on SQLite3. 

![Architecture diagram](/assets/loodb_architecture_diagram.svg "Architecture Diagram")
----


### SQLoo: The Official Query Language for LooDB

LooDB features its own flavor of SQL, which can currently support queries as specified below:

| Command     | **`create table`** |
| ----------- | ------------------ |
| Syntax      | `create table [table name] ( [col name] [type] [restriction], …);` |
| Explanation | `[table name]` is the name of your table<br>`[col]` name is the name of your column<br>`[type]` is either `integer` or `text`<br>`[restriction]` is either `primary key` or `not null` |

| Command     | **`drop table`** |
| ----------- | ---------------- |
| Syntax      | `drop table [table_name];` |
| Explanation | `[table name]` is the name of your table |

| Command     | **`insert`** |
| ----------- | ------------ |
| Syntax      | `insert into [table name] values ([value], …);` |
| Explanation | `[table name]` is the name of your table<br>`[value]` is either a null, text, or integer type |

| Command     | **`select`** |
| ----------- | ------------ |
| Syntax      | `select [cols] from [table name] where [wheres];` |
| Explanation | `[cols]` is either a list of valid column names or "*"<br>`[table name]` is the name of your table<br>is an expression of logical equalities, e.g. `(a = 'hello' and (b = 5 or c = null))` |

There are currently some limitations to the parser, as it will not accept:
- Negative integers
- Strings that contain spaces in them
----


### Installation Instructions

_**NOTE:** these instructions are currently only written for Ubuntu_

Before compiling the project, you will need to ensure that the prerequisites are correctly installed first.

Flex & Bison is the parser generator used to create the SQLoo interpreter. To install Flex & Bison,
run the following commands:

```
sudo apt update
sudo apt install flex bison
```

To compile LooDB, please ensure that your system has a version of the `g++` compiler that can support C++17.
Then, clone the repository and head to the project's root directory and run the command:
```
make
```
...and as long as there's a `loodb` executable produced, you're done! Simply run the `loodb` executable 
wherever you'd like to create a local `./loo` database directory 
# LooDB

LooDB is a lightweight SQL database based on SQLite3. 

![Architecture diagram](/assets/loodb_architecture_diagram_small.png "Architecture Diagram")
----


### SQLoo: The Official Query Language for LooDB

LooDB features its own flavor of SQL, which can currently support queries as specified below:

###### **`create`**
`create table [table name] ( [col name] [type] [restriction], …);`
- Where `[table name]` is the name of your table
- `[col]` name is the name of your column
- `[type]` is either `integer` or `text`
- `[restriction]` is either `primary key` or `not null`
    
###### **`drop`**
`drop table [table_name];`
- Where `[table name]` is the name of your table

###### **`insert`**
`insert into [table name] values ([value], …);`
- Where `[table name]` is the name of your table
- Where `[value]` is either a null, text, or integer type

###### **`select`**
`select [cols] from [table name] where [wheres];`
- Where `[cols]` is either a list of valid column names or “*”
- Where `[table name]` is the name of your table
- Where is an expression of logical equalities, e.g. `(a = 'hello' and (b = 5 or c = null))`

There are currently some limitations to the parser, as it will not accept:
- Negative integers
- Strings that contain spaces in them
----


### Installation Instructions

TODO
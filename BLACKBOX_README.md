# Children Metrics Generator

## About this

This project simply generate height and weight for children according to their age based on the data available on internet.

The program read data from mysql database and stores the result by creating a new table in it.

## Dependencies

* C++ compiler
* Mysql
* MySQL Connector/C++

### Compiling

On Ubuntu, you can compile the program using the following command:

```shell
g++ -Wall -I/usr/include/cppconn -o main main.cpp -L/usr/lib -lmysqlcppconn
```

### Execution

To execute the program, run the following command:

```shell
./main
```

The program will read data from the `children_metrics` table in the `my_database` database and generate a new table called `children_metrics_new`. The new table will contain the following columns:

* `age`: The age of the child in years.
* `height`: The height of the child in inches.
* `weight`: The weight of the child in pounds.

## Code Explanation

The program is written in C++. The main function is defined in the `main.cpp` file. The function first connects to the `my_database` database and creates a new table called `children_metrics_new`. The function then reads data from the `children_metrics` table and inserts it into the `children_metrics_new` table. The function finally closes the connection to the database.

The `children_metrics.sql` file contains the SQL statements used to create the `children_metrics` table. The `children_metrics_new.sql` file contains the SQL statements used to create the `children_metrics_new` table.

The `data.csv` file contains the data used to generate the `children_metrics` table. The file contains the following columns:

* `age`: The age of the child in years.
* `height`: The height of the child in inches.
* `weight`: The weight of the child in pounds.

## Usage

To use the program, you will need to have a MySQL database and a MySQL user account with the necessary privileges to create and modify tables. You will also need to download the MySQL Connector/C++ library.

Once
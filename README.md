# Children Metrics Generator

## About this

This project simply generate height and weight for children according to their age based on the data available on internet.


The program read data from mysql database and stores the result by creating a new table in it.

## Depends on
* C++ compiler
* Mysql
* MySQL Connector/C++ 

### Compiling

On Ubuntu

```shell
g++ -Wall -I/usr/include/cppconn -o main main.cpp -L/usr/lib -lmysqlcppconn
```
### Execution

On Ubuntu

```shell
./main
```
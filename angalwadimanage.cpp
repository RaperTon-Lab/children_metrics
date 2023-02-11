#include <stdlib.h>
#include <iostream>
#include "weight.hpp"
#include <iomanip>
#include "utils.hpp"

/*
  Include directly the different
  headers from cppconn/ and mysql_driver.h + mysql_util.h
  (and mysql_connection.h). This will reduce your build time!
*/

using namespace std;

int main(void)
{
    cout << endl;
    Date date = Date();
    std::string _checkTableQuery;
    std::string choice;

    try
    {
        sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::ResultSet *res;

        /* Create a connection */
        driver = get_driver_instance();
        con = driver->connect("localhost", "user", "passworD@123");
        /* Connect to the MySQL test database */
        con->setSchema("angalwadi");

        stmt = con->createStatement();
        for (int i = 0; i <= 0; ++i)
        {

            // Children table block
            std::string tablename = tableName(date, "children");
            _checkTableQuery = "SELECT COUNT(*) FROM information_schema.tables WHERE table_schema = 'angalwadi' AND table_name = '" + tablename + "';";
            res = stmt->executeQuery(_checkTableQuery);
            res->next();
            if (res->getInt(1) == 0)
            {
                cout << "Table does not exist." << endl;
            }
            else
            {
                cout << "Table exists for this month." << endl;
                std::cout << "\nDo you want to recalculate and recreate table, y|n:\t";
                std::cin >> choice;
                if (choice == "n")
                    continue;
                else
                {
                    stmt->execute("DROP TABLE " + tablename + "; ");
                }
            }
            // std::cout << "\n Not Jumped\n";
            stmt->execute("CREATE TABLE " + tablename + " (Sl_No INT NOT NULL AUTO_INCREMENT, Name VARCHAR(255) NOT NULL,Year INT NOT NULL,Month INT NOT NULL,Height_cm FLOAT NOT NULL,Weight_Kg FLOAT NOT NULL,PRIMARY KEY(Sl_No)); "); // create a new table !!!!!!!!!!! upto here
            cout << "\n Table " + tablename + " created.\n";
            res = stmt->executeQuery("SELECT * from children;");
            while (res->next())
            {
                Date _birthdate(res->getString("DOB"));
                Age age(_birthdate, date);
                if (age.years >= 3)
                {
                    stmt->execute("DELETE FROM children where Sl_No = " + res->getString("Sl_No") + "; ");
                    stmt->execute("SET  @num := 0;");
                    stmt->execute("UPDATE children SET Sl_No = @num := (@num+1);");
                    stmt->execute("ALTER TABLE children AUTO_INCREMENT = 1;");
                    std::cout << "\nDeleted " + res->getString("Name") + " from children Table.\n";
                    stmt->execute("INSERT INTO preschool (Name,DOB,Sex) values('" + res->getString("Name") + "','" + res->getString("DOB") + "','" + res->getString("Sex") + "');");
                    std::cout << "\n" + res->getString("Name") + " added to preschool table.\n";
                    continue;
                }
                std::string sex = res->getString("Sex");
                std::pair<float, float> metrics = calculateMetrics(age, sex[0]);
                stmt->execute("INSERT INTO " + tablename + " (Name, Year,Month,Height_cm,Weight_Kg) values('" + res->getString("Name") + "'," + to_string(age.years) + "," + to_string(age.months) + "," + to_string(metrics.first) + "," + to_string(metrics.second) + ");");
            }
            std::cout << "\nTable generation for children for this month complete.\n";
        }
        for (int i = 0; i <= 0; ++i)
        {

            // Preschool table block
            std::string tablename = tableName(date, "preschool");
            _checkTableQuery = "SELECT COUNT(*) FROM information_schema.tables WHERE table_schema = 'angalwadi' AND table_name = '" + tablename + "';";
            res = stmt->executeQuery(_checkTableQuery);
            res->next();
            if (res->getInt(1) == 0)
            {
                cout << "Table does not exist." << endl;
            }
            else
            {
                cout << "Table exists for this month for preschool." << endl;
                std::cout << "\nDo you want to recalculate and recreate table, y|n:\t";
                std::cin >> choice;
                if (choice == "n")
                    continue;
                else
                {
                    stmt->execute("DROP TABLE " + tablename + "; ");
                }
            }
            // std::cout << "\n Not Jumped\n";
            stmt->execute("CREATE TABLE " + tablename + " (Sl_No INT NOT NULL AUTO_INCREMENT, Name VARCHAR(255) NOT NULL,Year INT NOT NULL,Month INT NOT NULL,Height_cm FLOAT NOT NULL,Weight_Kg FLOAT NOT NULL,PRIMARY KEY(Sl_No)); "); // create a new table !!!!!!!!!!! upto here
            cout << "\n Table " + tablename + " created.\n";
            res = stmt->executeQuery("SELECT * from preschool;");
            while (res->next())
            {
                Date _birthdate(res->getString("DOB"));
                Age age(_birthdate, date);
                if (age.years >= 6)
                {
                    stmt->execute("DELETE FROM prechool where Sl_No = " + res->getString("Sl_No") + "; ");
                    stmt->execute("SET  @num := 0;");
                    stmt->execute("UPDATE preschool SET Sl_No = @num := (@num+1);");
                    stmt->execute("ALTER TABLE preschool AUTO_INCREMENT = 1;");
                    std::cout << "\nDeleted " + res->getString("Name") + " from prechool Table.\n";
                    continue;
                }
                std::string sex = res->getString("Sex");
                std::pair<float, float> metrics = calculateMetrics(age, sex[0]);
                stmt->execute("INSERT INTO " + tablename + " (Name, Year,Month,Height_cm,Weight_Kg) values('" + res->getString("Name") + "'," + to_string(age.years) + "," + to_string(age.months) + "," + to_string(metrics.first) + "," + to_string(metrics.second) + ");");
            }
            std::cout << "\nTable generation for preschool for this month complete.\n";
        }
        delete res;
        delete stmt;
        delete con;
    }
    catch (sql::SQLException &e)
    {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }

    cout << endl;

    return EXIT_SUCCESS;
}
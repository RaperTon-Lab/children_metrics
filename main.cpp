#include <iostream>
#include <cstdlib>
#include "weight.hpp"
#include "utils.hpp"

/*
  Include directly the different
  headers from cppconn/ and mysql_driver.h + mysql_util.h
  (and mysql_connection.h). This will reduce your build time!
*/
int main(void)
{
    std::cout << std::endl;
    Date date = Date();
    std::string _checkTableQuery;
    std::string choice;
    std::string listOfTable = "";

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

        // infant block
        for (int i = 0; i <= 0; ++i)
        {
            std::cout << "\n\n--------------Infant-------\n\n";
            // Children table block
            std::string tablename = tableName(date, "infant");
            listOfTable = listOfTable + tablename + " ";
            _checkTableQuery = "SELECT COUNT(*) FROM information_schema.tables WHERE table_schema = 'angalwadi' AND table_name = '" + tablename + "';";
            res = stmt->executeQuery(_checkTableQuery);
            res->next();
            if (res->getInt(1) == 0)
            {
                std::cout << "Table does not exist." << std::endl;
            }
            else
            {
                std::cout << "Table exists for this month." << std::endl;
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
            std::cout << "\n Table " + tablename + " created.\n";
            res = stmt->executeQuery("SELECT * from infant;");
            while (res->next())
            {
                Date _birthdate(res->getString("DOB"));
                Age age(_birthdate, date);
                if (age.months >= 6)
                {
                    stmt->execute("DELETE FROM infant where Sl_No = " + res->getString("Sl_No") + "; ");
                    stmt->execute("SET  @num := 0;");
                    stmt->execute("UPDATE infant SET Sl_No = @num := (@num+1);");
                    stmt->execute("ALTER TABLE infant AUTO_INCREMENT = 1;");
                    std::cout << "\nDeleted " + res->getString("Name") + " from infant Table.\n";
                    stmt->execute("INSERT INTO infant (Name,DOB,Sex) values('" + res->getString("Name") + "','" + res->getString("DOB") + "','" + res->getString("Sex") + "');");
                    std::cout << "\n" + res->getString("Name") + " added to infant table.\n";
                    continue;
                }
                std::string sex = res->getString("Sex");
                std::pair<float, float> metrics = calculateMetrics(age, sex[0]);
                stmt->execute("INSERT INTO " + tablename + " (Name, Year,Month,Height_cm,Weight_Kg) values('" + res->getString("Name") + "'," + std::to_string(age.years) + "," + std::to_string(age.months) + "," + toString(metrics.first) + "," + toString(metrics.second) + ");");
            }
            std::cout << "\nTable generation for infant for this month complete.\n";
        }

        // children
        for (int i = 0; i <= 0; ++i)
        {
            std::cout << "\n\n--------------children-------\n\n";
            // Children table block
            std::string tablename = tableName(date, "children");
            listOfTable = listOfTable + tablename + " ";
            _checkTableQuery = "SELECT COUNT(*) FROM information_schema.tables WHERE table_schema = 'angalwadi' AND table_name = '" + tablename + "';";
            res = stmt->executeQuery(_checkTableQuery);
            res->next();
            if (res->getInt(1) == 0)
            {
                std::cout << "Table does not exist." << std::endl;
            }
            else
            {
                std::cout << "Table exists for this month." << std::endl;
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
            std::cout << "\n Table " + tablename + " created.\n";
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
                stmt->execute("INSERT INTO " + tablename + " (Name, Year,Month,Height_cm,Weight_Kg) values('" + res->getString("Name") + "'," + std::to_string(age.years) + "," + std::to_string(age.months) + "," + toString(metrics.first) + "," + toString(metrics.second) + ");");
            }
            std::cout << "\nTable generation for children for this month complete.\n";
        }

        for (int i = 0; i <= 0; ++i)
        {
            std::cout << "\n\n\n\n--------------Pre school---------\n\n";

            // Preschool table block
            std::string tablename = tableName(date, "preschool");
            listOfTable = listOfTable + tablename + " ";
            _checkTableQuery = "SELECT COUNT(*) FROM information_schema.tables WHERE table_schema = 'angalwadi' AND table_name = '" + tablename + "';";
            res = stmt->executeQuery(_checkTableQuery);
            res->next();
            if (res->getInt(1) == 0)
            {
                std::cout << "Table does not exist." << std::endl;
            }
            else
            {
                std::cout << "Table exists for this month for preschool." << std::endl;
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
            std::cout << "\n Table " + tablename + " created.\n";
            res = stmt->executeQuery("SELECT * from preschool;");
            while (res->next())
            {
                Date _birthdate(res->getString("DOB"));
                Age age(_birthdate, date);
                if (age.years >= 6)
                {
                    stmt->execute("DELETE FROM preschool where Sl_No = " + res->getString("Sl_No") + "; ");
                    stmt->execute("SET  @num := 0;");
                    stmt->execute("UPDATE preschool SET Sl_No = @num := (@num+1);");
                    stmt->execute("ALTER TABLE preschool AUTO_INCREMENT = 1;");
                    std::cout << "\nDeleted " + res->getString("Name") + " from preschool Table.\n";
                    continue;
                }
                std::string sex = res->getString("Sex");
                std::pair<float, float> metrics = calculateMetrics(age, sex[0]);
                stmt->execute("INSERT INTO " + tablename + " (Name, Year,Month,Height_cm,Weight_Kg) values('" + res->getString("Name") + "'," + std::to_string(age.years) + "," + std::to_string(age.months) + "," + toString(metrics.first) + "," + toString(metrics.second) + ");");
            }
            std::cout << "\nTable generation for preschool for this month complete.\n";
        }

        // teens
        for (int i = 0; i <= 0; ++i)
        {
            std::cout << "\n\n\n\n--------------Aolescent---------\n\n";
            // Adolescent table block
            std::string tablename = tableName(date, "adolescent");
            listOfTable = listOfTable + tablename;
            _checkTableQuery = "SELECT COUNT(*) FROM information_schema.tables WHERE table_schema = 'angalwadi' AND table_name = '" + tablename + "';";
            res = stmt->executeQuery(_checkTableQuery);
            res->next();
            if (res->getInt(1) == 0)
            {
                std::cout << "Table does not exist." << std::endl;
            }
            else
            {
                std::cout << "Table exists for this month for adolescent." << std::endl;
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
            std::cout << "\n Table " + tablename + " created.\n";
            res = stmt->executeQuery("SELECT * from adolescent;");
            while (res->next())
            {
                Date _birthdate(res->getString("DOB"));
                Age age(_birthdate, date);
                std::string sex = res->getString("Sex");
                std::pair<float, float> metrics = calculateMetrics(age, sex[0]);
                stmt->execute("INSERT INTO " + tablename + " (Name, Year,Month,Height_cm,Weight_Kg) values('" + res->getString("Name") + "'," + std::to_string(age.years) + "," + std::to_string(age.months) + "," + toString(metrics.first) + "," + toString(metrics.second) + ");");
            }
            std::cout << "\nTable generation for adolescent for this month complete.\n";
        }

        delete res;
        delete stmt;
        delete con;
    }
    catch (sql::SQLException &e)
    {
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }

    std::cout << std::endl;

    std::cout << "--------------------------------Running the Python script from for PDF generation--------------------------------" << std::endl;
    std::string py_script = "python3 tabletopdf.py \"" + listOfTable + "\"";
    std::cout << py_script << std::endl;
    int exitCode = system(py_script.c_str());
    if (exitCode == 0)
    {
        std::cout << "\nPDF Generation Successful!\n";
    }
    else
    {
        std::cerr << "\nCannot run the specified python script!\n";
    }

    std::cout << "--------------------------------Running the Python script from for PDF merger--------------------------------" << std::endl;
    py_script = "python3 pdfmerger.py";
    exitCode = system(py_script.c_str());
    if (exitCode == 0)
    {
        std::cout << "\nPDF merger Successful!\n";
    }
    else
    {
        std::cerr << "\nCannot run the specified python script!\n";
    }

    return EXIT_SUCCESS;
}
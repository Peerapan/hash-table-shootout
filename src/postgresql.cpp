#include <iostream>
#include <pqxx/pqxx>

pqxx::connection C("dbname=tempPostgreSQL user=tempCubic password=Cubic \
                   hostaddr=127.0.0.1 port=5432");
std::string tmp;
pqxx::nontransaction W(C);

#define SETUP tmp = "CREATE TABLE IF NOT EXISTS INTTABLE(" \
"KEY    INT PRIMARY KEY NOT NULL," \
"VALUE              INT NOT NULL );"; \
W.exec( tmp ); \
tmp = "CREATE TABLE IF NOT EXISTS STRTABLE(" \
"KEY    CHAR(10) PRIMARY KEY NOT NULL," \
"VALUE              INT NOT NULL );"; \
W.exec( tmp );

#define INSERT_INT_INTO_HASH(key, value) tmp = "INSERT INTO INTTABLE (KEY,VALUE) VALUES (" + std::to_string(key) + ", " + std::to_string(value) + "); "; \
try{ W.exec( tmp ); }catch(const std::exception &e){ }

#define DELETE_INT_FROM_HASH(key) tmp = "DELETE FROM INTTABLE WHERE KEY=" + std::to_string(key); \
try{ W.exec( tmp ); }catch(const std::exception &e){ }

#define INSERT_STR_INTO_HASH(key, value) tmp = "INSERT INTO STRTABLE (KEY,VALUE) VALUES (\'"; \
tmp += key; tmp += "\', " + std::to_string(value) + "); "; \
try{ W.exec( tmp ); }catch(const std::exception &e){ }

#define DELETE_STR_FROM_HASH(key) tmp = "DELETE FROM STRTABLE WHERE KEY=\'"; \
tmp += key; tmp += "\'"; try{ W.exec( tmp ); }catch(const std::exception &e){ }

#define CLEAR tmp = "DELETE FROM INTTABLE"; \
W.exec( tmp ); tmp = "DELETE FROM STRTABLE"; W.exec( tmp );

#include "template.c"
#include <iostream>
#include <pqxx/pqxx>

pqxx::connection C("dbname=tempPostgreSQL user=tempCubic password=Cubic \
                   hostaddr=127.0.0.1 port=5432");
std::string tmp;
pqxx::work* W;

#define SETUP tmp = "CREATE TABLE IF NOT EXISTS INTTABLE(" \
"KEY    INT PRIMARY KEY NOT NULL," \
"VALUE              INT NOT NULL );"; \
W = new pqxx::work(C); try{ W->exec( tmp ); W->commit(); delete W;}catch (const std::exception &e){}  \
tmp = "CREATE TABLE IF NOT EXISTS STRTABLE(" \
"KEY    CHAR(10) PRIMARY KEY NOT NULL," \
"VALUE              CHAR(10) NOT NULL );"; \
W = new pqxx::work(C); try{ W->exec( tmp ); W->commit(); delete W; }catch (const std::exception &e){}
#define INSERT_INT_INTO_HASH(key, value) tmp = "INSERT INTO INTTABLE (KEY,VALUE) VALUES (" + std::to_string(key) + ", " + std::to_string(value) + "); "; \
W = new pqxx::work(C); try{ W->exec( tmp ); W->commit(); delete W; }catch (const std::exception &e){}

#define DELETE_INT_FROM_HASH(key) tmp = "DELETE FROM INTTABLE WHERE KEY=" + std::to_string(key); \
W = new pqxx::work(C); try{ W->exec( tmp ); W->commit(); delete W;}catch (const std::exception &e){}

#define INSERT_STR_INTO_HASH(key, value) tmp = "INSERT INTO STRTABLE (KEY,VALUE) VALUES (\'"; \
tmp += key; tmp += "\', \'" + std::to_string(value) + "\'); "; \
W = new pqxx::work(C); try{ W->exec( tmp ); W->commit(); delete W;}catch (const std::exception &e){}

#define DELETE_STR_FROM_HASH(key) tmp = "DELETE FROM STRTABLE WHERE KEY=\'"; \
tmp += key; tmp += "\'"; \
try{ W = new pqxx::work(C); W->exec( tmp ); W->commit(); delete W;}catch (const std::exception &e){}

#define CLEAR tmp = "DELETE FROM INTTABLE"; \
W = new pqxx::work(C); try{ W->exec( tmp );  W->commit(); delete W;}catch (const std::exception &e){} \
tmp = "DELETE FROM STRTABLE"; \
W = new pqxx::work(C); try{ W->exec( tmp );  W->commit(); delete W;}catch (const std::exception &e){}

static inline const char* InsertStrIntoHash(const char* key, int value)
{
    INSERT_STR_INTO_HASH(key, value);
    return key;
}
static inline int ExistsInIntHash(int key)
{
    tmp = "SELECT * FROM INTTABLE WHERE KEY=" + std::to_string(key);
        W = new pqxx::work(C);
        pqxx::result R( W->exec( tmp ) );
        pqxx::result::const_iterator res = R.begin();
        // res[0].as<int>() /* It's KEY column */
        W->commit();
        
        if(R.begin() != R.end())
            return 1;
        else
            return 0;
}
static inline int ExistsInStrHash(const char* key)
{
    tmp = "SELECT * FROM STRTABLE WHERE KEY=\'";
    tmp += key;
    tmp += "\'";
        W = new pqxx::work(C);
        pqxx::result R( W->exec( tmp ) );
        pqxx::result::const_iterator res = R.begin();
        // res[0].as<int>() /* It's KEY column */
        W->commit();
        
        if(R.begin() != R.end())
            return 1;
        else
            return 0;
}
static inline void SetIntIntoHash(int key, int value)
{
    std::string localStr = "UPDATE INTTABLE SET VALUE=" + std::to_string(value) \
    + " WHERE KEY=" + std::to_string(key);
        W = new pqxx::work(C);
        W->exec( localStr );
        W->commit();
}
static inline void SetStringIntoHash(const char* key, int value, size_t length)
{
    std::string localStr = "UPDATE STRTABLE SET VALUE=\'" + std::to_string(value) \
    + "\' WHERE KEY=\'" + key + "\'";
        W = new pqxx::work(C);
        W->exec( localStr );
        W->commit();
}

#include "template_access.c"
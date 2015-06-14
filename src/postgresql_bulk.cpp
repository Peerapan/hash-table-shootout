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

#define INSERT_STR_INTO_HASH(key, value) tmp = "INSERT INTO STRTABLE (KEY,VALUE) VALUES (\'"; \
tmp += key; tmp += "\', " + std::to_string(value) + "); "; \
try{ W.exec( tmp ); }catch(const std::exception &e){ }

#define CLEAR tmp = "DELETE FROM INTTABLE"; \
W.exec( tmp ); tmp = "DELETE FROM STRTABLE"; W.exec( tmp );


void BulkInsertIntIntoHash(int setIntKey[],int setIntValue[],int BULK_NO){
    int i;
    
    std::string sql = "INSERT INTO INTTABLE (KEY,VALUE) VALUES ";
    for(int i=0; i<BULK_NO-1; i++) {
        std::string appendSql = "(" + std::to_string(setIntKey[i]) + " ," + std::to_string(setIntValue[i]) + " ),";
        sql += appendSql;
    }
    std::string appendSql = "(" + std::to_string(setIntKey[BULK_NO-1]) + " ," + std::to_string(setIntValue[BULK_NO-1]) + " );";
    sql += appendSql;
    
    
    try{ W.exec( sql ); }catch(const std::exception &e){ }
}

void BulkDeleteIntFromHash(int setIntKey[], int BULK_NO){
    int i;
    
    std::string sql = "DELETE FROM INTTABLE WHERE ";
    for(int i=0; i<BULK_NO-1; i++) {
        std::string appendSql = "KEY = " + std::to_string(setIntKey[i]) + " OR ";
        sql += appendSql;
    }
    std::string appendSql = "KEY = " + std::to_string(setIntKey[BULK_NO-1]) + " ;";
    sql += appendSql;
    
    try{ W.exec( sql ); }catch(const std::exception &e){ }
}

void BulkInsertStrIntoHash(char* setStrKey[],int setIntValue[],int BULK_NO){
    int i;
    
    std::string sql = "INSERT INTO STRTABLE (KEY,VALUE) VALUES ";
    for(int i=0; i<BULK_NO-1; i++) {
        std::string appendSql = "(\'";
        appendSql += setStrKey[i];
        appendSql += "\' ,";
        appendSql += std::to_string(setIntValue[i]);
        appendSql += " ),";
        sql += appendSql;
    }
    std::string appendSql = "(\'";
    appendSql += setStrKey[BULK_NO-1];
    appendSql += "\' ,";
    appendSql += std::to_string(setIntValue[BULK_NO-1]);
    appendSql += " );";
    sql += appendSql;
    
    try{ W.exec( sql ); }catch(const std::exception &e){ }
}

void BulkDeleteStrFromHash(char* setStrKey[], int BULK_NO){
    int i;
    
    std::string sql = "DELETE FROM INTTABLE WHERE ";
    for(int i=0; i<BULK_NO-1; i++) {
        std::string appendSql = "KEY = \'";
        appendSql += setStrKey[i];
        appendSql += "\' OR ";
        sql += appendSql;
    }
    std::string appendSql = "KEY = \'";
    appendSql += setStrKey[BULK_NO-1];
    appendSql += "\' ;";
    sql += appendSql;
    
    try{ W.exec( sql ); }catch(const std::exception &e){ }
}

#include "template_bulk.c"
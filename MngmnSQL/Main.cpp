#include <iostream>
#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>

int main() {
    // Инициализируем ODBC драйвер
    SQLHENV env;
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
    SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);

    // Создаем и инициализируем соединение с базой данных
    SQLHDBC dbc;
    SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);
    //SQLCHAR connectionString[] = "DRIVER={SQL Server}; SERVER=ИМЯ_СЕРВЕРА; DATABASE=ИМЯ_БАЗЫ_ДАННЫХ; UID=ИМЯ_ПОЛЬЗОВАТЕЛЯ; PWD=ПАРОЛЬ;";
    SQLCHAR connectionString[] = "DRIVER={SQL Server}; SERVER=CHICHIL-SV; DATABASE=test; UID=sa; PWD=Qwerty123!;";
    SQLConnect(dbc, (SQLCHAR*)connectionString, SQL_NTS, NULL, SQL_NULL_HANDLE, SQL_NULL_HANDLE, NULL);

    // Отправляем запрос и получаем результат
    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    SQLCHAR query[] =  "SELECT * FROM Процесс";
    SQLExecDirect(stmt, query, SQL_NTS);

    // Обрабатываем результат
    SQLLEN id;
    SQLCHAR name[256];
    while (SQLFetch(stmt) == SQL_SUCCESS) {
        SQLGetData(stmt, 1, SQL_C_LONG, &id, 0, NULL);
        SQLGetData(stmt, 2, SQL_C_CHAR, name, 256, NULL);
        std::cout << "DocId: " << id << " Name: " << name << std::endl;
    }

    // Очищаем ресурсы
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    SQLDisconnect(dbc);
    SQLFreeHandle(SQL_HANDLE_DBC, dbc);
    SQLFreeHandle(SQL_HANDLE_ENV, env);

    return 0;
}

#include <iostream>
#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>

int main() {
    // �������������� ODBC �������
    SQLHENV env;
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
    SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);

    // ������� � �������������� ���������� � ����� ������
    SQLHDBC dbc;
    SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);
    //SQLCHAR connectionString[] = "DRIVER={SQL Server}; SERVER=���_�������; DATABASE=���_����_������; UID=���_������������; PWD=������;";
    SQLCHAR connectionString[] = "DRIVER={SQL Server}; SERVER=CHICHIL-SV; DATABASE=test; UID=sa; PWD=Qwerty123!;";
    SQLConnect(dbc, (SQLCHAR*)connectionString, SQL_NTS, NULL, SQL_NULL_HANDLE, SQL_NULL_HANDLE, NULL);

    // ���������� ������ � �������� ���������
    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    SQLCHAR query[] =  "SELECT * FROM �������";
    SQLExecDirect(stmt, query, SQL_NTS);

    // ������������ ���������
    SQLLEN id;
    SQLCHAR name[256];
    while (SQLFetch(stmt) == SQL_SUCCESS) {
        SQLGetData(stmt, 1, SQL_C_LONG, &id, 0, NULL);
        SQLGetData(stmt, 2, SQL_C_CHAR, name, 256, NULL);
        std::cout << "DocId: " << id << " Name: " << name << std::endl;
    }

    // ������� �������
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    SQLDisconnect(dbc);
    SQLFreeHandle(SQL_HANDLE_DBC, dbc);
    SQLFreeHandle(SQL_HANDLE_ENV, env);

    return 0;
}

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int callback(void *data, int argc, char **argv, char **azColName) {
    printf("✅ Login successful! Welcome %s\n", argv[0]);
    exit(0);
}

int main() {
    sqlite3 *db;
    char *err = 0;
    char username[100], password[100];
    char sql[300];

    sqlite3_open("./vulnerable/users.db", &db);

    printf("Username: ");
    scanf("%99s", username);

    printf("Password: ");
    scanf("%99s", password);

    snprintf(sql, sizeof(sql),
        "SELECT username FROM users WHERE username='%s' AND password='%s';",
        username, password);

    printf("\n[DEBUG] Executing SQL:\n%s\n\n", sql);

    if (sqlite3_exec(db, sql, callback, 0, &err) != SQLITE_OK) {
        printf("[SQL ERROR] %s\n", err);
    }


    printf("❌ Login failed\n");
    sqlite3_close(db);
    return 0;
}

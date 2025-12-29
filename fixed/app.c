#include <stdio.h>
#include <sqlite3.h>

int main() {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    char username[100], password[100];

    sqlite3_open("../vulnerable/users.db", &db);

    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);

    const char *sql =
        "SELECT username FROM users WHERE username=? AND password=?;";

    sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("✅ Secure login successful\n");
    } else {
        printf("❌ Secure login failed\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}

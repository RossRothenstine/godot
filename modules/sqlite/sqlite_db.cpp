#include "sqlite_db.h"

Ref<SQLiteDBStatement> SQLiteDB::prepare(const String &p_query) {
    Ref<SQLiteDBStatement> statement;
    statement.instantiate();
    statement->db = Ref<SQLiteDB>(this);
    return statement;
}

void SQLiteDB::_bind_methods() {
    ClassDB::bind_method(D_METHOD("prepare", "query"), &SQLiteDB::prepare);
}

void SQLiteDBStatement::_bind_methods() {

}
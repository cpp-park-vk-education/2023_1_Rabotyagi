class User: DatabaseTable{
    User("users"){
    }
    ~User(){
    }
    void initRecord(unsigned int id, const QString& username, const QString& hashed_password="", bool is_admin=False): _username=username, _hashed_password=hashed_password, _is_admin=is_admin;
    bool insertRecord() override {
        QSqlQuery query(db);
        query.prepare("INSERT INTO " + tableName + " (id,username, hashed_password, is_admin) VALUES (:id, :username, :hashed_password, :is_admin)");
        query.bindValue(":id", _id);
        query.bindValue(":username", _username);
        query.bindValue(":hashed_password", _hashed_password);
        query.bindValue(":is_admin", _is_admin);
        return query.exec();
    }
    bool deleteRecord() override {
        QSqlQuery query(db);
        query.prepare("DELETE FROM " + tableName + " WHERE id=:id");
        query.bindValue(":id", _id);
        return query.exec();
    }
    bool updateRecord() override{
        QSqlQuery query(db);
        query.prepare("UPDATE " + tableName + " SET username=:username, hashed_password=:hashed_password, is_admin:=is_admin WHERE id=:id");
        query.bindValue(":username", _username);
        query.bindValue(":hashed_password", _hashed_password);
        query.bindValue(":is_admin", _is_admin);
        return query.exec();
    }
    QList<QVariantList> readRecord() {
        QList<QVariantList> result;
        QSqlQuery query(db);
        query.prepare("SELECT * FROM " + tableName);
        if (query.exec()) {
            while (query.next()) {
                QVariantList record;
                record.append(query.value("id"));
                record.append(query.value("username"));
                record.append(query.value("hashed_password"));
                record.append(query.value("is_admin"));
                result.append(record);
            }
        } else {
            qDebug() << "Failed to select records:" << query.lastError().text();
        }
        return result;
    }
    private:
    unsigned int _id,
    QString _username,
    QString _hashed_password,
    bool is_admin;

}

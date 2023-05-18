class Guild : DatabaseTable
{
    Guild("guilds")
    {
    }
    ~Guild()
    {
    }
    void initRecord(unsigned int id, unsigned int owner_id, const QString &name, unsigned int user_count, const QString &created_at);
    bool insertRecord() override
    {
        QSqlQuery query(db);
        query.prepare("INSERT INTO " + tableName + " (id,owner_id,name, user_count, created_at) VALUES (:id, :owner_id, :name,:user_count, :created_at)");
        query.bindValue(":id", _id);
        query.bindValue(":owner_id", _owner_id);
        query.bindValue(":name", _name);
        query.bindValue(":user_count", _user_count);
        query.bindValue(":created_at", _created_at);
        return query.exec();
    }
    bool deleteRecord() override
    {
        QSqlQuery query(db);
        query.prepare("DELETE FROM " + tableName + " WHERE id=:id");
        query.bindValue(":id", _id);
        return query.exec();
    }
    bool updateRecord() override
    {
        QSqlQuery query(db);
        query.prepare("UPDATE " + tableName + " SET name=:name,user_count=:user_count WHERE id=:id");
        query.bindValue(":name", _name);
        query.bindValue(":user_count", _user_count);
        return query.exec();
    }
    QList<QVariantList> readRecord()
    {
        QList<QVariantList> result;
        QSqlQuery query(db);
        query.prepare("SELECT * FROM " + tableName);
        if (query.exec())
        {
            while (query.next())
            {
                QVariantList record;
                record.append(query.value("id"));
                record.append(query.value("owner_id"));
                record.append(query.value("name"));
                record.append(query.value("user_count"));
                record.append(query.value("created_at"));
                result.append(record);
            }
        }
        else
        {
            qDebug() << "Failed to select records:" << query.lastError().text();
        }
        return result;
    }

private:
    unsigned int _id,
        unsigned int _owner_id,
        unsigned int _name,
        QString _user_count,
        QString _created_at,
}

class Channel : DatabaseTable
{
    Channel("channels")
    {
    }
    ~Channel()
    {
    }
    void initRecord(unsigned int id, unsigned int guild_id, const QString &name, const QString &type, const QString &created_at, const QString &updated_at);
    bool insertRecord() override
    {
        QSqlQuery query(db);
        query.prepare("INSERT INTO " + tableName + " (id,guild_id,name, type, created_at, updated_at) VALUES (:id, :guild_id, :name,:type, :created_at, :updated_at)");
        query.bindValue(":id", _id);
        query.bindValue(":guild_id", _guild_id);
        query.bindValue(":name", _name);
        query.bindValue(":type", _type);
        query.bindValue(":created_at", _created_at);
        query.bindValue(":updated_at", _updated_at);
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
        query.prepare("UPDATE " + tableName + " SET name=:name,type=:type, updated_at=:updated_at WHERE id=:id");
        query.bindValue(":name", _name);
        query.bindValue(":type", _type);
        query.bindValue(":updated_at", _updated_at);
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
                record.append(query.value("guild_id"));
                record.append(query.value("name"));
                record.append(query.value("type"));
                record.append(query.value("created_at"));
                record.append(query.value("updated_at"));
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
        unsigned int _guild_id,
        unsigned int _name,
        QString _type,
        QString _created_at,
        QString _updated_at;
}
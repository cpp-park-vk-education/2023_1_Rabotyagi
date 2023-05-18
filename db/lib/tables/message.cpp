class Message : DatabaseTable
{
    Message("messages")
    {
    }
    ~Message()
    {
    }
    void initRecord(unsigned int id, unsigned int owner_id, unsigned int channel_id, const QString &content, const QString &created_at, const QString &updated_at);
    bool insertRecord() override
    {
        QSqlQuery query(db);
        query.prepare("INSERT INTO " + tableName + " (id,owner_id, channel_id, content, created_at, updated_at) VALUES (:id, :owner_id, :channel_id, :content, :created_at, :updated_at)");
        query.bindValue(":id", _id);
        query.bindValue(":owner_id", _owner_id);
        query.bindValue(":channel_id", _channel_id);
        query.bindValue(":content", _content);
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
        query.prepare("UPDATE " + tableName + " SET content=:content, updated_at=:updated_at WHERE id=:id");
        query.bindValue(":content", _content);
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
                record.append(query.value("owner_id"));
                record.append(query.value("channel_id"));
                record.append(query.value("content"));
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
        unsigned int _owner_id,
        unsigned int _channel_id,
        QString _content,
        QString _created_at,
        QString _updated_at;
}

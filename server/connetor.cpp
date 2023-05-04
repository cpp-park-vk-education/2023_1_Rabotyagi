class Guild : PostgresqlConnector {
    Guild() : PostgresqlConnector {};

    record read(1){
        /* Buisness Logic*/
        return result;
    };
    record update(){};
    record create(){};
    record delet(){};
}

class Channel {

    record read(){};
    record update(){};
    record create(){};
    record delet(){};
}

class User {

    record read(){};
    record update(){};
    record create(){};
    record delet(){};
}

{
    enum class GuildDB {
        first = "1, Server, 15 - usercount";
        first = "1, Server, 15 - usercount";
        first = "1, Server, 15 - usercount";
        first = "1, Server, 15 - usercount";
        first = "1, Server, 15 - usercount";
        first = "1, Server, 15 - usercount";
    }
}

// Assert
// Act
// Arrange
#include <iostream>
#include <data_types.hpp>

class UserManager {
public:

    static User* instance() {
         static User* _user = new User();
         return _user;
     }
};

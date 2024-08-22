#ifndef PROCEDURESERVER_H
#define PROCEDURESERVER_H

#include <QList>

#include <string>
#include <sstream>

#include <person.h>
#include <account.h>

class ProcedureServer final {
public:
    std::string createPerson(const std::string& name,
                             const int& age);
    std::string readPerson(const std::string& name);
    std::string updatePerson(const std::string& old_name,
                             const std::string& new_name,
                             const int& new_age);
    std::string deletePerson(const std::string& name);

    std::string listPerson();

    std::string createAccount(const std::string& person_name,
                              const std::string& website);
    std::string readAccount(const std::string& person_name,
                            const std::string& website);
    std::string deleteAccount(const std::string& person_name,
                              const std::string& website);
    std::string listAccount(const std::string& person_name);

    ~ProcedureServer();
private:
    QList<Person *> m_people;
    Person* findPerson(const std::string& name);
    std::string serializePerson(const Person*);
    std::string serializePeople();

    Account* findAccount(const Person* p, const std::string& website);
    std::string serializeAccount(const Account*);
    std::string serializeAccounts(const Person*);
};

#endif // PROCEDURESERVER_H

#include <procedureserver.h>

std::string ProcedureServer::createPerson(const std::string& name,
                                          const int& age){
    Person* p = new Person;
    p->setName(QString::fromStdString(name));
    p->setAge(age);
    m_people << p;
    return name + " added";
}

std::string ProcedureServer::readPerson(const std::string& name) {
    Person* found = findPerson(name);

    if( !found )
        return "Person named " + name + " not found";

    return serializePerson(found);
}

std::string ProcedureServer::updatePerson(const std::string& old_name,
                                          const std::string& new_name,
                                          const int& new_age) {
    Person* found = findPerson(old_name);
    if( !found ) {
        return "Person named " + old_name + " not found";
    }

    found->setName(QString::fromStdString(new_name));
    found->setAge(new_age);
    return old_name + " updated: " + serializePerson(found);
}

std::string ProcedureServer::deletePerson(const std::string& name){
    Person* found = findPerson(name);

    if( !found )
        return "Person named " + name + " not found";

    m_people.removeAll(found);
    found->deleteLater();
    return name + " deleted";
}

std::string ProcedureServer::listPerson() {
    return serializePeople();
}


Person* ProcedureServer::findPerson(const std::string& name) {
    auto found = std::find_if(m_people.begin(), m_people.end(),
    [&](Person* p)->bool{
        if(p->name().toStdString() == name)
            return true;
        return false;
    });
    if(found == m_people.end() )
        return nullptr;
    return *found;
}

std::string ProcedureServer::serializePerson(const Person* p) {
    std::ostringstream oss;
    oss << p->name().toStdString() << ", " << p->age();
    return oss.str();
}

std::string ProcedureServer::serializePeople() {
    std::ostringstream oss;
    std::for_each(m_people.begin(), m_people.end(),
    [&](Person* p){
        oss << serializePerson(p);
        if( p != *(m_people.end()-1) ) {
            oss << "; ";
        }
    });
    return oss.str();
}

std::string ProcedureServer::createAccount(const std::string& person_name,
                                           const std::string& website) {
    Person* found = findPerson(person_name);

    if( !found )
        return "Person named " + person_name + " not found";

    Account* acc = new Account(found);
    QObject::connect(found, &Person::nameChanged, acc, &Account::onNameChanged);
    acc->setWebsite(QString::fromStdString(website));
    acc->setLink(found->name());
    return "Added account at " + website + " for " + person_name;
}

std::string ProcedureServer::readAccount(const std::string& person_name,
                                         const std::string& website){
    Person* found_p = findPerson(person_name);
    if ( !found_p )
        return "Person named " + person_name + " not found";
    Account* found_a = findAccount(found_p, website);
    if ( !found_a )
        return "Person named " + person_name +
               " doesn't have an account at " + website;
    return serializeAccount(found_a);
}

std::string ProcedureServer::deleteAccount(const std::string& person_name,
                                           const std::string& website){
    Person* found_p = findPerson(person_name);
    if ( !found_p )
        return "Person named " + person_name + " not found";
    Account* found_a = findAccount(found_p, website);
    if ( !found_a )
        return "Person named " + person_name +
               " doesn't have an account at " + website;
    found_a->deleteLater();
    return person_name + "'s account at " + website + " has been deleted";
}

std::string ProcedureServer::listAccount(const std::string& person_name){
    Person* found_p = findPerson(person_name);
    if ( !found_p )
        return "Person named " + person_name + " not found";
    return serializeAccounts(found_p);
}

Account* ProcedureServer::findAccount(const Person * p,
                                      const std::string& website) {
    auto found = std::find_if(p->children().begin(), p->children().end(),
    [&](QObject* obj)->bool{
        Account* acc = qobject_cast<Account* >(obj);
        if( acc && acc->website().toStdString() == website) {
            return true;
        }
        return false;
    });
    if( found != p->children().end() )
        return qobject_cast<Account* >(*found);
    return nullptr;
}

std::string ProcedureServer::serializeAccount(const Account* a) {
    std::stringstream oss;
    oss << a->link().toStdString() + "@" + a->website().toStdString();
    return oss.str();
}

std::string ProcedureServer::serializeAccounts(const Person* p) {
    std::stringstream oss;
    std::for_each(p->children().begin(), p->children().end(),
    [&](QObject* obj){
        Account* a = qobject_cast<Account* >(obj);
        if ( a ) {
            oss << a->link().toStdString() + "@" + a->website().toStdString();
            if( obj != *(p->children().end()-1) ) {
                oss << "; ";
            }
        }
    });
    return oss.str();
}

ProcedureServer::~ProcedureServer() {
    qDeleteAll(m_people.begin(), m_people.end());
}

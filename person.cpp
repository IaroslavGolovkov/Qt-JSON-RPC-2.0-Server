#include <person.h>
#include <iostream>

#include <QVariant>

Person::Person(QObject *parent) : QObject(parent){}
Person::~Person() {
    std::cout << __func__ << std::endl;
}

QString& Person::name() { return m_name; };
QString Person::name() const { return m_name; };
void Person::setName(const QString& name) {
    m_name = name;
    Q_EMIT nameChanged(name);
};

int& Person::age() { return m_age; };
int Person::age() const { return m_age; };
void Person::setAge(const int& age) { m_age = age; };

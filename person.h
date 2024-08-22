#ifndef PERSON_H
#define PERSON_H

#include <QObject>
#include <QString>

class Person : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int age READ age WRITE setAge)
public:
    explicit Person(QObject* parent = nullptr);
    ~Person();

    QString& name();
    QString name() const;
    void setName(const QString&);

    int& age();
    int age() const;
    void setAge(const int&);

    Q_SIGNAL void nameChanged(const QString& new_name);

private:
    QString m_name{};
    int m_age{0};
};

#endif // PERSON_H

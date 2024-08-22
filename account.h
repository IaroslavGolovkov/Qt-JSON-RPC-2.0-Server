#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QObject>
#include <QString>

class Account : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString website READ website WRITE setWebsite)
    Q_PROPERTY(QString link READ link WRITE setLink)
public:
    explicit Account(QObject* parent);
    ~Account();

    QString& website();
    QString website() const;
    void setWebsite(const QString&);

    QString& link();
    QString link() const;
    void setLink(const QString&);

    Q_SLOT void onNameChanged(const QString& new_name);

private:
    QString m_website;
    QString m_link;
};

#endif // ACCOUNT_H

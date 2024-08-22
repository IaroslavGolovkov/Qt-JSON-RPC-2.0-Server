#include <account.h>
#include <iostream>
#include <QVariant>

Account::Account(QObject* parent) : QObject(parent){}
Account::~Account() {
    std::cout << __func__ << std::endl;
}

QString& Account::website() { return m_website; };
QString Account::website() const { return m_website; };
void Account::setWebsite(const QString& website) { m_website = website; };

QString& Account::link() { return m_link; };
QString Account::link() const { return m_link; };
void Account::setLink(const QString& link) { m_link = link.toLower(); };

Q_SLOT void Account::onNameChanged(const QString& new_name) {
    setProperty("link", new_name.toLower());
}

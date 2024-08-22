#ifndef SOCKETDISPATCHER_H
#define SOCKETDISPATCHER_H

#include <QObject>
#include <QList>
#include <QByteArray>

#include "procedureserver.h"
#include "jsonrpccxx/server.hpp"

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

using namespace jsonrpccxx;

/**
 * @brief Диспетчер сокетов
 * Устанавливает/закрывает соединения
 * Отправляет сообщения на обработку
 */
class SocketDispatcher : public QObject
{
    Q_OBJECT
public:
    explicit SocketDispatcher(quint16 port,
                              bool debug = false,
                              QObject *parent = nullptr);
    ~SocketDispatcher();

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onNewConnection();
    void processRequest(QString);
    void socketDisconnected();

private:
    JsonRpc2Server rpcServer;
    ProcedureServer procServer;
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
    bool m_debug;
};

#endif //SOCKETDISPATCHER_H

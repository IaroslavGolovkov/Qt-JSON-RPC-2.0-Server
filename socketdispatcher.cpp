#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include <QtCore/QDebug>

#include "socketdispatcher.h"

QT_USE_NAMESPACE

SocketDispatcher::SocketDispatcher(quint16 port, bool debug, QObject *parent) :
    QObject(parent),
    m_pWebSocketServer(new QWebSocketServer(
        QStringLiteral("Echo Server"), QWebSocketServer::NonSecureMode, this)),
    m_debug(debug)
{
    if (m_pWebSocketServer->listen(QHostAddress::Any, port)) {
        if (m_debug)
            qDebug() << "Echoserver listening on port" << port;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &SocketDispatcher::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::closed,
                this, &SocketDispatcher::closed);
    }
    rpcServer.Add("createPerson", GetHandle(
                      &ProcedureServer::createPerson, procServer), {});
    rpcServer.Add("readPerson", GetHandle(
                      &ProcedureServer::readPerson, procServer), {});
    rpcServer.Add("updatePerson", GetHandle(
                      &ProcedureServer::updatePerson, procServer), {});
    rpcServer.Add("deletePerson", GetHandle(
                      &ProcedureServer::deletePerson, procServer), {});
    rpcServer.Add("listPerson", GetHandle(
                      &ProcedureServer::listPerson, procServer), {});

    rpcServer.Add("createAccount", GetHandle(
                      &ProcedureServer::createAccount, procServer), {});
    rpcServer.Add("readAccount", GetHandle(
                      &ProcedureServer::readAccount, procServer), {});
    rpcServer.Add("deleteAccount", GetHandle(
                      &ProcedureServer::deleteAccount, procServer), {});
    rpcServer.Add("listAccount", GetHandle(
                      &ProcedureServer::listAccount, procServer), {});
}

SocketDispatcher::~SocketDispatcher()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

/**
 * @brief Обработка нового подключения
 */
void SocketDispatcher::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived,
            this, &SocketDispatcher::processRequest);
    connect(pSocket, &QWebSocket::disconnected,
            this, &SocketDispatcher::socketDisconnected);

    m_clients << pSocket;
}

/**
 * @brief (SLOT) Обработка принятого сообщения от WebSocket'а (SIGNAL)
 * @param message
 */
void SocketDispatcher::processRequest(QString request)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << "Message received:" << request;

    QString reply =
        QString::fromStdString(rpcServer.HandleRequest(request.toStdString()));

    if (pClient) {
        pClient->sendTextMessage(reply);
    }
}

/**
 * @brief Обработка отключения сокета
 */
void SocketDispatcher::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << "socketDisconnected:" << pClient;
    if (pClient) {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}

/**************************************************************************
 *   文件名	：modemanager.h
 *   =======================================================================
 *   创 建 者	：
 *   创建日期	：2024-3-28
 *   邮   箱	：499131808@qq.com
 *   Q Q		：499131808
 *   公   司      ：
 *   功能描述      ：
 *   使用说明 ：任何人或机构要使用、修改、发布本源代码,都必须要获得的授权
 *   ======================================================================
 *   修改者	：
 *   修改日期	：
 *   修改内容	：
 *   ======================================================================
 *
 ***************************************************************************/
#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QRemoteObjectNode>
#include <QSharedPointer>
#include <qremoteobjectabstractitemmodelreplica.h>

class ModeManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    ModeManager(const QUrl &url, const QString &name, QObject *parent = nullptr);
    Q_PROPERTY(QAbstractItemModelReplica *replical READ replical NOTIFY replicalChanged)
    Q_PROPERTY(QRemoteObjectDynamicReplica *dynamicReplical READ dynamicReplical NOTIFY
                   dynamicReplicalChanged FINAL)

    QAbstractItemModelReplica *replical();

    QRemoteObjectDynamicReplica *dynamicReplical() const;

signals:
    void replicalChanged();

    void dynamicReplicalChanged();

private:
    QRemoteObjectNode m_node;
    QAbstractItemModelReplica *m_replical = nullptr;
    QRemoteObjectDynamicReplica *m_dynamicReplical = nullptr;
};

/**************************************************************************
 *   文件名	：hosttest.cpp
 *   =======================================================================
 *   创 建 者	：
 *   创建日期	：2024-3-29
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
#include "hosttest.h"

HostTest::HostTest(QObject *parent)
    : QObject{parent}
{
    // qRegisterMetaType<QList<Data *>>();
    // qRegisterMetaType<QList<Data>>();
    // qRegisterMetaType<Data>("Data");
    // qRegisterMetaType<const Data *>("const Data *");
    // qRegisterMetaType<Data>();
    // qmlRegisterType<Data>("Data", 1, 0, "Data");

    QUrl url("local:tugs");
    m_host.reset(new QRemoteObjectHost(url));
    QVector<int> roles;
    roles << Qt::UserRole + 1 << Qt::UserRole + 2 << Qt::UserRole + 3 << Qt::UserRole + 4
          << Qt::UserRole + 5;
    m_host->enableRemoting(&m_dataModel, QStringLiteral("TiQmlObjectListModel"), roles);
    m_dataModel.append(Actor("111,"));
    m_dataModel.append(Actor("222,"));
    m_dataModel.append(Actor("333,"));

    m_myVar = QVariant::fromValue(Data("aaa", 143));
    emit myVarChanged();
    Actor actor;
    actor.setName("ActorName11111");
    m_actor = QVariant::fromValue(actor);
    ActorO actorO;
    actorO.setName("actorOName11111");
    m_actorO = QVariant::fromValue(actorO);
}

QVariant HostTest::myVar() const
{
    return m_myVar;
}

// QDataStream &operator<<(QDataStream &out, const Message &myObj)
// {
//     out << myObj.body();
//     return out;
// }

QVariant HostTest::actor() const
{
    return m_actor;
}

QVariant HostTest::actorO() const
{
    return m_actorO;
}

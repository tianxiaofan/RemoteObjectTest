/**************************************************************************
 *   文件名	：modemanager.cpp
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
#include "modemanager.h"

ModeManager::ModeManager(const QUrl &url, const QString &name, QObject *parent)
    : QObject(parent)
{
    // qRegisterMetaType<Data>();
    // qRegisterMetaType<Data *>();
    // qmlRegisterType<Data>("Data", 1, 0, "Data");
    m_node.connectToNode(url);
    // m_node.reset(new QRemoteObjectNode(url));
    m_node.setHeartbeatInterval(1000);
    m_replical = m_node.acquireModel(name);
    m_dynamicReplical = m_node.acquireDynamic(name);
    connect(m_dynamicReplical,
            &QRemoteObjectDynamicReplica::initialized,
            this,
            &ModeManager::dynamicReplicalChanged);
}

QAbstractItemModelReplica *ModeManager::replical()
{
    return m_replical;
}

QRemoteObjectDynamicReplica *ModeManager::dynamicReplical() const
{
    return m_dynamicReplical;
}

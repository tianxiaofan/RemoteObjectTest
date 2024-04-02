/**************************************************************************
 *   文件名	：hosttest.h
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
#pragma once

#include <QAbstractListModel>
#include <QColor>
#include <QDataStream>
#include <QDebug>
#include <QObject>
#include <QPoint>
#include <QQmlEngine>
#include <QRemoteObjectHost>

class Data : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    Data() { setObjectName("Data"); }
    Data(const QString &name, int id)
        : m_name(name)
        , m_id(id)
    {
        setObjectName("Data");
    }
    Data(const Data &other)
        : m_name(other.m_name)
        , m_id(other.m_id)
    {
        setObjectName("Data");
    }
    ~Data() {}
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged FINAL)
    QString name() const { return m_name; }

    int id() const { return m_id; }
    // = 操作符重载
    Data &operator=(const Data &other)
    {
        setObjectName(other.objectName());
        m_name = other.m_name;
        m_id = other.m_id;
        return *this;
    }

    friend QDataStream &operator<<(QDataStream &out, const Data &data)
    {
        out << data.m_name << data.m_id;
        return out;
    }
    friend QDataStream &operator>>(QDataStream &in, Data &data)
    {
        in >> data.m_name >> data.m_id;
        return in;
    }
#if 0
        // friend QDataStream &operator<<(QDataStream &out, const Data *data)
        // {
        //     out << data->m_name << data->m_id;
        //     return out;
        // }

        // friend QDataStream &operator>>(QDataStream &in, Data *data)
        // {
        //     in >> data->m_name >> data->m_id;
        //     return in;
        // }
#endif
    friend QDebug operator<<(QDebug dbg, const Data &data)
    {
        dbg.nospace() << "Data(" << data.m_name << ", " << data.m_id << ")";
        return dbg.space();
    }

public slots:
    void setName(QString name)
    {
        if (m_name == name)
            return;

        m_name = name;
        emit nameChanged();
    }

    void setId(int id)
    {
        if (m_id == id)
            return;

        m_id = id;
        emit idChanged();
    }

signals:
    void nameChanged();
    void idChanged();

private:
    QString m_name;
    int m_id;
};
Q_DECLARE_METATYPE(Data)

class Actor
{
    Q_GADGET
    Q_PROPERTY(QString name READ name WRITE setName)
public:
    Actor() {}
    Actor(const QString &name)
        : m_name(name)
    {}
    QString name() const { return m_name; }
    void setName(const QString &name) { m_name = name; }

    friend QDataStream &operator<<(QDataStream &out, const Actor &actor)
    {
        out << actor.m_name;
        return out;
    }
    friend QDataStream &operator>>(QDataStream &in, Actor &actor)
    {
        in >> actor.m_name;
        return in;
    }

private:
    QString m_name;
};
Q_DECLARE_METATYPE(Actor)
class MyDataModel : public QAbstractListModel
{
    Q_OBJECT
    // QAbstractItemModel interface
public:
    MyDataModel() {}
    enum ArrowRoles {
        objectname = Qt::UserRole + 1,
        object,
        object_pointer,
        object_name,
        object_id
    };
    int rowCount(const QModelIndex &parent = QModelIndex()) const override
    {
        return m_data.count();
    }
    QVariant data(const QModelIndex &index, int role) const override
    {
        if (!index.isValid())
            return QVariant();
        if (index.row() < 0 || index.row() >= m_data.count())
            return QVariant();
        switch (role) {
        // case objectname:
        //     return QVariant(m_data[index.row()].objectName());
        case object: {
            // Message data = *m_data.at(index.row());
            return QVariant::fromValue(m_data.at(index.row()));
        }
        // case object_pointer:
        //     return QVariant::fromValue(m_data.at(index.row()).data());
        // case object_name:
        //     return QVariant::fromValue((m_data[index.row()])->name());
        // case object_id:
        //     return QVariant::fromValue(m_data[index.row()]->id());
        default:
            return QVariant();
        }
        return QVariant();
    }
    void append(const Actor &data)
    {
        const int rowOfInsert = m_data.count();
        beginInsertRows(QModelIndex(), rowOfInsert, rowOfInsert);
        m_data.append(data);
        endInsertRows();
    }
    void clearArrow()
    {
        beginResetModel();
        m_data.clear();
        endResetModel();
    }

protected:
    // QAbstractItemModel interface
    QHash<int, QByteArray> roleNames() const override
    {
        static QHash<int, QByteArray> roles;
        roles[objectname] = "objectname";
        roles[object] = "object";
        roles[object_pointer] = "object_pointer";
        roles[object_name] = "object_name";
        roles[object_id] = "object_id";
        return roles;
    }

private:
    QList<Actor> m_data;
};

class ActorO : public QObject
{
    Q_OBJECT
public:
    ActorO() {}
    ActorO(const ActorO &actor)
        : m_name(actor.m_name)
    {}
    ActorO &operator=(const ActorO &other)
    {
        m_name = other.m_name;
        return *this;
    }

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    QString name() const { return m_name; }
    void setName(const QString &name)
    {
        m_name = name;
        emit nameChanged();
    }
signals:
    void nameChanged();

private:
    QString m_name;
};

class HostTest : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit HostTest(QObject *parent = nullptr);
    Q_PROPERTY(MyDataModel *customMode READ customMode CONSTANT)
    Q_PROPERTY(QVariant myVar READ myVar NOTIFY myVarChanged FINAL)
    Q_PROPERTY(QVariant actor READ actor NOTIFY actorChanged FINAL)
    Q_PROPERTY(QVariant actorO READ actorO NOTIFY actorOChanged FINAL)

    MyDataModel *customMode() const { return const_cast<MyDataModel *>(&m_dataModel); }

    QVariant myVar() const;

    QVariant actor() const;

    QVariant actorO() const;

signals:

    void myVarChanged();

    void actorChanged();

    void actorOChanged();

private:
    MyDataModel m_dataModel;
    QSharedPointer<QRemoteObjectHost> m_host;
    QVariant m_myVar;
    QVariant m_actor;
    QVariant m_actorO;
};
// Q_DECLARE_TYPEINFO(Data, Q_RELOCATABLE_TYPE);

// Q_DECLARE_OPAQUE_POINTER(Data *)

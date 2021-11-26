#ifndef MANAGERMODELS_H
#define MANAGERMODELS_H


#include <QObject>
#include <QAbstractListModel>
#include <QFileInfo>
#include <QDir>
#include <QDebug>
#include <QtCore>

class Manager : public QObject
{
    Q_OBJECT
public:
    //explicit Manager(QObject *parent = nullptr);
    Manager();
    Manager(const QString &name);
    Manager(const QString &name,const int &image);
    virtual ~Manager();
    const QString &name() const;
    void setName(const QString &name);

    const int &image() const;
    void setImage(const int &image);

private:
    QString m_name;//
    int m_image;//
};

class ManagerModels: public QAbstractListModel
{
     Q_OBJECT
public:

    explicit ManagerModels(QObject *parent = nullptr);
    ~ManagerModels();

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int,QByteArray> roleNames() const;
    enum Manager_Role{
        manager_name_role,
        manager_image_role
    };
    enum Icon{
        file,
        folder
    };
    void pathData(const QString &path);
    void addData(Manager * manager);
    void findData( QString path,const QString &text);
public slots:
    void changeData(int index);
    void find(const QString &text);
private:
    QList<Manager*> m_data;
    QString m_pathF;
};


#endif // MANAGERMODELS_H

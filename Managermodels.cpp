#include "Managermodels.h"

Manager::Manager(const QString &name)
{
    m_name = name;
}

Manager::Manager(const QString &name, const int &image)
{
    m_name = name;
    m_image = image;
}
Manager::~Manager()
{}

const QString &Manager::name() const
{
    return m_name;
}

void Manager::setName(const QString &name)
{
    m_name = name;
}

const int &Manager::image() const //getImage
{
    return m_image;
}

void Manager::setImage(const int &image)
{
    m_image = image;
}

ManagerModels::ManagerModels(QObject *parent) : QAbstractListModel(parent)
{
    m_pathF = "F:/FileManager";
    pathData(m_pathF);
}

ManagerModels::~ManagerModels()
{
    for(Manager* var : m_data)
    {
        delete var;
    }
}

int ManagerModels::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_data.count();

}

QVariant ManagerModels::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row <0 || row >= m_data.count()){
        return QVariant();
    }
    switch(role){
    case manager_name_role:
        return m_data[row]->name();
    case manager_image_role:
        if(m_data[row]->image() == file){
          //  qDebug() << "File";
            return "qrc:images/file.png";
        }
        else{
        return "qrc:images/folder.png";
        }
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ManagerModels::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[manager_name_role] = "manager_name";
    roles[manager_image_role] = "manager_image";
    return roles;
}

void ManagerModels::pathData(const QString &path)
{
//  qDebug() << __FUNCTION__ << __LINE__;
   qDebug() <<__LINE__<< "path" << path;
   QDir dirObj(path);

   for(QFileInfo var : dirObj.entryInfoList(QDir::AllDirs | QDir::Files |QDir::NoDotAndDotDot))
   {
       Manager * obj = nullptr ;
       if(var.isFile() == true)
       {
           qDebug() << "inside File";
          /*Manager * */obj = new Manager(var.fileName(),file);

       }
       else/*if(var.isDir())*/{
          // qDebug() << "inside Folder";
          /* Manager * */obj =  new Manager(var.fileName(),folder);

       }
       addData(obj);
   }
}

void ManagerModels::addData(Manager *manager)
{
    beginResetModel();
    m_data.append(manager);
    endResetModel();
}

void ManagerModels::findData( QString path,const QString &text)
{
//    int flag = 0;
    Manager *managerObj= nullptr;
    QDir dir(path);
    for(QFileInfo var : dir.entryInfoList(QDir::AllDirs | QDir::Files |QDir::NoDotAndDotDot))
    {
        if(var.isFile()){
           if(var.fileName() == text)
             {
               path = path +"/"+var.fileName();
               managerObj = new Manager(path);
               addData(managerObj);
             }
        }
        else if(var.isDir()){
            if(var.fileName() == text){
             //  qDebug() << __FUNCTION__ << "Folder";
               path = path +"/"+var.fileName();
               managerObj = new Manager(path);
               addData(managerObj);
              }
//              qDebug()  <<"path " << path + "/" + var.fileName();
              findData(path + "/" + var.fileName(),text);
            }
        }
//    if(flag == 1){
//        m_data.clear();
//        qDebug() << path;
//        pathData(path);
//        qDebug() <<__LINE__ <<"RIGHT";
//        flag = 0;
//    }else{
//    qDebug() << __LINE__ <<"FALL";
//    }
//    return;

//    }else{
//       for(int i =0;i <folder.size();i++)
//       {
//           qDebug() <<__LINE__ << path+"/"+folder.at(i);
//           findData(path+"/"+folder.at(i),text);
//           if(i> folder.size()){
//               break;
//           }
//       }
//       qDebug() << __LINE__ <<"FALL";
//       return;
//    }
  }

void ManagerModels::changeData(int index)
{
    QString path;
    if(index <0 || index >m_data.count())
    {
        return;
    }
    if(m_data.at(index)->name().contains("/"))
    {
        path = m_data.at(index)->name();
    }
    else{

        path = m_pathF + "/" + m_data.at(index)->name();}
    QFileInfo fileInfo(path);
    if(fileInfo.isDir()== true){
         m_pathF = path;
         if(m_data.isEmpty() != true){
               m_data.clear();
         pathData(m_pathF);
         }
    }
    else{

        Manager *obj = new Manager(fileInfo.fileName(),file);
        m_data.clear();
        addData(obj);
    }
//    QFileInfo fileInfo(path);
//    if(fileInfo.isDir()== true){
//      m_pathF = path;
//    }
//    if(m_data.isEmpty() != true){
//          m_data.clear();
//    pathData(m_pathF);
//    }
}

void ManagerModels::find(const QString &text)
{
    m_data.clear();
    m_pathF = "F:/FileManager";
    qDebug() << __FUNCTION__ << __LINE__<< m_pathF;
    findData(m_pathF,text);
    if(!m_data.isEmpty())
    {
        for(Manager *obj : m_data)
        {
            qDebug() << obj->name();
        }
    }
}

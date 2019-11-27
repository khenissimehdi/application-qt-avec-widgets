#ifndef IMAGELIBRARY_H
#define IMAGELIBRARY_H
#define THUMBNAIL_SIZE 128 /*taille de iamge*/
#include <QFileDialog>
#include <QStringListModel>
#include <QMainWindow>
#include <QListView>
#include <QToolBar>
#include <QAction>
#include <QDir>
#include <QMessageBox>
#include <QVariant>
#include <QSettings>
#include <QStringList>
#include <QFileInfo>
#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include <QImage>
#include <QAbstractListModel>
class Item// : public QObject
{
//    Q_OBJECT


public:
    QString path;
    QImage thumbnail;
    Item (const QString &, const QImage &);

};
class  Model : public QAbstractListModel
{

 private:
    QList<Item> items;
  public:
    int rowCount(const QModelIndex &)const;
    QVariant data(const QModelIndex  &,int)const;
    Model ();
    void addItem(const Item & );
    void setThumbnail();
    //void beginInsertRows(const QModelIndex &,int ,int);
    //void endInsertRows();

};

class ImageLibrary : public QMainWindow
{
    Q_OBJECT

private:
    Model model;
    QListView view ;
    QToolBar toolbar;



public:
    ImageLibrary(QWidget *parent = nullptr);
    ~ImageLibrary();
    void go();
    //void addItem (const QString & ,const QImage &);
    void addItem (const QString &);
};

class Worker : public QObject
{
    Q_OBJECT

private:
    QString path;
    QFutureWatcher<Item> watcher;
    QFuture<Item> future;


public:


    Worker (const QString &);

    void process();
    static QImage Thumbnail(const QString&);
    static Item MappedItem(const QString &);
    void processItem(int );
signals:
    //void newItem(const QString & ,const QImage);
    void newItem(const Item);
    void finished();
    void newThumbnail();

};





#endif // IMAGELIBRARY_H

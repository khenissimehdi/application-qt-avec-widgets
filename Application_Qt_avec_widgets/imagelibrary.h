#ifndef IMAGELIBRARY_H
#define IMAGELIBRARY_H
<<<<<<< HEAD
#define THUMBNAIL_SIZE 128 /*taille de iamge*/
=======
>>>>>>> 5879228613ee131dfa84903d838298fb427b9d16
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
    void addItem(const QString & ,const QImage & );
    //void beginInsertRows(const QModelIndex &,int ,int);
    //void endInsertRows();

};

=======
>>>>>>> 5879228613ee131dfa84903d838298fb427b9d16
class ImageLibrary : public QMainWindow
{
    Q_OBJECT

private:
<<<<<<< HEAD
    Model model;
=======
    QStringListModel model;
>>>>>>> 5879228613ee131dfa84903d838298fb427b9d16
    QListView view ;
    QToolBar toolbar;



public:
    ImageLibrary(QWidget *parent = nullptr);
    ~ImageLibrary();
    void go();
    void addItem (const QString & );
};

class Worker : public QObject
{
    Q_OBJECT

private:
    QString path;

public:
    Worker (const QString &);
    void process();
<<<<<<< HEAD
    static QImage Thumbnail(const QString&);

signals:
    void newItem(const QString & ,const QImage);
    void finished();
};





=======

signals:
    void newItem(const QString &);
    void finished();
};
>>>>>>> 5879228613ee131dfa84903d838298fb427b9d16
#endif // IMAGELIBRARY_H

#ifndef IMAGELIBRARY_H
#define IMAGELIBRARY_H
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
class ImageLibrary : public QMainWindow
{
    Q_OBJECT

private:
    QStringListModel model;
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

signals:
    void newItem(const QString &);
    void finished();
};
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
    Model (const QList<Item> &);
    addItem(const QString & );


};
#endif // IMAGELIBRARY_H

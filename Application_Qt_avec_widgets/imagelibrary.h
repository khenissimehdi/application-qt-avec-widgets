#ifndef IMAGELIBRARY_H
#define IMAGELIBRARY_H
#include <QStringListModel>
#include <QListView>
#include <QToolBar>
#include <QMainWindow>
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QVariant>
#include <QSettings>
#include <QStringList>
#include <QFileInfo>
#include <QDir>






class ImageLibrary : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImageLibrary(QWidget *parent = 0);//when we have we have a form we use explicit(but here we dun have don't panic)
    ~ImageLibrary();
    void go();

private:
    QStringListModel  model;
    QListView  view ;
    QToolBar toolbar;




};
class Worker : public QObject
{
    Q_OBJECT
public:
    Worker(const QString &);
    void process();
signals:
    void newItem(QString &);
private:
    QString path ;

};

#endif // IMAGELIBRARY_H

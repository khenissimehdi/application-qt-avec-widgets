#ifndef IMAGELIBRARY_H
#define IMAGELIBRARY_H
#include <QStringListModel>
#include <QListView>
#include <QToolBar>
#include <QMainWindow>
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>




class ImageLibrary : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImageLibrary(QWidget *parent = 0);
    ~ImageLibrary();
    void go();

private:
    QStringListModel  model;
    QListView  view ;
    QToolBar toolbar;




};

#endif // IMAGELIBRARY_H

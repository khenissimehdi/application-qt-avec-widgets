#include "imagelibrary.h"



ImageLibrary::ImageLibrary(QWidget *parent) :QMainWindow(parent),model(parent), view(parent), toolbar(parent)
{

    view.setModel(&model);
    toolbar.addAction ("Its Alive !!", this, & ImageLibrary::go);
    addToolBar(&toolbar);
    setCentralWidget(&view);






}


Worker::Worker(const QString & path):path(path)
{
}

void Worker::process()
{

    QStringList list;
    list.append(path);

    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.jpeg";

    while(!(list.isEmpty()))
    {
        QFileInfo x = list[0];
        if(x.isDir())
        {
            QDir chemin = list[0];
            //chemin.setNameFilters(filters);
            QList<QFileInfo> petiteListe = chemin.entryInfoList();
            foreach (QFileInfo val, petiteListe)
            {
                if(val.isDir())
                {
                    list.append(val.absoluteFilePath());

                }

                /*if(val == "*.png")
                {
                    list.append(val.absoluteFilePath());

                }*/



            }
        }
        else
        {
            QString val = x.absoluteFilePath();
            emit newItem(val);
        }

        list.removeFirst();
    }

}

void ImageLibrary::go()
{

    QSettings settings;
    QString newDir=settings.value("", QDir::homePath()).toString();

    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    newDir,
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);


    if(dir.isEmpty())
    {
        QMessageBox::warning(this,"warning","Dir is empty ");
    }
    else
    {
        settings.setValue("",dir);




        QMessageBox::information(this, "Bravo", dir);

        //QSettings::settings.value(dir);

    }
     Worker worker(dir);
     QObject::connect(&worker,&Worker::newItem,this,&ImageLibrary::addItem);
     worker.process();





}
ImageLibrary::~ImageLibrary()
{

}
void ImageLibrary::addItem (const QString & item)
   {
     QStringList list = model.stringList ();
      model.setStringList (list << item);
    }

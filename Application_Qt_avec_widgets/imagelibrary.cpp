#include "imagelibrary.h"


ImageLibrary::ImageLibrary(QWidget *parent):QMainWindow(parent),model(parent),view(parent),toolbar(parent)
{
    view.setModel(&model);
    toolbar.addAction ("GO !", this, & ImageLibrary::go);
    addToolBar(&toolbar);
    setCentralWidget(&view);
}
void ImageLibrary::go()
{
    QSettings content;//we set up our QSettings object
    QString newDir = content.value("",QDir::homePath()).toString();//we set upa new dir by putting the value of homepath in content and setting it to newdir



    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    newDir,//we put our predefinded variable in his place its replaces Qdir::homePATH()
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    if(dir.isEmpty())
       {
           QMessageBox::warning(this,"warning","Dir is empty ");
       }
       else
       {
           content.setValue("",dir);//we save the dir where we was in content to replace it with homepath()
           QMessageBox::information(this, "Bravo", dir,QMessageBox::Yes);
           //QSettings::settings.value(dir);

       }
   /*
        Worker worker(dir);
        QObject::connect(&worker,&Worker::newItem,this,&ImageLibrary::addItem);
        worker.process();
        */

    //QThread * thread = new QThread;
    Worker * worker = new Worker (dir);
    /*
    worker->moveToThread (thread);
    connect (thread, &QThread::started, worker, &Worker::process);
    connect (worker, &Worker::finished, thread, &QThread::quit);
    connect (worker, &Worker::finished, worker, &Worker::deleteLater);
    connect (thread, &QThread::finished, thread, &QThread::deleteLater);
    */
    connect(worker,&Worker::newItem,this,&ImageLibrary::addItem);
    //thread->start ();
    QtConcurrent::run([worker](){worker->process();});



}
void ImageLibrary::addItem (const QString & item)
{
  QStringList list = model.stringList ();
  model.setStringList (list << item);
}
Worker::Worker(const QString & path):path(path){

}

//Worker:: ~Worker(){}






void Worker::process()
{


    QStringList list;//create a list
    list.append(path);//add path to the list

    //QStringList filters;//create a filter
    //filters << "*.png" << "*.jpg" << "*.jpeg";

    while(!(list.isEmpty()))
    {
        QFileInfo x = list[0];
        if(x.isDir())
        {
            QDir chemin = list[0];
            //chemin.setNameFilters(filters);
            QList<QFileInfo> petiteListe = chemin.entryInfoList();
            petiteListe.removeAt(0);
            petiteListe.removeAt(0);

            foreach (QFileInfo val, petiteListe)
            {
                QFileInfo fi(val);
                QString ext = fi.suffix();
                if(val.isDir())
                {
                   path=val.absoluteFilePath();
                   process();
                }

                else if (val.isFile() and (ext=="png" or ext=="jpg" or ext=="jpeg")){
                    list.append(val.absoluteFilePath());

                }
            }
        }
        else
        {
            QString val = x.absoluteFilePath();
            emit newItem(val);
        }

        list.removeFirst();
    }
    emit finished();
}


ImageLibrary::~ImageLibrary()
{
}


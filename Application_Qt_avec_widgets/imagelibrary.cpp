#include "imagelibrary.h"


ImageLibrary::ImageLibrary(QWidget *parent):QMainWindow(parent),model(),view(parent),toolbar(parent)
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
    connect(worker,&Worker::newItem,&model,&Model::addItem);
    //thread->start ();
    QtConcurrent::run([worker](){worker->process();});



}
void ImageLibrary::addItem (const QString & item)
{
  //QStringList list = model.stringList ();
  //model.setStringList (list << item);
}
Worker::Worker(const QString & path):path(path){

}

//Worker:: ~Worker(){}






void Worker::process()
{


    QStringList list;//create a list
    list.append(path);//add path to the list
    connect(&watcher,&QFutureWatcher<Item>::resultReadyAt,this,&Worker::processItem);
    //QStringList filters;//create a filter
    //filters << "*.png" << "*.jpg" << "*.jpeg";

    while(!(list.isEmpty()))
    {
        QFileInfo x = list[0];
        QDir chemin = list[0];
        //chemin.setNameFilters(filters);
        QList<QFileInfo> petiteListe = chemin.entryInfoList();
        if(x.isDir())
        {

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
         //QList<QFileInfo> liste=petiteListe;
        }
        else
        {


            /*QString val = x.absoluteFilePath();
            QImage image =Thumbnail(val);
            emit newItem(val,image);
            */
            future=QtConcurrent::mapped(petiteListe,MappedItem);
            watcher.setFuture(future);
            watcher.waitForFinished();        }

        list.removeFirst();
    }
    emit finished();
}

Item::Item (const QString  & path, const QImage & thumbnail):path(path),thumbnail(thumbnail)
{
}
/*
 *Class Model
*/
Model::Model(){}

int Model::rowCount(const QModelIndex & parent)const{
    if(parent.isValid())
    {
        return 0;
    }
    else{
    return this->items.count();
    }
}
QVariant Model::data(const QModelIndex  & index,int role)const{
    if (index.isValid()){
        switch(role){
            case Qt::ToolTipRole:
                return items[index.row()].path;
            case Qt::DecorationRole:
                return QPixmap::fromImage(items[index.row()].thumbnail);
            case Qt::SizeHintRole:
                return items[index.row()].thumbnail.size();
            default:
                       return QVariant();

    }
   }
    else
    {
        return QVariant();
    }
}
void Model::addItem(const Item & item)
{    int nbelement = items.size();
     beginInsertRows(QModelIndex(), nbelement,nbelement);
     items.append(item);
     endInsertRows();
    }
/*
void Model::addItem(const QString & path ,const QImage & thumbnail)
{    int nbelement = items.size();
     beginInsertRows(QModelIndex(), nbelement,nbelement);
     items.append(Item(path,thumbnail));
     endInsertRows();
    }*/
QImage Worker::Thumbnail(const QString & path)
{
    QSize size(THUMBNAIL_SIZE,THUMBNAIL_SIZE);
    QImage image (path);
    image = image.scaled(size,Qt::KeepAspectRatio);
    return image;
}
Item Worker::MappedItem(const QString & path)
{
    QImage image(path);
    return Item(path,image);
}
void Worker::processItem(int k)
{
    emit newItem(watcher.resultAt(k));

}
ImageLibrary::~ImageLibrary()
{
}

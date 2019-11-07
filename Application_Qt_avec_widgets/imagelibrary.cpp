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
  QStringList List ;
  QFileInfo file;
  file.setFile(path);

  if(file.isFile())
  {
      List.append(path);


  }
  else
  {
      while(file.isDir())
      {
          List.append(path);

      }

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





}
ImageLibrary::~ImageLibrary()
{

}

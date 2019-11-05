#include "imagelibrary.h"



ImageLibrary::ImageLibrary(QWidget *parent) :QMainWindow(parent),model(parent), view(parent), toolbar(parent)
{

    view.setModel(&model);
    toolbar.addAction ("Its Alive !!", this, & ImageLibrary::go);
    addToolBar(&toolbar);
    setCentralWidget(&view);





}
void ImageLibrary::go()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    QDir::homePath(),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    if(dir.isEmpty())
    {
        QMessageBox::warning(this,"warning","Dir is empty ");
    }
    else
    {
        QMessageBox::information(this, "Bravo", dir);

    }





}
ImageLibrary::~ImageLibrary()
{

}

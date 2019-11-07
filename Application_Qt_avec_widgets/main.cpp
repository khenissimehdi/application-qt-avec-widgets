#include "imagelibrary.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImageLibrary w;
    a.setOrganizationName("khen0002");
    a.setApplicationName("My First App");
    w.show();


    return a.exec();
}

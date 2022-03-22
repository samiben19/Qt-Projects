#include "GUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repository repo;
    Service srv{ repo };
    GUI gui{ srv };
    gui.show();
    return a.exec();
}

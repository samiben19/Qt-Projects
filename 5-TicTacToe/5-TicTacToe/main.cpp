#include "GUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repository repo{ "jocuri.txt" };
    Service srv{ repo };
    GUI g{srv};
    g.show();
    return a.exec();
}

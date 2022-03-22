#include "GUI.h"
#include "tests.h"
#include <QtWidgets/QApplication>

void test()
{
    Tests teste;
    teste.testAll();
}

int main(int argc, char* argv[])
{
    test();
    QApplication a(argc, argv);
    RepositoryFile repo{ "produse.txt" };
    Service srv{ repo };
    GUI* app = new GUI{ srv };
    app->show();
    return a.exec();
}

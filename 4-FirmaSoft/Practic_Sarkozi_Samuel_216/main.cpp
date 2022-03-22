#include <QtWidgets/QApplication>
#include "GUI.h"
#include "Teste.h"

void testare()
{
	Teste teste;
	teste.testAll();
}

//int main()
//{
//	testare();
//	return 0;
//}

int main(int argc, char *argv[])
{
    testare();
    QApplication a(argc, argv);
    Repository repo{ "taskturi.txt" };
    Service srv{ repo };
    GUI g{ srv };
    g.show();
    return a.exec();
}

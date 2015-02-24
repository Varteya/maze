#include <QApplication>
#include <QDesktopWidget>
#include <fstream>
#include "Player.h"
#include "glwidget.h"




int main(int argc, char *argv[])
{
    Field mapField;
    std::ifstream map ("text_map.txt");
    try {
        mapField.readFieldFromFile(map);
    }
    catch (std::exception& e){
        std::cout << e.what() << '\n';
        return 1;
    }

    int x, y;
    map >> x >> y;
    Player p(&mapField, x, y);

    QApplication a(argc, argv);
    GLWidget window(mapField, p);

    window.resize(window.sizeHint());
    int desktopArea = QApplication::desktop()->width() *
                     QApplication::desktop()->height();
    int widgetArea = window.width() * window.height();
    if (((float)widgetArea / (float)desktopArea) < 0.75f)
        window.show();
    else
        window.showMaximized();
    return a.exec();
}

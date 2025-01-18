#include "mydialogue.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    
    MyDialog d;
    d.show();

    return app.exec();
}

#include "mafenetre.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MaFenetre fenetre;
    fenetre.creer_mat();
    fenetre.show();
    return app.exec();
}

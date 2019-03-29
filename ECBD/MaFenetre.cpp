#include "MaFenetre.h"
#include <QFont>

MaFenetre::MaFenetre(QWidget *parent) : QMainWindow(parent){

setFixedSize(1400,825);

m_nom = new QLabel("Nom:", this);
m_nom->setFont(QFont("Helvetica", 12, QFont::Light, true));
m_nom->move(950,50);
m_prenom = new QLabel("Prenom:", this);
m_prenom->setFont(QFont("Helvetica", 12, QFont::Light, true));
m_prenom->move(950,80);
m_fievre = new QLabel("Fièvre", this);
m_fievre->setFont(QFont("Helvetica", 12, QFont::Light, true));
m_fievre->move(600,150);
m_douleur = new QLabel("Douleur", this);
m_douleur->setFont(QFont("Helvetica", 12, QFont::Light, true));
m_douleur->move(740,150);
m_toux = new QLabel("Toux", this);
m_toux->setFont(QFont("Helvetica", 12, QFont::Light, true));
m_toux->move(900,150);
m_val_text = new QLabel("Les valeurs des attributs:", this);
m_val_text->setFont(QFont("Helvetica", 12, QFont::Light, true));
m_val_text->setGeometry(300,208,200,15);


m_nomi = new QLineEdit(this);
m_nomi->setGeometry(1020,56,200,20);
m_prenomi = new QLineEdit(this);
m_prenomi->setGeometry(1020,86,200,20);

m_bou = new QPushButton("Quitter", this);
m_bou->setGeometry(600,400,80,40);
m_predire = new QPushButton("Predire", this);
m_predire->setGeometry(1050,196,100,40);

m_combo_fievre = new QComboBox(this);
m_combo_fievre->setGeometry(550,200,140,30);
m_combo_fievre->addItem("NULL");
m_combo_fievre->addItem("Oui");
m_combo_fievre->addItem("Non");
m_combo_douleur = new QComboBox(this);
m_combo_douleur->setGeometry(700,200,140,30);
m_combo_douleur->addItem("NULL");
m_combo_douleur->addItem("Oui");
m_combo_douleur->addItem("Non");
m_combo_toux = new QComboBox(this);
m_combo_toux->setGeometry(850,200,140,30);
m_combo_toux->addItem("NULL");
m_combo_toux->addItem("Oui");
m_combo_toux->addItem("Non");


connect(m_bou, SIGNAL(clicked()), this, SLOT(setQuitter()));

read_csv(m_mat, m_vet, "data.csv");
}
void MaFenetre::setQuitter(){
exit(0);
}

/*void MaFenetre::creer_combo(int num_col){
    for (int i(0);i<m_mat.size();i++) {
        m_com->addItem(m_mat[i][num_col]):
    }
}*/

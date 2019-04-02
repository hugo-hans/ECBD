#include "mafenetre.h"
#include <QFont>
#include <QHeaderView>
#include <sstream>

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
    m_maladie = new QLabel("Maladie : ", this);
    m_maladie->setFont(QFont("Helvetica", 12, QFont::Light, true));
    m_maladie->setGeometry(650,250,200,20);


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
    m_combo_douleur->addItem("Abdomen");
    m_combo_douleur->addItem("Gorge");
    m_combo_douleur->addItem("Non");
    m_combo_toux = new QComboBox(this);
    m_combo_toux->setGeometry(850,200,140,30);
    m_combo_toux->addItem("NULL");
    m_combo_toux->addItem("Oui");
    m_combo_toux->addItem("Non");

    m_tab = new QTableWidget(this);
    m_tab->setGeometry(199,449,1002,352);
    m_tab->setColumnCount(4);
    m_tab->setRowCount(10);
    for (int i(0);i<4;i++) {
        m_tab->setColumnWidth(i,250);

    }
    for (int i(0);i<10;i++) {
        m_tab->setRowHeight(i,350/10);

    }
    m_tab->verticalHeader()->setVisible(false);
    m_tab->horizontalHeader()->setVisible(false);


    connect(m_bou, SIGNAL(clicked()), this, SLOT(setQuitter()));
    connect(m_predire, SIGNAL(clicked()), this, SLOT(predire()));

    read_csv(m_mat, m_vet, "data.csv");
}
void MaFenetre::setQuitter(){
    exit(0);
}

void MaFenetre::creer_mat(){
    for (unsigned long j(0);j<m_vet.size();j++) {
        m_tab->setItem(0,j,new QTableWidgetItem(m_vet[j].c_str()));
    }

    for (unsigned long i(0);i<m_mat.size();i++) {
        for (unsigned long j(0);j<m_vet.size();j++) {
            m_tab->setItem(i+1,j,new QTableWidgetItem(m_mat[i][j].c_str()));
        }
    }

}

void MaFenetre::score(string maladie, string fievre, string douleur, string toux, vector<double> &Scores, unsigned total){
    double Score;
    double Freq;
    double Conf;
    double Conf_f;
    double Conf_d;
    double Conf_t;
    double cpt0 = 0;
    double cpt1 = 0;
    double cpt2 = 0;
    double cpt3 = 0;
    for (int i(0);i<total;i++) {
        bool t = maladie == m_mat[i][3];
        if(m_mat[i][3] == maladie)++cpt0;
    }
    for (int i(0);i<total;i++) {
        if(m_mat[i][3] == maladie){
            if(fievre != "NULL" && m_mat[i][0] == fievre){
                ++cpt1;
            }
            else if (douleur != "NULL" &&  m_mat[i][1] == douleur) {
                ++cpt2;
            }
            else if (toux != "NULL" &&  m_mat[i][2] == toux) {
                ++cpt3;
            }
        }
    }
    Freq=cpt0/total;
    Conf_f = (cpt1/total)/Freq;
    cout << cpt1<<' ' <<total<<' '<<Freq<<' '<<Conf_f;
    Conf_d = (cpt2/total)/Freq;
    Conf_t = (cpt3/total)/Freq;
    Conf= Conf_f*Conf_d*Conf_t;
    Score=Freq*Conf;
    Scores.push_back(Score);
}

void MaFenetre::predire(){
    string fievre = (m_combo_fievre->currentText()).toStdString();
    string douleur = (m_combo_douleur->currentText().toStdString());
    string toux = (m_combo_toux->currentText().toStdString());
    vector<double> Scores(0,0);
    double total = m_mat.size();
    m_alert = new QMessageBox;
    if(fievre == "NULL" && douleur == "NULL" && toux == "NULL"){
        m_maladie->setText("NULL");
    }
    else {
        for (unsigned i(0);i<5;i++) {
            switch (i) {
            case 0:
                score("Appendicite",  fievre,  douleur,  toux,  Scores,  total);
                break;
            case 1:
                score("Rhume",  fievre,  douleur,  toux,  Scores,  total);
                break;
            case 2:
                score("Mal de gorge",  fievre,  douleur,  toux,  Scores,  total);
                break;
            case 3:
                score("Refroidissement",  fievre,  douleur,  toux,  Scores,  total);
                break;
            case 4:
                score("Aucune",  fievre,  douleur,  toux,  Scores,  total);
                break;
            }
        }
        for (unsigned i(0);i<Scores.size();i++) {
            cout << "Scores["<<i<<"] = "<<Scores[i]<<endl;
        }
        int max =distance(Scores.begin(), max_element(Scores.begin(), Scores.end()));
        switch (max) {
        case 0:
            m_maladie->setText("Maladie : Appendicite");
            break;
        case 1:
            m_maladie->setText("Maladie : Rhume");
            break;
        case 2:
            m_maladie->setText("Maladie : Mal de gorge");
            break;
        case 3:
            m_maladie->setText("Maladie : Refroidissement");
            break;
        case 4:
            m_maladie->setText("Maladie : Aucune");
            break;
        }
    }
}

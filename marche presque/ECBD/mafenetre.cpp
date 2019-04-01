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
    m_tab->setGeometry(199,449,1002,344);
    m_tab->setColumnCount(4);
    m_tab->setRowCount(9);
    for (int i(0);i<4;i++) {
        m_tab->setColumnWidth(i,250);

    }
    for (int i(0);i<9;i++) {
        m_tab->setRowHeight(i,350/9);

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
    for (unsigned long i(0);i<m_mat.size();i++) {
        for (unsigned long j(0);j<m_vet.size();j++) {
            if(i==0){
                m_tab->setItem(0,j+1,new QTableWidgetItem(m_vet[j].c_str()));
            }
            else {
                m_tab->setItem(i,j+1,new QTableWidgetItem(m_mat[i][j].c_str()));
            }

        }
    }
    cout << m_mat.size() << endl;
    cout << m_vet.size() << endl;

}
void MaFenetre::scoreApp(string fievre, string douleur, string toux, vector<double> Scores, unsigned total){
    double Score_Appendicite;
    double Freq_App;
    double Conf_App;
    unsigned cpt_Appendicite;
    unsigned cpt_cApp;
    unsigned cpt_cApp0;
    unsigned cpt_cApp1;
    if(fievre != "NULL" && douleur != "NULL" && toux != "NULL"){
        Scores.push_back(0);
    }
    else {
        for (int i(0);i<total;i++) {
            if(m_mat[0][i].c_str() == "Appendicite")cpt_Appendicite++;
        }
        for (int i(0);i<total;i++) {
            if(m_mat[0][i].c_str() == "Appendicite"){
                for (int j(0);j<m_vet.size();j++) {
                    if(fievre != "NULL" && m_mat[i][j] == fievre){
                        ++cpt_cApp;
                    }
                    else if (douleur != "NULL" &&  m_mat[i][j] == douleur) {
                        ++cpt_cApp0;
                    }
                    else if (toux != "NULL" &&  m_mat[i][j] == toux) {
                        ++cpt_cApp1;
                    }
                }
            }
        }
        Freq_App=cpt_Appendicite/total;
        Conf_App=((cpt_cApp/total)/Freq_App)*((cpt_cApp0/total)/Freq_App)*((cpt_cApp1/total)/Freq_App);
        Scores.push_back(Freq_App*Conf_App);
    }
}
void MaFenetre::scoreRhume(string fievre, string douleur, string toux, vector<double> Scores, unsigned total){
    double Score_Rhume;
    double Freq_Rhume;
    double Conf_Rhume;
    unsigned cpt_Rhume;
    unsigned cpt_cRhume;
    unsigned cpt_cRhume0;
    unsigned cpt_cRhume1;
    if(fievre != "NULL" && douleur != "NULL" && toux != "NULL"){
        Scores.push_back(0);
    }
    else {
        for (int i(0);i<total;i++) {
            if(m_mat[0][i].c_str() == "Rhume")cpt_Rhume++;
        }
        for (int i(0);i<total;i++) {
            if(m_mat[0][i].c_str() == "Rhume"){
                for (int j(0);j<m_vet.size();j++) {
                    if(fievre != "NULL" && m_mat[i][j] == fievre){
                        ++cpt_cRhume;
                    }
                    else if (douleur != "NULL" &&  m_mat[i][j] == douleur) {
                        ++cpt_cRhume0;
                    }
                    else if (toux != "NULL" &&  m_mat[i][j] == toux) {
                        ++cpt_cRhume1;
                    }
                }
            }
        }
        Freq_Rhume=cpt_Rhume/total;
        Conf_Rhume=((cpt_cRhume/total)/Freq_Rhume)*((cpt_cRhume0/total)/Freq_Rhume)*((cpt_cRhume1/total)/Freq_Rhume);
        Scores.push_back(Freq_Rhume*Conf_Rhume);
    }
}
void MaFenetre::scoreMal(string fievre, string douleur, string toux, vector<double> Scores, unsigned total){
    double Score_Mal;
    double Freq_Mal;
    double Conf_Mal;
    unsigned cpt_Mal;
    unsigned cpt_cMal;
    unsigned cpt_cMal0;
    unsigned cpt_cMal1;
    if(fievre != "NULL" && douleur != "NULL" && toux != "NULL"){
        Scores.push_back(0);
    }
    else {
        for (int i(0);i<total;i++) {
            if(m_mat[0][i].c_str() == "Mal")cpt_Mal++;
        }
        for (int i(0);i<total;i++) {
            if(m_mat[0][i].c_str() == "Mal"){
                for (int j(0);j<m_vet.size();j++) {
                    if(fievre != "NULL" && m_mat[i][j] == fievre){
                        ++cpt_cMal;
                    }
                    else if (douleur != "NULL" &&  m_mat[i][j] == douleur) {
                        ++cpt_cMal0;
                    }
                    else if (toux != "NULL" &&  m_mat[i][j] == toux) {
                        ++cpt_cMal1;
                    }
                }
            }
        }
        Freq_Mal=cpt_Mal/total;
        Conf_Mal=((cpt_cMal/total)/Freq_Mal)*((cpt_cMal0/total)/Freq_Mal)*((cpt_cMal1/total)/Freq_Mal);
        Scores.push_back(Freq_Mal*Conf_Mal);
    }
}
void MaFenetre::scoreRefroidissement(string fievre, string douleur, string toux, vector<double> Scores, unsigned total){
    double Score_Refroidissment;
    double Freq_Refroidissment;
    double Conf_Refroidissment;
    unsigned cpt_Refroidissment;
    unsigned cpt_cRefroidissment;
    unsigned cpt_cRefroidissment0;
    unsigned cpt_cRefroidissment1;
    if(fievre != "NULL" && douleur != "NULL" && toux != "NULL"){
        Scores.push_back(0);
    }
    else {
        for (int i(0);i<total;i++) {
            if(m_mat[0][i].c_str() == "Refroidissment")cpt_Refroidissment++;
        }
        for (int i(0);i<total;i++) {
            if(m_mat[0][i].c_str() == "Refroidissment"){
                for (int j(0);j<m_vet.size();j++) {
                    if(fievre != "NULL" && m_mat[i][j] == fievre){
                        ++cpt_cRefroidissment;
                    }
                    else if (douleur != "NULL" &&  m_mat[i][j] == douleur) {
                        ++cpt_cRefroidissment0;
                    }
                    else if (toux != "NULL" &&  m_mat[i][j] == toux) {
                        ++cpt_cRefroidissment1;
                    }
                }
            }
        }
        Freq_Refroidissment=cpt_Refroidissment/total;
        Conf_Refroidissment=((cpt_cRefroidissment/total)/Freq_Refroidissment)*((cpt_cRefroidissment0/total)/Freq_Refroidissment)*((cpt_cRefroidissment1/total)/Freq_Refroidissment);
        Scores.push_back(Freq_Refroidissment*Conf_Refroidissment);
    }
}
void MaFenetre::scoreAucune(string fievre, string douleur, string toux, vector<double> Scores, unsigned total){
    double Score_Aucune;
    double Freq_Aucune;
    double Conf_Aucune;
    unsigned cpt_Aucune;
    unsigned cpt_cAucune;
    unsigned cpt_cAucune0;
    unsigned cpt_cAucune1;
    if(fievre != "NULL" && douleur != "NULL" && toux != "NULL"){
        Scores.push_back(0);
    }
    else {
        for (int i(0);i<total;i++) {
            if(m_mat[0][i].c_str() == "Aucune")cpt_Aucune++;
        }
        for (int i(0);i<total;i++) {
            if(m_mat[0][i].c_str() == "Aucune"){
                for (int j(0);j<m_vet.size();j++) {
                    if(fievre != "NULL" && m_mat[i][j] == fievre){
                        ++cpt_cAucune;
                    }
                    else if (douleur != "NULL" &&  m_mat[i][j] == douleur) {
                        ++cpt_cAucune0;
                    }
                    else if (toux != "NULL" &&  m_mat[i][j] == toux) {
                        ++cpt_cAucune1;
                    }
                }
            }
        }
        Freq_Aucune=cpt_Aucune/total;
        Conf_Aucune=((cpt_cAucune/total)/Freq_Aucune)*((cpt_cAucune0/total)/Freq_Aucune)*((cpt_cAucune1/total)/Freq_Aucune);
        Scores.push_back(Freq_Aucune*Conf_Aucune);
    }
}

void MaFenetre::predire(){
    string fievre = (m_combo_fievre->currentText()).toStdString();
    string douleur = (m_combo_douleur->currentText().toStdString());
    string toux = (m_combo_toux->currentText().toStdString());
    vector<double> Scores;
    unsigned total = m_mat.size();

    this->scoreApp(fievre, douleur, toux, Scores, total);
    this->scoreRhume(fievre, douleur, toux, Scores, total);
    this->scoreMal(fievre, douleur, toux, Scores, total);
    this->scoreRefroidissement(fievre, douleur, toux, Scores, total);
    this->scoreAucune(fievre, douleur, toux, Scores, total);

    int max =distance(Scores.begin(), max_element(Scores.begin(), Scores.end()));
    m_alert = new QMessageBox;
    cout << max;
    switch (max) {
    case 0:
        m_alert->setText("Appendicite");
        break;
    case 1:
        m_alert->setText("Rhume");
        break;
    case 2:
        m_alert->setText("Mal de gorge");
        break;
    case 3:
        m_alert->setText("Refroidissement");
        break;
    case 4:
        m_alert->setText("Aucune");
        break;
    }
    m_alert->show();
}

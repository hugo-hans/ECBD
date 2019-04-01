#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMainWindow>
#include <QComboBox>
#include <QString>
#include <QLineEdit>
#include <QTableWidget>
#include <QMessageBox>


#include <vector>
#include "charger_csv.h"

class MaFenetre : public QMainWindow{
    Q_OBJECT // Macro OBLIGATOIRE
public slots :
    void setQuitter();
    void predire();
public :
    MaFenetre(QWidget *parent = 0);
    void creer_mat();
private :
    QLabel *m_nom, *m_prenom, *m_fievre, *m_douleur, *m_toux, *m_val_text;
    QLineEdit *m_nomi, *m_prenomi;
    QPushButton *m_bou, *m_predire;
    QComboBox *m_combo_fievre, *m_combo_douleur, *m_combo_toux;
    CVString m_vet;
    CMatString m_mat;
    QTableWidget *m_tab;
    QMessageBox *m_alert;
};

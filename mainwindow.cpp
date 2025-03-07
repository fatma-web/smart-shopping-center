#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "services.h" // Assurez-vous que ce fichier est bien inclus
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_Services->setModel(s.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_ajouter_clicked()
{
    int id = ui->le_id_ser->text().toInt();
    QString nom = ui->le_nom->text();
    double prix = ui->le_prix->text().toDouble();
    QString description = ui->le_descrip->text();
    QString statut = ui->le_statut->text();
    QString type = ui->le_type->text();
    QString dateDebut = ui->le_dated_date->date().toString("yyyy-MM-dd");
    QString dateFin = ui->le_datef_date->date().toString("yyyy-MM-dd");

    qDebug() << " [UI] Valeurs récupérées : " << id << nom << prix << description << statut << type << dateDebut << dateFin;

    if (nom.isEmpty() || description.isEmpty() || statut.isEmpty() || type.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Veuillez remplir tous les champs !\n"), QMessageBox::Cancel);
        return;
    }

    Services service(id, nom, prix, description, statut, type, dateDebut, dateFin);
    bool test = service.ajouter();

    if (test) {
        qDebug() << "✅ [AJOUT] Mise à jour du tableau";
        ui->tab_Services->setModel(s.afficher()); // Rafraîchir l'affichage
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\nClick Cancel to exit."), QMessageBox::Cancel);

        // Remplir également les champs de modification avec les données ajoutées
        ui->le_modif_id_ser->setText(QString::number(id));
        ui->le_modif_nom->setText(nom);
        ui->le_modif_prix->setText(QString::number(prix));
        ui->le_modif_descrip->setText(description);
        ui->le_modif_statut->setText(statut);
        ui->le_modif_type->setText(type);
        ui->le_modif_dated_date->setDate(QDate::fromString(dateDebut, "yyyy-MM-dd"));
        ui->le_modif_datef_date->setDate(QDate::fromString(dateFin, "yyyy-MM-dd"));
    } else {
        qDebug() << " [AJOUT] Affichage non mis à jour";
    }
}



void MainWindow::on_pushButton_supprimer_clicked()
{
    int id = ui->id_supp->text().toInt();

    qDebug() << " [UI] Suppression - ID récupéré : " << id;

    if (id == 0) {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Veuillez entrer un ID valide !\n"), QMessageBox::Cancel);
        return;
    }

    bool test = s.supprimer(id);

    if (test) {
        qDebug() << "✅ [SUPPRESSION] Succès! Rafraîchissement du tableau.";
        ui->tab_Services->setModel(s.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Suppression effectuée\nClick Cancel to exit."), QMessageBox::Cancel);
    } else {
        qDebug() << " [SUPPRESSION] Échec ! Vérifie la requête SQL.";
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Suppression non effectuée\nClick Cancel to exit."), QMessageBox::Cancel);
    }
}


void MainWindow::on_pushButton_annuler_clicked()
{
    ui->le_id_ser->clear();
    ui->le_nom->clear();
    ui->le_prix->clear();
    ui->le_descrip->clear();
    ui->le_statut->clear();
    ui->le_type->clear();
    ui->le_dated_date->clear();
    ui->le_datef_date->clear();
}

void MainWindow::on_pushButton_annuler_2_clicked()
{
    ui->le_modif_id_ser->clear();
    ui->le_modif_nom->clear();
    ui->le_modif_prix->clear();
    ui->le_modif_descrip->clear();
    ui->le_modif_statut->clear();
    ui->le_modif_type->clear();
    ui->le_modif_dated_date->clear();
    ui->le_modif_datef_date->clear();
}

void MainWindow::on_pushButton_modifier_clicked()
{
    int id = ui->le_modif_id_ser->text().toInt();
    QString nom = ui->le_modif_nom->text();
    double prix = ui->le_modif_prix->text().toDouble();
    QString description = ui->le_modif_descrip->text();
    QString statut = ui->le_modif_statut->text();
    QString type = ui->le_modif_type->text();
    QString dateDebut = ui->le_modif_dated_date->date().toString("yyyy-MM-dd");
    QString dateFin = ui->le_modif_datef_date->date().toString("yyyy-MM-dd");

    qDebug() << "📌 [UI] Modification - Valeurs récupérées : "
             << id << nom << prix << description << statut << type << dateDebut << dateFin;

    if (id == 0 || nom.isEmpty() || description.isEmpty() || statut.isEmpty() || type.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Veuillez remplir tous les champs !\n"), QMessageBox::Cancel);
        return;
    }

    Services service(id, nom, prix, description, statut, type, dateDebut, dateFin);
    bool test = service.modifier(id, nom, prix, description, statut, type, dateDebut, dateFin);

    if (test) {
        qDebug() << "✅ [MODIFICATION] Succès! Rafraîchissement du tableau.";
        ui->tab_Services->setModel(s.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Modification effectuée\nClick Cancel to exit."), QMessageBox::Cancel);
    } else {
        qDebug() << " [MODIFICATION] Échec ! Vérifie la requête SQL.";
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Modification non effectuée\nClick Cancel to exit."), QMessageBox::Cancel);
    }
}



void MainWindow::on_pushButton_annuler_3_clicked()
{
    ui->id_supp->clear();
}

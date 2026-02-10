#include "smartresearchpublicationmanagement.h"
#include "ui_smartresearchpublicationmanagement.h"

#include <QFile>
#include <QMessageBox>
#include <QDate>
#include <QDebug>  // Garder seulement QDebug

SmartResearchPublicationManagement::SmartResearchPublicationManagement(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SmartResearchPublicationManagement)
{
    ui->setupUi(this);

    applyTheme(":/styles/light.qss");


    // Initialiser les combobox de la page Inventory
    setupInventoryComboBoxes();

    // Initialiser le QStackedWidget de l'inventaire
    ui->InventoryStack->setCurrentIndex(0);

    // Ajouter des données de démonstration au tableau Inventory
    setupDemoInventoryData();
}

SmartResearchPublicationManagement::~SmartResearchPublicationManagement()
{
    delete ui;
}

void SmartResearchPublicationManagement::applyTheme(const QString& qssPath)
{
    QFile f(qssPath);
    if (f.open(QFile::ReadOnly)) {
        qApp->setStyleSheet(QString::fromUtf8(f.readAll()));
        f.close();
    }
}

void SmartResearchPublicationManagement::setupInventoryComboBoxes()
{
    // Initialiser les combobox des filtres
    ui->InventoryType->addItems({"Tous", "Équipement", "Consommable", "Réactif", "Matériel", "Logiciel"});
    ui->InventoryStatus->addItems({"Tous", "on_hand", "limited", "stock_out"});
    ui->InventoryZone->addItems({"Toutes", "A", "B", "C", "D"});

    // Initialiser les combobox du formulaire
    ui->Type->addItems({"Équipement", "Consommable", "Réactif", "Matériel", "Logiciel"});
    ui->Unit->addItems({"Kg", "L", "M", "Pièce", "Unité", "Boîte"});
    ui->Status->addItems({"on_hand", "limited", "stock_out"});
    ui->Zone->addItems({"A", "B", "C", "D"});
    ui->Shelf->addItems({"0", "1", "2", "3", "4"});
}

void SmartResearchPublicationManagement::setupDemoInventoryData()
{
    // Configuration du tableau avec 12 colonnes
    ui->TableInventory->setColumnCount(12);
    QStringList headers = {"ID", "Nom", "SKU", "Type", "Qt Av.", "Qt Rs.", "Seuil", "Unité", "Prix", "Zone", "Étagère", "Statut"};
    ui->TableInventory->setHorizontalHeaderLabels(headers);

    // Ajouter des données de démonstration
    QStringList demoData = {
        "PROD-001|Microscope|SKU-MIC-001|Équipement|5|2|3|Pièce|2500.00|A|2|on_hand",
        "PROD-002|Tubes à essai|SKU-TUB-002|Consommable|100|25|20|Boîte|15.50|B|1|on_hand",
        "PROD-003|Réactif A|SKU-REA-003|Réactif|50|10|15|L|120.75|C|3|limited",
        "PROD-004|Ordinateur|SKU-ORD-004|Matériel|10|3|5|Pièce|1200.00|D|0|on_hand",
        "PROD-005|Logiciel Lab|SKU-LOG-005|Logiciel|1|0|1|Licence|500.00|A|4|stock_out"
    };

    ui->TableInventory->setRowCount(demoData.size());

    for (int i = 0; i < demoData.size(); i++) {
        QStringList fields = demoData[i].split('|');
        for (int j = 0; j < fields.size() && j < 12; j++) {
            QTableWidgetItem *item = new QTableWidgetItem(fields[j]);
            ui->TableInventory->setItem(i, j, item);
        }
    }

    // Ajuster la largeur des colonnes
    ui->TableInventory->horizontalHeader()->setStretchLastSection(true);
    for (int i = 0; i < 12; i++) {
        ui->TableInventory->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }
}

void SmartResearchPublicationManagement::on_BtnTheme_clicked()
{
    m_dark = !m_dark;
    applyTheme(m_dark ? QString(":/styles/dark.qss") : QString(":/styles/light.qss"));
}

void SmartResearchPublicationManagement::on_BtnEmployee_clicked(){ ui->Pages->setCurrentWidget(ui->PageEmployee); }
void SmartResearchPublicationManagement::on_BtnFinance_clicked(){ ui->Pages->setCurrentWidget(ui->PageFinance); }
void SmartResearchPublicationManagement::on_BtnPublication_clicked(){ ui->Pages->setCurrentWidget(ui->PagePublication); }
void SmartResearchPublicationManagement::on_BtnLabs_clicked(){ ui->Pages->setCurrentWidget(ui->PageLabs); }
void SmartResearchPublicationManagement::on_BtnInventory_clicked(){ ui->Pages->setCurrentWidget(ui->PageInventory); }
void SmartResearchPublicationManagement::on_BtnPlans_clicked(){ ui->Pages->setCurrentWidget(ui->PagePlans); }

// ============= SLOTS POUR L'INVENTAIRE =============

void SmartResearchPublicationManagement::on_BtnInventoryAdd_clicked()
{
    qDebug() << "Bouton Ajouter Inventory cliqué";
    ui->InventoryStack->setCurrentIndex(1);
    ui->PopupTitleInventory->setText("Ajouter un produit");

    // Réinitialiser tous les champs du formulaire
    ui->IdProduct->clear();
    ui->Name->clear();
    ui->Sku->clear();
    ui->Type->setCurrentIndex(0);
    ui->QtAv->setValue(0);
    ui->QtRs->setValue(0);
    ui->Threshold->setValue(0);
    ui->Unit->setCurrentIndex(0);
    ui->Price->setValue(0.00);
    ui->Status->setCurrentIndex(0);
    ui->Zone->setCurrentIndex(0);
    ui->Shelf->setCurrentIndex(0);
}

void SmartResearchPublicationManagement::on_BtnInventoryEdit_clicked()
{
    qDebug() << "Bouton Modifier Inventory cliqué";

    // Vérifier si une ligne est sélectionnée dans le tableau
    QModelIndexList selectedIndexes = ui->TableInventory->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner un produit à modifier.");
        return;
    }

    // Afficher le popup de modification
    ui->InventoryStack->setCurrentIndex(1);
    ui->PopupTitleInventory->setText("Modifier le produit");

    // Charger les données du produit sélectionné
    int row = selectedIndexes.first().row();

    // Récupérer les données depuis le tableau
    QString productId = ui->TableInventory->item(row, 0) ? ui->TableInventory->item(row, 0)->text() : "";
    QString name = ui->TableInventory->item(row, 1) ? ui->TableInventory->item(row, 1)->text() : "";
    QString sku = ui->TableInventory->item(row, 2) ? ui->TableInventory->item(row, 2)->text() : "";
    QString type = ui->TableInventory->item(row, 3) ? ui->TableInventory->item(row, 3)->text() : "";
    QString qtAv = ui->TableInventory->item(row, 4) ? ui->TableInventory->item(row, 4)->text() : "0";
    QString qtRs = ui->TableInventory->item(row, 5) ? ui->TableInventory->item(row, 5)->text() : "0";
    QString threshold = ui->TableInventory->item(row, 6) ? ui->TableInventory->item(row, 6)->text() : "0";
    QString unit = ui->TableInventory->item(row, 7) ? ui->TableInventory->item(row, 7)->text() : "";
    QString price = ui->TableInventory->item(row, 8) ? ui->TableInventory->item(row, 8)->text() : "0.00";
    QString zone = ui->TableInventory->item(row, 9) ? ui->TableInventory->item(row, 9)->text() : "";
    QString shelf = ui->TableInventory->item(row, 10) ? ui->TableInventory->item(row, 10)->text() : "";
    QString status = ui->TableInventory->item(row, 11) ? ui->TableInventory->item(row, 11)->text() : "";

    // Remplir le formulaire
    ui->IdProduct->setText(productId);
    ui->Name->setText(name);
    ui->Sku->setText(sku);

    // Définir les combobox
    int typeIndex = ui->Type->findText(type);
    if (typeIndex >= 0) ui->Type->setCurrentIndex(typeIndex);

    ui->QtAv->setValue(qtAv.toInt());
    ui->QtRs->setValue(qtRs.toInt());
    ui->Threshold->setValue(threshold.toInt());

    int unitIndex = ui->Unit->findText(unit);
    if (unitIndex >= 0) ui->Unit->setCurrentIndex(unitIndex);

    // Nettoyer le préfixe € du prix s'il existe
    QString cleanPrice = price;
    if (cleanPrice.startsWith("€ ")) {
        cleanPrice = cleanPrice.mid(2);
    }
    ui->Price->setValue(cleanPrice.toDouble());

    int statusIndex = ui->Status->findText(status);
    if (statusIndex >= 0) ui->Status->setCurrentIndex(statusIndex);

    int zoneIndex = ui->Zone->findText(zone);
    if (zoneIndex >= 0) ui->Zone->setCurrentIndex(zoneIndex);

    int shelfIndex = ui->Shelf->findText(shelf);
    if (shelfIndex >= 0) ui->Shelf->setCurrentIndex(shelfIndex);
}

void SmartResearchPublicationManagement::on_BtnInventoryDelete_clicked()
{
    qDebug() << "Bouton Supprimer Inventory cliqué";

    QModelIndexList selectedIndexes = ui->TableInventory->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner un produit à supprimer.");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  "Êtes-vous sûr de vouloir supprimer le produit sélectionné ?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // Supprimer la ligne sélectionnée
        int row = selectedIndexes.first().row();
        ui->TableInventory->removeRow(row);
        qDebug() << "Produit supprimé de la ligne" << row;
        QMessageBox::information(this, "Succès", "Produit supprimé avec succès.");
    }
}

void SmartResearchPublicationManagement::on_BtnInventoryApply_clicked()
{
    qDebug() << "Bouton Appliquer les filtres cliqué";

    QString searchText = ui->InventorySearch->text().toLower();
    QString typeFilter = ui->InventoryType->currentText();
    QString statusFilter = ui->InventoryStatus->currentText();
    QString zoneFilter = ui->InventoryZone->currentText();

    qDebug() << "Filtres appliqués:";
    qDebug() << "  Recherche:" << searchText;
    qDebug() << "  Type:" << typeFilter;
    qDebug() << "  Statut:" << statusFilter;
    qDebug() << "  Zone:" << zoneFilter;

    // Filtrer les lignes du tableau
    bool filterApplied = false;

    for (int row = 0; row < ui->TableInventory->rowCount(); row++) {
        bool rowVisible = true;

        // Filtrer par texte de recherche
        if (!searchText.isEmpty()) {
            bool textMatch = false;
            for (int col = 0; col < ui->TableInventory->columnCount(); col++) {
                QTableWidgetItem *item = ui->TableInventory->item(row, col);
                if (item && item->text().toLower().contains(searchText)) {
                    textMatch = true;
                    break;
                }
            }
            if (!textMatch) {
                rowVisible = false;
            }
        }

        // Filtrer par type
        if (typeFilter != "Tous") {
            QTableWidgetItem *typeItem = ui->TableInventory->item(row, 3);
            if (typeItem && typeItem->text() != typeFilter) {
                rowVisible = false;
            }
        }

        // Filtrer par statut
        if (statusFilter != "Tous") {
            QTableWidgetItem *statusItem = ui->TableInventory->item(row, 11);
            if (statusItem && statusItem->text() != statusFilter) {
                rowVisible = false;
            }
        }

        // Filtrer par zone
        if (zoneFilter != "Toutes") {
            QTableWidgetItem *zoneItem = ui->TableInventory->item(row, 9);
            if (zoneItem && zoneItem->text() != zoneFilter) {
                rowVisible = false;
            }
        }

        // Afficher ou masquer la ligne
        ui->TableInventory->setRowHidden(row, !rowVisible);
        if (!rowVisible) filterApplied = true;
    }

    if (filterApplied) {
        QMessageBox::information(this, "Filtres", "Filtres appliqués avec succès.");
    } else {
        // Afficher toutes les lignes si aucun filtre actif
        for (int row = 0; row < ui->TableInventory->rowCount(); row++) {
            ui->TableInventory->setRowHidden(row, false);
        }
        QMessageBox::information(this, "Filtres", "Tous les filtres ont été réinitialisés.");
    }
}

void SmartResearchPublicationManagement::on_BtnInventoryExport_clicked()
{
    qDebug() << "Bouton Exporter PDF cliqué";
    QMessageBox::information(this, "Export PDF", "Export PDF en cours (démo)...");
    // Ici, vous généreriez le PDF
    QMessageBox::information(this, "Export PDF", "PDF exporté avec succès (démo).");
}

void SmartResearchPublicationManagement::on_BtnPopupCancelInventory_clicked()
{
    qDebug() << "Bouton Annuler (popup) cliqué";
    ui->InventoryStack->setCurrentIndex(0);
}

void SmartResearchPublicationManagement::on_BtnPopupSaveInventory_clicked()
{
    qDebug() << "Bouton Enregistrer (popup) cliqué";

    // Récupérer les valeurs du formulaire
    QString idProduct = ui->IdProduct->text().trimmed();
    QString name = ui->Name->text().trimmed();
    QString sku = ui->Sku->text().trimmed();
    QString type = ui->Type->currentText();
    int qtAv = ui->QtAv->value();
    int qtRs = ui->QtRs->value();
    int threshold = ui->Threshold->value();
    QString unit = ui->Unit->currentText();
    double price = ui->Price->value();
    QString status = ui->Status->currentText();
    QString zone = ui->Zone->currentText();
    QString shelf = ui->Shelf->currentText();

    // Validation
    if (idProduct.isEmpty() || name.isEmpty() || sku.isEmpty()) {
        QMessageBox::warning(this, "Champs requis",
                             "Veuillez remplir l'ID, le nom et le SKU du produit.");
        return;
    }

    if (qtAv < 0 || qtRs < 0 || threshold < 0 || price < 0) {
        QMessageBox::warning(this, "Valeurs invalides",
                             "Les valeurs numériques doivent être positives.");
        return;
    }

    qDebug() << "Données du produit à sauvegarder:";
    qDebug() << "  ID:" << idProduct;
    qDebug() << "  Nom:" << name;
    qDebug() << "  SKU:" << sku;
    qDebug() << "  Type:" << type;
    qDebug() << "  QtAv:" << qtAv;
    qDebug() << "  QtRs:" << qtRs;
    qDebug() << "  Seuil:" << threshold;
    qDebug() << "  Unité:" << unit;
    qDebug() << "  Prix:" << price;
    qDebug() << "  Statut:" << status;
    qDebug() << "  Zone:" << zone;
    qDebug() << "  Étagère:" << shelf;

    // Vérifier si on est en mode édition ou ajout
    bool isEditMode = (ui->PopupTitleInventory->text().startsWith("Modifier"));

    if (isEditMode) {
        // Mode édition - trouver et mettre à jour la ligne existante
        for (int row = 0; row < ui->TableInventory->rowCount(); row++) {
            QTableWidgetItem *item = ui->TableInventory->item(row, 0);
            if (item && item->text() == idProduct) {
                // Mettre à jour la ligne
                ui->TableInventory->item(row, 0)->setText(idProduct);
                ui->TableInventory->item(row, 1)->setText(name);
                ui->TableInventory->item(row, 2)->setText(sku);
                ui->TableInventory->item(row, 3)->setText(type);
                ui->TableInventory->item(row, 4)->setText(QString::number(qtAv));
                ui->TableInventory->item(row, 5)->setText(QString::number(qtRs));
                ui->TableInventory->item(row, 6)->setText(QString::number(threshold));
                ui->TableInventory->item(row, 7)->setText(unit);
                ui->TableInventory->item(row, 8)->setText(QString("€ %1").arg(price, 0, 'f', 2));
                ui->TableInventory->item(row, 9)->setText(zone);
                ui->TableInventory->item(row, 10)->setText(shelf);
                ui->TableInventory->item(row, 11)->setText(status);
                break;
            }
        }
        QMessageBox::information(this, "Succès", "Produit modifié avec succès.");
    } else {
        // Mode ajout - ajouter une nouvelle ligne
        int newRow = ui->TableInventory->rowCount();
        ui->TableInventory->insertRow(newRow);

        ui->TableInventory->setItem(newRow, 0, new QTableWidgetItem(idProduct));
        ui->TableInventory->setItem(newRow, 1, new QTableWidgetItem(name));
        ui->TableInventory->setItem(newRow, 2, new QTableWidgetItem(sku));
        ui->TableInventory->setItem(newRow, 3, new QTableWidgetItem(type));
        ui->TableInventory->setItem(newRow, 4, new QTableWidgetItem(QString::number(qtAv)));
        ui->TableInventory->setItem(newRow, 5, new QTableWidgetItem(QString::number(qtRs)));
        ui->TableInventory->setItem(newRow, 6, new QTableWidgetItem(QString::number(threshold)));
        ui->TableInventory->setItem(newRow, 7, new QTableWidgetItem(unit));
        ui->TableInventory->setItem(newRow, 8, new QTableWidgetItem(QString("€ %1").arg(price, 0, 'f', 2)));
        ui->TableInventory->setItem(newRow, 9, new QTableWidgetItem(zone));
        ui->TableInventory->setItem(newRow, 10, new QTableWidgetItem(shelf));
        ui->TableInventory->setItem(newRow, 11, new QTableWidgetItem(status));

        QMessageBox::information(this, "Succès", "Produit ajouté avec succès.");
    }

    ui->InventoryStack->setCurrentIndex(0);
}

void SmartResearchPublicationManagement::on_BtnPopupResetInventory_clicked()
{
    qDebug() << "Bouton Vider (popup) cliqué";

    // Réinitialiser tous les champs du formulaire
    ui->IdProduct->clear();
    ui->Name->clear();
    ui->Sku->clear();
    ui->Type->setCurrentIndex(0);
    ui->QtAv->setValue(0);
    ui->QtRs->setValue(0);
    ui->Threshold->setValue(0);
    ui->Unit->setCurrentIndex(0);
    ui->Price->setValue(0.00);
    ui->Status->setCurrentIndex(0);
    ui->Zone->setCurrentIndex(0);
    ui->Shelf->setCurrentIndex(0);
}

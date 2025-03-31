#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "parser/objparser.h"
#include <iostream>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    showMaximized();
    // Connect the spin box to color change method
    connect(ui->editRed, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::onColorChange);
    connect(ui->editGreen, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::onColorChange);
    connect(ui->editBlue, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::onColorChange);
    connect(ui->editAlpha, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::onColorChange);

    // import obj file
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::onImportButtonClicked);

    connect(this, &MainWindow::fileSelected, this, [this](const QString &filePath) {
        ui->renderWidget->importObjFile(filePath.toStdString());
    });


    connect(ui->rotateLeft, &QPushButton::clicked, this, [this]() {
        ui->renderWidget->rotate({-5.0f, 0, 1, 0});
    });

    connect(ui->rotateRight, &QPushButton::clicked, this, [this]() {
        ui->renderWidget->rotate({5.0f, 0, 1, 0});
    });

    connect(ui->rotateTop, &QPushButton::clicked, this, [this]() {
        ui->renderWidget->rotate({5.0f, 1, 0, 0});
    });

    connect(ui->rotateDown, &QPushButton::clicked, this, [this]() {
        ui->renderWidget->rotate({-5.0f, 1, 0, 0});
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onColorChange()
{
    ui->renderWidget->changeColor({ (float)ui->editRed->value(),  (float)ui->editGreen->value(), (float)ui->editBlue->value(), (float)ui->editAlpha->value(), });
}

void MainWindow::onImportButtonClicked()
{
    QFileDialog dialog(this);
    dialog.setOption(QFileDialog::DontUseNativeDialog);
    dialog.setWindowTitle("Select File");
    dialog.setMinimumSize(600, 400);

    dialog.setNameFilter("OBJ Files (*.obj)");

    if (dialog.exec() == QDialog::Accepted) {
        QString filePath = dialog.selectedFiles().first();
        emit fileSelected(filePath);
    }
}

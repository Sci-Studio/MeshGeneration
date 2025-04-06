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

    // Connect the render button to the render action
    connect(ui->renderShapeButton, &QPushButton::clicked, this, &MainWindow::onRenderButtonClicked);

    // Connect the spin box to color change method
    connect(ui->editRed, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::onColorChange);
    connect(ui->editGreen, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::onColorChange);
    connect(ui->editBlue, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::onColorChange);
    connect(ui->editAlpha, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::onColorChange);

    // import obj file
    connect(ui->importObjFile, &QPushButton::clicked, this, &MainWindow::onImportButtonClicked);

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
    // test protetection rule
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onRenderButtonClicked()
{

}

void MainWindow::onColorChange(double c)
{
    std::vector<float> color;
    color.resize(4);
    color[0] = ui->editRed->value();
    color[1] = ui->editGreen->value();
    color[2] = ui->editBlue->value();
    color[3] = ui->editAlpha->value();
    ui->renderWidget->changeColor(color);
}

void MainWindow::onImportButtonClicked()
{
    // Open a file dialog to select a file
        QString filePath = QFileDialog::getOpenFileName(this, "Open File", "", "OBJ Files (*.obj)");

        if (!filePath.isEmpty()) {
            // File selected, process it
            emit fileSelected(filePath);
        } else {
            // No file selected
            QMessageBox::information(this, "No file selected", "Ok");
        }
}

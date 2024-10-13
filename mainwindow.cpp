#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>

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


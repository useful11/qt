#include "rules.h"
#include "ui_rules.h"

rules::rules(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rules)
{
    ui->setupUi(this);
    setWindowTitle("游戏规则介绍");
}

rules::~rules()
{
    delete ui;
}

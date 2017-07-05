#include "mainwindow.h"
#include <QApplication>
#include <QDialog>
#include "lexical.h"
#include "syntax.h"
#include "cal_quat.h"
#include "quaternion.h"
#include "target_code.h"

lexical_analyse main_lexical;
syntax_analyse main_syntax;
cal_quat main_quat;
target_code main_tar;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

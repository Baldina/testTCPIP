#include "mainwidget.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  Client widget;

  widget.show();
  app.exec();
}

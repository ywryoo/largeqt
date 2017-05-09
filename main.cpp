/// @author Ryangwook Ryoo, 2017
/// @email ywryoo@gmail.com
/// @license GNU LGPL
///
/// Distributed under the GNU LGPL License
/// (See accompanying file LICENSE or copy at
/// http://www.gnu.org/licenses/lgpl.html)

#include <QApplication>
#include "mainwindow.h"

int main( int argc, char **argv )
{
  
    QApplication a( argc, argv );

    MainWindow w( argc, argv );

    w.show();
 
    return a.exec();
}

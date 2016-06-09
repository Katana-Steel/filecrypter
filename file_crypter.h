#ifndef __file_crypter_h
/* FCMain -- The GUI to all the 5 encryption algorithms
 *
 * Written by René Kjellerup <katana_steel@users.sourceforge.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#define __file_crypter_h 1

#include <QMainWindow>
#include "ui_file_crypter.h"

namespace xcrypter {
class crypt;
}

class FCMain : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT
    xcrypter::crypt *xcry;
public:
    FCMain(QWidget *p=0);

    void show();

private slots:
    void startEnc();
    void startDec();
    void openInput();
    void setOutput();
    void setKey();
    void openKey();
    void check_xcrypter(int idx);
    void adjustUI();
    void about();

private:
    bool algo1e();
    bool algo1d();
    bool algo2e();
    bool algo2d();
    bool algo3e();
    bool algo3d();
    bool algo4e();
    bool algo4d();

};

#endif


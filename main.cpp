/* main.cpp -- the application start up.
 *
 * Starts the main dialog: FCMain, and sends control to it.
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

#include <QApplication>
#include <QCleanlooksStyle>
#include "file_crypter.h"

int
main(int p1, char *p2[])
{
    QApplication a(p1,p2);
    QStyle *st = new QCleanlooksStyle;
    a.setPalette(st->standardPalette());
    a.setStyle(st);
    FCMain win;
    win.show();
    return a.exec();
}

/* file_crypter.cpp -- The implementation of the GUI and the 4 simple
 * algorithms
 *
 * The main dialog which gives access to all the 5 different encryption
 * algorithms. The 4 simple ones are implemented here, with the 5th
 * "xcrypter" algorithm being accessed as appropriate for that algorithm.
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

#include "file_crypter.h"
#include <QtGui>
#include <fstream>
#include <crypt.h>

FCMain::FCMain(QWidget *p)
    : QMainWindow(p)
{
    xcry = 0;
    setupUi(this);

    check_xcrypter(0);

    connect(actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    connect(encBtn, SIGNAL(clicked()), this, SLOT(startEnc()));
    connect(decBtn, SIGNAL(clicked()), this, SLOT(startDec()));
    connect(inputFileBtn, SIGNAL(clicked()), this, SLOT(openInput()));
    connect(outputFileBtn, SIGNAL(clicked()), this, SLOT(setOutput()));
    connect(keyFileBtn, SIGNAL(clicked()), this, SLOT(openKey()));
    connect(setKeyFileBtn, SIGNAL(clicked()), this, SLOT(setKey()));
    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(check_xcrypter(int)));
}

void
FCMain::startEnc()
{
    bool ret;
    switch(comboBox->currentIndex())
    {
    case 0:
        ret = algo1e();
        break;
    case 1:
        ret = algo2e();
        break;
    case 2:
        ret = algo3e();
        break;
    case 3:
        ret = algo4e();
        break;
    case 4:
	if(xcry) {
	    std::ifstream I(inputFile->text().toAscii().constData(),
    		std::ios_base::binary);
	    std::ofstream O(outputFile->text().toAscii().constData(),
    		std::ios_base::binary);
	    xcry->enc(I,O);
	    I.close();
	    O.close();
	    ret = true;
	} else {
    	    ret = false;
	}
        break;
    default:
        ret = false;
    }
    if(!ret)
	QMessageBox::information(this,"File Crypter","Unable to process your request");
}

void
FCMain::startDec()
{
    bool ret;
    switch(comboBox->currentIndex())
    {
    case 0:
        ret = algo1d();
        break;
    case 1:
        ret = algo2d();
        break;
    case 2:
        ret = algo3d();
        break;
    case 3:
        ret = algo4d();
        break;
    case 4:
	if(xcry) {
	    std::ifstream I(inputFile->text().toAscii().constData(),
    		std::ios_base::binary);
	    std::ofstream O(outputFile->text().toAscii().constData(),
    		std::ios_base::binary);
	    xcry->dec(I,O);
	    I.close();
	    O.close();
	    ret = true;
	} else {
    	    ret = false;
	}
        break;
    default:
        ret = false;
    }
    if(!ret)
	QMessageBox::information(this,"File Crypter","Unable to process your request");
}

void
FCMain::about()
{
    QDialog *win = new QDialog;
    QVBoxLayout *vb = new QVBoxLayout(win);
    QLabel *lab = new QLabel("File Crypter");
    vb->addWidget(lab);
    lab = new QLabel(" ");
    vb->addWidget(lab);
    lab = new QLabel("version 1.5");
    vb->addWidget(lab);
    lab = new QLabel("by");
    vb->addWidget(lab);
    lab = new QLabel("René Kjellerup");
    vb->addWidget(lab);
    vb->addStretch();
    win->exec();
    delete win;
}

void
FCMain::show()
{
    QMainWindow::show();
    adjustUI();
}

void
FCMain::adjustUI()
{
    QRect rc;
    if(inputFileBtn->width() <= outputFileBtn->width())
        rc = outputFileBtn->rect();
    else
        rc = inputFileBtn->rect();

    setKeyFileBtn->setMinimumWidth(rc.width());
    inputFileBtn->setMinimumWidth(rc.width());
    outputFileBtn->setMinimumWidth(rc.width());
    this->setMinimumWidth(rc.width()*4);
}

void
FCMain::setKey()
{
    if(keyFile->text().isEmpty()) return;

    if(xcry) delete xcry;
    xcry = new xcrypter::crypt(keyFile->text().toAscii().constData());
}

void
FCMain::openKey()
{
    QString fname = QFileDialog::getOpenFileName(this, "Input File:");
    if(!fname.isNull())
	keyFile->setText(fname);

}

void
FCMain::check_xcrypter(int idx)
{
    bool vis = false;
    if(idx == 4) vis = true;

    keyFile->setVisible(vis);
    keyFileBtn->setVisible(vis);
    setKeyFileBtn->setVisible(vis);
}

void
FCMain::openInput()
{
    QString fname = QFileDialog::getOpenFileName(this, "Input File:");
    if(!fname.isNull())
	inputFile->setText(fname);
}

void
FCMain::setOutput()
{
    QString fname = QFileDialog::getSaveFileName(this, "Output File:");
    if(!fname.isNull())
	outputFile->setText(fname);
}

bool
FCMain::algo1e()
{
    unsigned long long count = 0;   // cryption counter
    unsigned char c; // tmp data
    int cc;
    std::ifstream I(inputFile->text().toAscii().constData(),
        std::ios_base::binary);
    std::ofstream O(outputFile->text().toAscii().constData(),
	std::ios_base::binary);
    while((cc = I.get()) >= 0) {
        c = (unsigned char)cc;
	switch(count%5) {
	case 0:
	  c += 0x12;
	  O << c;
	  break;
	case 1:
	  c += 0x10;
	  O << c;
	  break;
	case 2:
	  c += 0x14;
	  O << c;
	  break;
	case 3:
	  c += 0x18;
	  O << c;
	  break;
	case 4:
	  c += 0x16;
	  O << c;
	  break;
	}
	count++;
    }
    I.close();
    O.close();
    return true;
}
bool
FCMain::algo1d()
{
    unsigned long long count = 0;   // cryption counter
    unsigned char c; // tmp data
    int cc;
    std::ifstream I(inputFile->text().toAscii().constData(),
        std::ios_base::binary);
    std::ofstream O(outputFile->text().toAscii().constData(),
	std::ios_base::binary);
    while((cc = I.get()) >= 0) {
        c = (unsigned char)cc;
	switch(count%5) {
	case 0:
	  c -= 0x12;
	  O << c;
	  break;
	case 1:
	  c -= 0x10;
	  O << c;
	  break;
	case 2:
	  c -= 0x14;
	  O << c;
	  break;
	case 3:
	  c -= 0x18;
	  O << c;
	  break;
	case 4:
	  c -= 0x16;
	  O << c;
	  break;
	}
	count++;
    }
    I.close();
    O.close();
    return true;
}
bool
FCMain::algo2e()
{
    unsigned long long count = 0;   // cryption counter
    unsigned char c; // tmp data
    int cc;
    std::ifstream I(inputFile->text().toAscii().constData(),
        std::ios_base::binary);
    std::ofstream O(outputFile->text().toAscii().constData(),
	std::ios_base::binary);
    while((cc = I.get()) >= 0) {
        c = (unsigned char)cc;
	switch(count%5) {
	case 0:
	  c -= 0x12;
	  O << c;
	  break;
	case 1:
	  c += 0x10;
	  O << c;
	  break;
	case 2:
	  c -= 0x14;
	  O << c;
	  break;
	case 3:
	  c += 0x18;
	  O << c;
	  break;
	case 4:
	  c -= 0x16;
	  O << c;
	  break;
	}
	count++;
    }
    I.close();
    O.close();
    return true;
}
bool
FCMain::algo2d()
{
    unsigned long long count = 0;   // cryption counter
    unsigned char c; // tmp data
    int cc;
    std::ifstream I(inputFile->text().toAscii().constData(),
        std::ios_base::binary);
    std::ofstream O(outputFile->text().toAscii().constData(),
	std::ios_base::binary);
    while((cc = I.get()) >= 0) {
        c = (unsigned char)cc;
	switch(count%5) {
	case 0:
	  c += 0x12;
	  O << c;
	  break;
	case 1:
	  c -= 0x10;
	  O << c;
	  break;
	case 2:
	  c += 0x14;
	  O << c;
	  break;
	case 3:
	  c -= 0x18;
	  O << c;
	  break;
	case 4:
	  c += 0x16;
	  O << c;
	  break;
	}
	count++;
    }
    I.close();
    O.close();
    return true;
}
bool
FCMain::algo3e()
{
    unsigned long long count = 0;   // cryption counter
    unsigned char c; // tmp data
    int cc;
    std::ifstream I(inputFile->text().toAscii().constData(),
        std::ios_base::binary);
    std::ofstream O(outputFile->text().toAscii().constData(),
	std::ios_base::binary);
    while((cc = I.get()) >= 0) {
        c = (unsigned char)cc;
	switch(count%5) {
	case 0:
	  c += 0x12;
	  O << c;
	  break;
	case 1:
	  c += 0x10;
	  O << c;
	  break;
	case 2:
	  c -= 0x14;
	  O << c;
	  break;
	case 3:
	  c -= 0x18;
	  O << c;
	  break;
	case 4:
	  c -= 0x16;
	  O << c;
	  break;
	}
	count++;
    }
    I.close();
    O.close();
    return true;
}
bool
FCMain::algo3d()
{
    unsigned long long count = 0;   // cryption counter
    unsigned char c; // tmp data
    int cc;
    std::ifstream I(inputFile->text().toAscii().constData(),
        std::ios_base::binary);
    std::ofstream O(outputFile->text().toAscii().constData(),
	std::ios_base::binary);
    while((cc = I.get()) >= 0) {
        c = (unsigned char)cc;
	switch(count%5) {
	case 0:
	  c -= 0x12;
	  O << c;
	  break;
	case 1:
	  c -= 0x10;
	  O << c;
	  break;
	case 2:
	  c += 0x14;
	  O << c;
	  break;
	case 3:
	  c += 0x18;
	  O << c;
	  break;
	case 4:
	  c += 0x16;
	  O << c;
	  break;
	}
	count++;
    }
    I.close();
    O.close();
    return true;
}
bool
FCMain::algo4e()
{
    unsigned long long count = 0;   // cryption counter
    unsigned char c; // tmp data
    int cc;
    std::ifstream I(inputFile->text().toAscii().constData(),
        std::ios_base::binary);
    std::ofstream O(outputFile->text().toAscii().constData(),
	std::ios_base::binary);
    while((cc = I.get()) >= 0) {
        c = (unsigned char)cc;
	switch(count%15) {
	case 0:
	  c += 0x12;
	  O << c;
	  break;
	case 1:
	  c += 0x10;
	  O << c;
	  break;
	case 2:
	  c += 0x14;
	  O << c;
	  break;
	case 3:
	  c += 0x18;
	  O << c;
	  break;
	case 4:
	  c += 0x16;
	  O << c;
	  break;
	case 5:
	  c += 0x12;
	  O << c;
	  break;
	case 6:
	  c -= 0x10;
	  O << c;
	  break;
	case 7:
	  c += 0x14;
	  O << c;
	  break;
	case 8:
	  c -= 0x18;
	  O << c;
	  break;
	case 9:
	  c += 0x16;
	  O << c;
	  break;
	case 10:
	  c += 0x12;
	  O << c;
	  break;
	case 11:
	  c += 0x10;
	  O << c;
	  break;
	case 12:
	  c -= 0x14;
	  O << c;
	  break;
	case 13:
	  c -= 0x18;
	  O << c;
	  break;
	case 14:
	  c -= 0x16;
	  O << c;
	  break;
	}
	count++;
    }
    I.close();
    O.close();
    return true;
}
bool
FCMain::algo4d()
{
    unsigned long long count = 0;   // cryption counter
    unsigned char c; // tmp data
    int cc;
    std::ifstream I(inputFile->text().toAscii().constData(),
        std::ios_base::binary);
    std::ofstream O(outputFile->text().toAscii().constData(),
	std::ios_base::binary);
    while((cc = I.get()) >= 0) {
        c = (unsigned char)cc;
	switch(count%15) {
	case 0:
	  c -= 0x12;
	  O << c;
	  break;
	case 1:
	  c -= 0x10;
	  O << c;
	  break;
	case 2:
	  c -= 0x14;
	  O << c;
	  break;
	case 3:
	  c -= 0x18;
	  O << c;
	  break;
	case 4:
	  c -= 0x16;
	  O << c;
	  break;
	case 5:
	  c -= 0x12;
	  O << c;
	  break;
	case 6:
	  c += 0x10;
	  O << c;
	  break;
	case 7:
	  c -= 0x14;
	  O << c;
	  break;
	case 8:
	  c += 0x18;
	  O << c;
	  break;
	case 9:
	  c -= 0x16;
	  O << c;
	  break;
	case 10:
	  c -= 0x12;
	  O << c;
	  break;
	case 11:
	  c -= 0x10;
	  O << c;
	  break;
	case 12:
	  c += 0x14;
	  O << c;
	  break;
	case 13:
	  c += 0x18;
	  O << c;
	  break;
	case 14:
	  c += 0x16;
	  O << c;
	  break;
	}
	count++;
    }
    I.close();
    O.close();
    return true;
}


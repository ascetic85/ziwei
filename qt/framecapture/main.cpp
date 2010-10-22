/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include "framecapture.h"

#include <iostream>
#include <QtGui>

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget (QWidget *parent = 0)
        : QWidget (parent)
        , m_capture(0)
    {
        setWindowTitle(tr("Http Capture"));
        QVBoxLayout *layout = new QVBoxLayout();


        QHBoxLayout *itemLayout = new QHBoxLayout();
        QLabel *label = new QLabel();
        label->setText(tr("Http:"));
        label->setBuddy(&m_urlEdit);
        itemLayout->addWidget(label);
        itemLayout->addWidget(&m_urlEdit);
        layout->addItem(itemLayout);

        itemLayout = new QHBoxLayout();
        label = new QLabel();
        label->setText(tr("Name:"));
        label->setBuddy(&m_fileName);
        itemLayout->addWidget(label);
        itemLayout->addWidget(&m_fileName);
        layout->addItem(itemLayout);



        button.setText(tr("Capture"));
        layout->addWidget(&button);
        setLayout(layout);

        // capture
        m_capture = new FrameCapture();
        connect(m_capture, SIGNAL(finished()), this, SLOT(finish()));

        connect(&button, SIGNAL(clicked()), this, SLOT(load()));
    }

    ~Widget ()
    {
        if (m_capture)
            delete m_capture;
    }


private slots:
    void finish()
    {
        m_urlEdit.setEnabled(true);
        button.setText(tr("Load"));
        QToolTip::showText(QCursor::pos(), "~O~K~", this);
    }

    void load()
    {
        m_urlEdit.setEnabled(false);
        button.setText(tr("Capturing"));
        QString fileName = m_fileName.text();
        if (fileName.isEmpty())
            fileName = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss.png");
        m_capture->load(QUrl::fromUserInput(m_urlEdit.text()), fileName);
    }

private:
    FrameCapture *m_capture;
    QLineEdit m_urlEdit;
    QLineEdit m_fileName;
    QPushButton button;
};

int main(int argc, char * argv[])
{
//    if (argc != 3) {
//        std::cout << "Capture a web page and save its internal frames in different images" << std::endl << std::endl;
//        std::cout << "  framecapture <url> <outputfile>" << std::endl;
//        std::cout << std::endl;
//        std::cout << "Notes:" << std::endl;
//        std::cout << "  'url' is the URL of the web page to be captured" << std::endl;
//        std::cout << "  'outputfile' is the prefix of the image files to be generated" << std::endl;
//        std::cout << std::endl;
//        std::cout << "Example: " << std::endl;
//        std::cout << "  framecapture qt.nokia.com trolltech.png" << std::endl;
//        std::cout << std::endl;
//        std::cout << "Result:" << std::endl;
//        std::cout << "  trolltech.png (full page)" << std::endl;
//        std::cout << "  trolltech_frame1.png (...) trolltech_frameN.png ('N' number of internal frames)" << std::endl;
//        return 0;
//    }



    QApplication a(argc, argv);

//    QUrl url = QUrl::fromUserInput(QString::fromLatin1(argv[1]));
//    QString fileName = QString::fromLatin1(argv[2]);

//    FrameCapture capture;
//    QObject::connect(&capture, SIGNAL(finished()), QApplication::instance(), SLOT(quit()));
//    capture.load(url, fileName);

    Widget widget;
    widget.show();
    return a.exec();
}

#include "main.moc"

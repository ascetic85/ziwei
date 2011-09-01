/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: qt-info@nokia.com
**
** This software, including documentation, is protected by copyright
** controlled by Nokia Corporation.  You may use this software in
** accordance with the terms and conditions contained in the Qt Phone
** Demo License Agreement.
**
****************************************************************************/

#ifndef KINETICSCROLL_H
#define KINETICSCROLL_H

#include <QObject>


class KineticScrollPrivate;

class KineticScroll : public QObject
{
    Q_OBJECT

public:
    KineticScroll(QObject *parent = 0);
    ~KineticScroll();

    void mouseUp(int value);
    bool mouseDown(int value);
    void mouseMove(int value);
    void mouseCancel();
    void kineticStart(qreal speed);
    void kineticStop();

public Q_SLOTS:
    void animator();

Q_SIGNALS:
    void signalMoveOffset(int);

private:
    KineticScrollPrivate *d;
};

#endif

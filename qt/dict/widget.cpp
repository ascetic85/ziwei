#include "widget.h"

#include <QApplication>
#include <QClipboard>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QRegExp>
#include <QLabel>
#include <QCursor>
#include <QToolTip>
#include <QMenu>
#include <QAction>
#include <QSystemTrayIcon>

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    // dict.cn url
    m_url = QString("http://dict.cn/ws.php?utf8=true&q=%1");

    // handle clipboard event from X11
    connect(QApplication::clipboard(), SIGNAL(selectionChanged()),
            this, SLOT(selectionChange()));

    // network
    m_manager = new QNetworkAccessManager(this);
    connect(m_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    // show result
    connect(this, SIGNAL(showDialog(QString)),
            this, SLOT(showDialogWithResult(QString)));

    // system tray init
    createActions();
    createTrayIcon();

    m_trayIcon->setIcon(QIcon(":/images/trash.svg"));
    m_trayIcon->show();
}

Widget::~Widget()
{

}

void Widget::selectionChange()
{
    // people do not want to scan
    if (!m_scanAction->isChecked()) return;

    QString text = QApplication::clipboard()->text(QClipboard::Selection);

    // deal with sentence
    QStringList texts = text.split(QRegExp("[\\W_]"));

    // get first valid word
    foreach(text, texts) {
        m_word = text.remove(QRegExp("[\\W_]"));
        if (m_word != "") {
            m_manager->get(QNetworkRequest(QUrl(m_url.arg(m_word))));
            break;
        }
    }
}

void Widget::replyFinished(QNetworkReply *reply)
{
    QString result = QString::fromUtf8(reply->readAll());
    QRegExp regExp("<def>.*</def>.");
    regExp.indexIn(result);

    emit showDialog(regExp.cap().remove(QRegExp("<def>|</def>")));
}

void Widget::showDialogWithResult(QString result)
{
    if (result == QString())
        result = m_word + QString("\nNot Found");
    else
        result.insert(0, m_word + ":\n");
    QToolTip::showText(QCursor::pos(), result);
}

void Widget::createActions()
{
    // scan
    m_scanAction = new QAction(tr("&Scan"), this);
    m_scanAction->setCheckable(true);
    m_scanAction->setChecked(true);

    // quit
    m_quitAction = new QAction(tr("&Quit"), this);
    connect(m_quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void Widget::createTrayIcon()
{
    // menu
    m_trayIconMenu = new QMenu(this);
    m_trayIconMenu->addAction(m_scanAction);
    m_trayIconMenu->addAction(m_quitAction);

    // icon
    m_trayIcon = new QSystemTrayIcon(this);
    m_trayIcon->setContextMenu(m_trayIconMenu);
}

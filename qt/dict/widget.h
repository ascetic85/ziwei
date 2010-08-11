#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QNetworkReply;
class QNetworkAccessManager;
class QAction;
class QMenu;
class QSystemTrayIcon;

// Maybe we need a main window?

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

Q_SIGNALS:
    void showDialog(QString);

private Q_SLOTS:
    void selectionChange();
    void replyFinished(QNetworkReply*);
    void showDialogWithResult(QString);

private:
    void createActions();
    void createTrayIcon();

private:
    QNetworkAccessManager *m_manager;
    QString m_url;
    QString m_word;

    // system tray
    QAction *m_quitAction;
    QAction *m_scanAction;
    QMenu *m_trayIconMenu;
    QSystemTrayIcon *m_trayIcon;
};

#endif // WIDGET_H

#ifndef CONNECTIONLISTDIALOG_H
#define CONNECTIONLISTDIALOG_H

#include <QDialog>
#include <QTreeWidget>
#include <QPushButton>
#include <QList>

class ConnectionListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionListDialog(QWidget *parent = nullptr);
    
    // Get selected connection items
    QList<QTreeWidgetItem*> getSelectedItems() const;
    
private slots:
    void onOkClicked();
    void onCancelClicked();

private:
    void setupUI();
    void populateConnections();
    
    QTreeWidget *m_treeWidget;
    QPushButton *m_okButton;
    QPushButton *m_cancelButton;
};

#endif // CONNECTIONLISTDIALOG_H

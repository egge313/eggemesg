#include "connectionlistdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QStandardPaths>
#include <QApplication>
#include <QStyle>

ConnectionListDialog::ConnectionListDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUI();
    populateConnections();
    setWindowTitle("Connections");
    resize(600, 400);
}

void ConnectionListDialog::setupUI()
{
    // Main layout (vertical)
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Create tree widget with 3 columns
    m_treeWidget = new QTreeWidget(this);
    m_treeWidget->setColumnCount(3);
    m_treeWidget->setHeaderLabels(QStringList() << "Icon" << "Name" << "Connection String");
    m_treeWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_treeWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    
    // Configure column widths
    m_treeWidget->setColumnWidth(0, 50);
    m_treeWidget->setColumnWidth(1, 150);
    m_treeWidget->setColumnWidth(2, 300);
    
    // Add tree widget to main layout
    mainLayout->addWidget(m_treeWidget);
    
    // Button layout (horizontal)
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    
    m_okButton = new QPushButton("OK", this);
    m_cancelButton = new QPushButton("Cancel", this);
    
    connect(m_okButton, &QPushButton::clicked, this, &ConnectionListDialog::onOkClicked);
    connect(m_cancelButton, &QPushButton::clicked, this, &ConnectionListDialog::onCancelClicked);
    
    buttonLayout->addWidget(m_okButton);
    buttonLayout->addWidget(m_cancelButton);
    
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
}

void ConnectionListDialog::populateConnections()
{
    // Sample data: connections with icons, names, and connection strings
    struct ConnectionData {
        const char *icon;
        const char *name;
        const char *connectionString;
    };
    
    ConnectionData connections[] = {
        {"💾", "Production DB", "postgresql://prod.example.com:5432/maindb"},
        {"🧪", "Development DB", "postgresql://dev.example.com:5432/devdb"},
        {"📋", "Test DB", "postgresql://test.example.com:5432/testdb"},
        {"⚙️", "Local DB", "sqlite:///home/user/local.db"},
        {"🔐", "Secure DB", "mysql://secure.example.com:3306/securedb?ssl=true"},
    };
    
    for (const auto &conn : connections) {
        QTreeWidgetItem *item = new QTreeWidgetItem(m_treeWidget);
        item->setText(0, conn.icon);
        item->setText(1, conn.name);
        item->setText(2, conn.connectionString);
    }
}

QList<QTreeWidgetItem*> ConnectionListDialog::getSelectedItems() const
{
    return m_treeWidget->selectedItems();
}

void ConnectionListDialog::onOkClicked()
{
    // Process selected items
    QList<QTreeWidgetItem*> selected = getSelectedItems();
    
    if (selected.isEmpty()) {
        return;
    }
    
    // Example: Print selected connections
    for (QTreeWidgetItem *item : selected) {
        qDebug() << "Selected:" << item->text(1) << "-" << item->text(2);
    }
    
    accept();
}

void ConnectionListDialog::onCancelClicked()
{
    reject();
}

// --- end of connectionlistdialog.cpp ---

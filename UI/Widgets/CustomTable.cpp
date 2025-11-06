/**
 * @file CustomTable.cpp
 * @brief Implementation of CustomTable widget
 *
 * @author Football Field Management System
 * @date 2025-11-06
 */

#include "CustomTable.h"
#include <QHeaderView>

CustomTable::CustomTable(QWidget *parent)
    : QTableWidget(parent)
{
    setupTable();
}

void CustomTable::setupHeaders(const QStringList &headers)
{
    setColumnCount(headers.count());
    setHorizontalHeaderLabels(headers);

    // Auto-resize columns
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void CustomTable::addDataRow(const QStringList &rowData)
{
    int row = rowCount();
    insertRow(row);

    for (int col = 0; col < rowData.count() && col < columnCount(); ++col)
    {
        QTableWidgetItem *item = new QTableWidgetItem(rowData[col]);
        item->setTextAlignment(Qt::AlignCenter);
        setItem(row, col, item);
    }
}

void CustomTable::clearData()
{
    setRowCount(0);
}

void CustomTable::applyModernStyle()
{
    setStyleSheet(R"(
        QTableWidget {
            background-color: #ffffff;
            border: 1px solid #e0e0e0;
            border-radius: 8px;
            gridline-color: #f0f0f0;
            selection-background-color: #e8f5e9;
            selection-color: #2c3e50;
        }
        
        QTableWidget::item {
            padding: 8px;
            border: none;
        }
        
        QTableWidget::item:hover {
            background-color: #f5f5f5;
        }
        
        QHeaderView::section {
            background-color: #2ecc71;
            color: #ffffff;
            padding: 12px;
            border: none;
            font-weight: 600;
            font-size: 13px;
        }
        
        QHeaderView::section:first {
            border-top-left-radius: 8px;
        }
        
        QHeaderView::section:last {
            border-top-right-radius: 8px;
        }
        
        QScrollBar:vertical {
            border: none;
            background: #f0f0f0;
            width: 10px;
            border-radius: 5px;
        }
        
        QScrollBar::handle:vertical {
            background: #bdc3c7;
            border-radius: 5px;
            min-height: 20px;
        }
        
        QScrollBar::handle:vertical:hover {
            background: #95a5a6;
        }
        
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            height: 0px;
        }
    )");
}

void CustomTable::setupTable()
{
    // Basic settings
    setAlternatingRowColors(true);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSortingEnabled(true);

    // Header settings
    verticalHeader()->setVisible(false);
    horizontalHeader()->setStretchLastSection(true);
    horizontalHeader()->setHighlightSections(false);

    // Apply styling
    applyModernStyle();
}

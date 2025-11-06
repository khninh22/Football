/**
 * @file CustomTable.h
 * @brief Custom styled table widget
 * @details Modern table with alternating row colors and custom header
 *
 * @author Football Field Management System
 * @date 2025-11-06
 */

#ifndef CUSTOMTABLE_H
#define CUSTOMTABLE_H

#include <QTableWidget>
#include <QHeaderView>

/**
 * @class CustomTable
 * @brief Styled table widget for data display
 *
 * Features:
 * - Modern styling
 * - Alternating row colors
 * - Custom header styling
 * - Hover effects
 * - Sorting support
 */
class CustomTable : public QTableWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param parent Parent widget
     */
    explicit CustomTable(QWidget *parent = nullptr);

    /**
     * @brief Setup table with column headers
     * @param headers List of column header names
     */
    void setupHeaders(const QStringList &headers);

    /**
     * @brief Add a row of data
     * @param rowData List of data for each column
     */
    void addDataRow(const QStringList &rowData);

    /**
     * @brief Clear all data (keeps headers)
     */
    void clearData();

    /**
     * @brief Apply modern styling to table
     */
    void applyModernStyle();

private:
    /**
     * @brief Setup table appearance and behavior
     */
    void setupTable();
};

#endif // CUSTOMTABLE_H

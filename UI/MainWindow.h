/**
 * @file MainWindow.h
 * @brief Main application window with sidebar navigation
 * @details Modern dashboard-style interface with sidebar and stacked pages
 *
 * @author Football Field Management System
 * @date 2025-11-06
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QWidget>
#include <QVector>

// Forward declarations
class SidebarButton;
class QVBoxLayout;
class QHBoxLayout;
class HeThongQuanLy;

/**
 * @class MainWindow
 * @brief Main application window
 *
 * Features:
 * - Green sidebar with navigation buttons
 * - Stacked pages for different sections
 * - Integration with Core management system
 * - Modern, responsive design
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param parent Parent widget
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor
     */
    ~MainWindow();

private slots:
    /**
     * @brief Handle page navigation
     * @param index Page index to navigate to
     */
    void navigateToPage(int index);

private:
    // UI Components
    QWidget *m_centralWidget;        ///< Central widget
    QHBoxLayout *m_mainLayout;       ///< Main horizontal layout
    QWidget *m_sidebar;              ///< Sidebar container
    QVBoxLayout *m_sidebarLayout;    ///< Sidebar layout
    QStackedWidget *m_stackedWidget; ///< Page container

    // Sidebar buttons
    QVector<SidebarButton *> m_menuButtons; ///< Navigation buttons

    // Core system
    HeThongQuanLy *m_heThong; ///< Management system instance

    // Current page
    int m_currentPage; ///< Current page index

    /**
     * @brief Setup main window properties
     */
    void setupWindow();

    /**
     * @brief Create and setup sidebar
     */
    void setupSidebar();

    /**
     * @brief Create and add all pages
     */
    void setupPages();

    /**
     * @brief Setup connections between components
     */
    void setupConnections();

    /**
     * @brief Create header for a page
     * @param title Page title
     * @return Header widget
     */
    QWidget *createPageHeader(const QString &title);
};

#endif // MAINWINDOW_H

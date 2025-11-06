/**
 * @file SidebarButton.h
 * @brief Custom button widget for sidebar navigation
 * @details Styled button with icon and text for sidebar menu
 *
 * @author Football Field Management System
 * @date 2025-11-06
 */

#ifndef SIDEBARBUTTON_H
#define SIDEBARBUTTON_H

#include <QPushButton>
#include <QIcon>
#include <QString>

/**
 * @class SidebarButton
 * @brief Custom sidebar button with icon and hover effects
 *
 * Features:
 * - Icon + text layout
 * - Hover and active states
 * - Modern flat design
 */
class SidebarButton : public QPushButton
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param iconPath Path to icon file (SVG preferred)
     * @param text Button text
     * @param parent Parent widget
     */
    explicit SidebarButton(const QString &iconPath, const QString &text,
                           QWidget *parent = nullptr);

    /**
     * @brief Set button as active (selected state)
     * @param active True to activate
     */
    void setActive(bool active);

    /**
     * @brief Check if button is active
     * @return True if active
     */
    bool isActive() const { return m_active; }

protected:
    /**
     * @brief Handle mouse enter event
     * @param event Mouse event
     */
    void enterEvent(QEnterEvent *event) override;

    /**
     * @brief Handle mouse leave event
     * @param event Mouse event
     */
    void leaveEvent(QEvent *event) override;

private:
    bool m_active;         ///< Active state flag
    QString m_normalStyle; ///< Normal state style
    QString m_hoverStyle;  ///< Hover state style
    QString m_activeStyle; ///< Active state style

    /**
     * @brief Initialize button styles
     */
    void setupStyles();

    /**
     * @brief Update button appearance based on state
     */
    void updateStyle();
};

#endif // SIDEBARBUTTON_H

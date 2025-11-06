/**
 * @file SidebarButton.cpp
 * @brief Implementation of SidebarButton widget
 *
 * @author Football Field Management System
 * @date 2025-11-06
 */

#include "SidebarButton.h"
#include <QEnterEvent>

SidebarButton::SidebarButton(const QString &iconPath, const QString &text,
                             QWidget *parent)
    : QPushButton(text, parent), m_active(false)
{
    // Set icon
    if (!iconPath.isEmpty())
    {
        setIcon(QIcon(iconPath));
        setIconSize(QSize(24, 24));
    }

    // Configure button
    setCursor(Qt::PointingHandCursor);
    setCheckable(false);
    setMinimumHeight(50);

    // Setup styles
    setupStyles();
    updateStyle();
}

void SidebarButton::setActive(bool active)
{
    m_active = active;
    updateStyle();
}

void SidebarButton::enterEvent(QEnterEvent *event)
{
    QPushButton::enterEvent(event);
    if (!m_active)
    {
        setStyleSheet(m_hoverStyle);
    }
}

void SidebarButton::leaveEvent(QEvent *event)
{
    QPushButton::leaveEvent(event);
    if (!m_active)
    {
        setStyleSheet(m_normalStyle);
    }
}

void SidebarButton::setupStyles()
{
    // Normal state - transparent background
    m_normalStyle = R"(
        QPushButton {
            background-color: transparent;
            color: rgba(255, 255, 255, 0.8);
            border: none;
            border-radius: 8px;
            padding: 12px 16px;
            text-align: left;
            font-size: 14px;
            font-weight: 500;
        }
    )";

    // Hover state - semi-transparent white
    m_hoverStyle = R"(
        QPushButton {
            background-color: rgba(255, 255, 255, 0.1);
            color: #ffffff;
            border: none;
            border-radius: 8px;
            padding: 12px 16px;
            text-align: left;
            font-size: 14px;
            font-weight: 500;
        }
    )";

    // Active state - white background with green text
    m_activeStyle = R"(
        QPushButton {
            background-color: #ffffff;
            color: #2ecc71;
            border: none;
            border-radius: 8px;
            padding: 12px 16px;
            text-align: left;
            font-size: 14px;
            font-weight: 600;
        }
    )";
}

void SidebarButton::updateStyle()
{
    if (m_active)
    {
        setStyleSheet(m_activeStyle);
    }
    else
    {
        setStyleSheet(m_normalStyle);
    }
}

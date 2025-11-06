/**
 * @file StatsCard.h
 * @brief Card widget for displaying statistics
 * @details Modern card with icon, title, value, and trend
 *
 * @author Football Field Management System
 * @date 2025-11-06
 */

#ifndef STATSCARD_H
#define STATSCARD_H

#include <QWidget>
#include <QString>
#include <QColor>

class QLabel;
class QVBoxLayout;
class QHBoxLayout;

/**
 * @class StatsCard
 * @brief Statistics card widget with icon, title, and value
 *
 * Features:
 * - Icon with colored background
 * - Title and subtitle
 * - Large value display
 * - Trend indicator (optional)
 * - Shadow and hover effects
 */
class StatsCard : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param title Card title (e.g., "Tổng doanh thu")
     * @param value Main value to display
     * @param iconPath Path to icon file
     * @param color Card accent color
     * @param parent Parent widget
     */
    explicit StatsCard(const QString &title, const QString &value,
                       const QString &iconPath, const QColor &color,
                       QWidget *parent = nullptr);

    /**
     * @brief Set the main value
     * @param value New value to display
     */
    void setValue(const QString &value);

    /**
     * @brief Set trend indicator
     * @param trend Trend text (e.g., "+12.5%")
     * @param positive True for positive trend (green), false for negative (red)
     */
    void setTrend(const QString &trend, bool positive = true);

    /**
     * @brief Set subtitle text
     * @param subtitle Subtitle text (e.g., "So với tháng trước")
     */
    void setSubtitle(const QString &subtitle);

protected:
    /**
     * @brief Paint event for custom styling
     * @param event Paint event
     */
    void paintEvent(QPaintEvent *event) override;

    /**
     * @brief Mouse enter event for hover effect
     * @param event Enter event
     */
    void enterEvent(QEnterEvent *event) override;

    /**
     * @brief Mouse leave event
     * @param event Leave event
     */
    void leaveEvent(QEvent *event) override;

private:
    QLabel *m_iconLabel;     ///< Icon display
    QLabel *m_titleLabel;    ///< Title label
    QLabel *m_valueLabel;    ///< Main value label
    QLabel *m_trendLabel;    ///< Trend indicator
    QLabel *m_subtitleLabel; ///< Subtitle label
    QColor m_accentColor;    ///< Card accent color
    bool m_hovered;          ///< Hover state

    /**
     * @brief Setup card layout and styling
     */
    void setupUI();
};

#endif // STATSCARD_H

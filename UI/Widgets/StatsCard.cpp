/**
 * @file StatsCard.cpp
 * @brief Implementation of StatsCard widget
 *
 * @author Football Field Management System
 * @date 2025-11-06
 */

#include "StatsCard.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>
#include <QPainterPath>
#include <QEnterEvent>

StatsCard::StatsCard(const QString &title, const QString &value,
                     const QString &iconPath, const QColor &color,
                     QWidget *parent)
    : QWidget(parent), m_accentColor(color), m_hovered(false)
{
    setMinimumSize(250, 140);
    setMaximumHeight(160);
    setCursor(Qt::PointingHandCursor);

    setupUI();

    m_titleLabel->setText(title);
    m_valueLabel->setText(value);

    if (!iconPath.isEmpty())
    {
        QPixmap pixmap(iconPath);
        m_iconLabel->setPixmap(pixmap.scaled(32, 32, Qt::KeepAspectRatio,
                                             Qt::SmoothTransformation));
    }
}

void StatsCard::setValue(const QString &value)
{
    m_valueLabel->setText(value);
}

void StatsCard::setTrend(const QString &trend, bool positive)
{
    m_trendLabel->setText(trend);
    m_trendLabel->setVisible(!trend.isEmpty());

    QString color = positive ? "#27ae60" : "#e74c3c";
    m_trendLabel->setStyleSheet(QString("color: %1; font-weight: 600;").arg(color));
}

void StatsCard::setSubtitle(const QString &subtitle)
{
    m_subtitleLabel->setText(subtitle);
    m_subtitleLabel->setVisible(!subtitle.isEmpty());
}

void StatsCard::setupUI()
{
    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 16, 20, 16);
    mainLayout->setSpacing(8);

    // Top row: Icon + Title
    QHBoxLayout *topRow = new QHBoxLayout();
    topRow->setSpacing(12);

    // Icon with colored background
    QWidget *iconContainer = new QWidget(this);
    iconContainer->setFixedSize(48, 48);
    iconContainer->setStyleSheet(QString(
                                     "background-color: %1; border-radius: 12px;")
                                     .arg(m_accentColor.lighter(150).name()));

    QVBoxLayout *iconLayout = new QVBoxLayout(iconContainer);
    iconLayout->setContentsMargins(8, 8, 8, 8);

    m_iconLabel = new QLabel(iconContainer);
    m_iconLabel->setAlignment(Qt::AlignCenter);
    iconLayout->addWidget(m_iconLabel);

    // Title
    m_titleLabel = new QLabel(this);
    m_titleLabel->setStyleSheet("color: #7f8c8d; font-size: 13px; font-weight: 500;");

    topRow->addWidget(iconContainer);
    topRow->addWidget(m_titleLabel, 1);

    // Value
    m_valueLabel = new QLabel(this);
    m_valueLabel->setStyleSheet("color: #2c3e50; font-size: 28px; font-weight: 700;");

    // Trend and subtitle row
    QHBoxLayout *bottomRow = new QHBoxLayout();
    bottomRow->setSpacing(8);

    m_trendLabel = new QLabel(this);
    m_trendLabel->setStyleSheet("font-size: 12px; font-weight: 600;");
    m_trendLabel->setVisible(false);

    m_subtitleLabel = new QLabel(this);
    m_subtitleLabel->setStyleSheet("color: #95a5a6; font-size: 11px;");
    m_subtitleLabel->setVisible(false);

    bottomRow->addWidget(m_trendLabel);
    bottomRow->addWidget(m_subtitleLabel);
    bottomRow->addStretch();

    // Add all to main layout
    mainLayout->addLayout(topRow);
    mainLayout->addWidget(m_valueLabel);
    mainLayout->addLayout(bottomRow);
    mainLayout->addStretch();

    // Card styling
    setStyleSheet(R"(
        StatsCard {
            background-color: #ffffff;
            border-radius: 12px;
        }
    )");
}

void StatsCard::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Draw shadow
    QPainterPath path;
    path.addRoundedRect(rect(), 12, 12);

    // Shadow effect
    if (m_hovered)
    {
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(0, 0, 0, 15));
        painter.drawRoundedRect(rect().adjusted(0, 2, 0, 2), 12, 12);
    }

    // Draw card background
    painter.setBrush(QColor("#ffffff"));
    painter.setPen(QPen(QColor("#e0e0e0"), 1));
    painter.drawRoundedRect(rect(), 12, 12);

    // Draw accent line at top
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_accentColor);
    painter.drawRoundedRect(QRect(0, 0, width(), 4), 2, 2);
}

void StatsCard::enterEvent(QEnterEvent *event)
{
    Q_UNUSED(event);
    m_hovered = true;
    update();
}

void StatsCard::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_hovered = false;
    update();
}

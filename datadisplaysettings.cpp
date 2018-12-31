#include "datadisplaysettings.h"
#include "datadisplay.h"
#include "ui_datadisplaysettings.h"
#include <QColorDialog>
#include <QDebug>
#include <QPropertyAnimation>

DataDisplaySettings::DataDisplaySettings(QWidget *parent)
    : QFrame(parent)
    , m_menuVisible(false)
    , m_colourDialog(new QColorDialog(this))
{
    setupUi(this);
    // the 7 additional pixel will make the tab widget's upper edge visible
    // indicating that the settings "button" will reveal more when clicked
    m_hiddenHeight = m_display_control_bar->rect().bottomLeft().y() + 7;

    showIcon = m_panel_settings->tabIcon(0);
    hideIcon.addFile(QStringLiteral(":/images/hide_down.svg"));

    connect(m_panel_settings, &QTabWidget::tabBarClicked, this, &DataDisplaySettings::toggleVisibility);
    connect(m_colourDialog, &QColorDialog::colorSelected, this, &DataDisplaySettings::fontColourSelected);
    connect(m_bt_font_colour, &QPushButton::clicked, [this](){ showColourDialog(FONT); });
    connect(m_bt_bg_colour, &QPushButton::clicked, [this](){ showColourDialog(BACKGROUND); });

    setupPropertyChangeActions();
    preparePreview();
}

void DataDisplaySettings::setupPropertyChangeActions()
{
    connect(m_cb_fonts, &QFontComboBox::currentFontChanged, this, &DataDisplaySettings::preparePreview);
}

void DataDisplaySettings::toggleVisibility()
{
    // Create animation
    QPropertyAnimation *animation = new QPropertyAnimation(this, "pos");
    int delta = height() - m_hiddenHeight - 3;
    int end_y = m_menuVisible ? pos().y() + delta : pos().y() - delta;
    QPoint endPos = QPoint(0, end_y);
    // qDebug() << Q_FUNC_INFO << "isVisiable?:" << m_menuVisible << delta << pos() << "==>" << endPos;
    animation->setStartValue(pos());
    animation->setEndValue(endPos);
    animation->start();
    if (m_menuVisible) {
        m_panel_settings->setTabIcon(0, showIcon);
        m_menuVisible = false;
    } else {
        m_panel_settings->setTabIcon(0, hideIcon);
        m_menuVisible = true;
    }
}

void DataDisplaySettings::showColourDialog(SettingsTarget target)
{

    Q_UNUSED(target)
    if (m_colourDialog->isVisible()) m_colourDialog->close();
   // TODO: m_colourDialog->setCurrentColor()
    // get current settings item
    m_colourDialog->open();
}

void DataDisplaySettings::populateTextTypeCombo()
{

}

void DataDisplaySettings::populateBackgroundTypeCombo()
{

}

void DataDisplaySettings::preparePreview()
{
    m_preview_display->clear();

    m_preview_display->setDisplayTime(true);
    m_preview_display->displayData(QByteArray::fromStdString("The quick brown fox jumped over the control field\n"));
    m_preview_display->setDisplayHex(true);
    m_preview_display->displayData(QByteArray::fromStdString("This is hex text"));
}

/**
 * Overriden from Frame
 * @brief DataDisplaySettings::setGeometry
 * @param w
 * @param h
 */
void DataDisplaySettings::setGeometry(const QRect &rect)
{
    QWidget::setGeometry(rect);
    m_panel_settings->resize(rect.width(), m_panel_settings->height());
}

void DataDisplaySettings::fontColourSelected(const QColor &colour)
{
    qDebug() << "colour selected" << colour.rgb();
}

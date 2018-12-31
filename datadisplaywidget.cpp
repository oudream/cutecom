#include "datadisplaywidget.h"
#include "datadisplay.h"
#include "datadisplaysettings.h"

#include <QDebug>
#include <QVBoxLayout>

DataDisplayWidget::DataDisplayWidget(QWidget *parent)
    : QWidget(parent)
    , m_dataDisplay(new DataDisplay(nullptr))
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_dataDisplay);
    m_settingsPanel = new DataDisplaySettings(this);
    // to remove any margins around the content but make space
    // for the hidden settings panel
    mainLayout->setContentsMargins(QMargins(0, 0, 0, m_settingsPanel->hiddenHeight()));
    setMinimumWidth(m_settingsPanel->frameGeometry().width());
}

void DataDisplayWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    QRect rect = geometry();
    //     qDebug() << Q_FUNC_INFO << "new size: " << rect;
    m_settingsPanel->setGeometry(QRect(rect.x(), rect.y() + rect.height() - m_settingsPanel->currentHeight(),
                                       event->size().width(), m_settingsPanel->height()));
    //     qDebug() << Q_FUNC_INFO << "position: " << m_settingsPanel->pos();
}

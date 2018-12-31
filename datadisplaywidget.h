#ifndef DATADISPLAYWIDGET_H
#define DATADISPLAYWIDGET_H

#include <QtWidgets/QWidget>

class DataDisplay;
class DataDisplaySettings;

class DataDisplayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DataDisplayWidget(QWidget *parent = nullptr);
    DataDisplay *getDataDisplay() const { return m_dataDisplay; }

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    DataDisplay *m_dataDisplay;
    DataDisplaySettings *m_settingsPanel;
};

#endif // DATADISPLAYWIDGET_H

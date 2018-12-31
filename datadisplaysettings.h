#ifndef DATADISPLAYSETTINGS_H
#define DATADISPLAYSETTINGS_H

#include "ui_datadisplaysettings.h"
#include <QtWidgets/QFrame>

class QColorDialog;

class DataDisplaySettings : public QFrame, private Ui::DataDisplaySettings
{
    Q_OBJECT
public:
    enum SettingsTarget { FONT, BACKGROUND };
    enum TextType { OUTPUT, HEX, HEX_COUNTER, TIME };
    enum BackgroundType { BG_OUTPUT, BG_TIME };

    explicit DataDisplaySettings(QWidget *parent = nullptr);

    int hiddenHeight() { return m_hiddenHeight; }
    int currentHeight() { return (m_menuVisible) ? height() : m_hiddenHeight; }

    void setGeometry(const QRect &);

    void fontColourSelected(const QColor &colour);

private:
    void toggleVisibility();
    void showColourDialog(SettingsTarget target);
    void populateTextTypeCombo();
    void populateBackgroundTypeCombo();
    void preparePreview();
    void setupPropertyChangeActions();

private:
    /**
     * The space in the y-achsis needed
     * when the panel is collapsed
     * @brief m_hiddenHeight
     */
    int m_hiddenHeight;
    bool m_menuVisible;
    QIcon showIcon;
    QIcon hideIcon;
    QColorDialog *m_colourDialog;
};

#endif // DATADISPLAYSETTINGS_H

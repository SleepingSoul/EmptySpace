#include "settingsstate.h"
#include "gamewindow.h"
#include "settingsscene.h"
#include "sizes.h"
#include <QGraphicsProxyWidget>
#include "sounds.h"
#include <QTimer>
#include <QVBoxLayout>
#include <QSlider>
#include <QGraphicsView>
#include <QLabel>
#include <QPushButton>
#include <QMediaPlayer>
#include <QComboBox>
#include "templates.h"
#include <QApplication>
#include <QCheckBox>

SettingsState::SettingsState(GameWindow *gwd, const int ww, const int wh)
    : wwidth(ww), wheight(wh), game_window(gwd),
      settings(QApplication::organizationName(), QApplication::applicationName())
{
    /*allocate memory for new scene*/
    pstgs_scene = new SettingsScene(wwidth, wheight);
    pstgs_scene->setSceneRect(0, 0, wwidth, wheight);

    /*allocating memory and set up the view*/
    pgraphics_view = new QGraphicsView;
    pgraphics_view->setRenderHint               (QPainter::Antialiasing);
    pgraphics_view->setVerticalScrollBarPolicy  (Qt::ScrollBarAlwaysOff);
    pgraphics_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pgraphics_view->setScene                    (pstgs_scene);

    /*deal with layout*/
    lout = new QGridLayout;
    lout->setContentsMargins(0, 0, 0, 0);
    lout->addWidget(pgraphics_view);

    /*deal with "Volume" label*/
    QGraphicsTextItem *txt_volume = pstgs_scene->addText("Volume:");
    QFont font;
    font.setBold(true);
    font.setFamily("Arial Black");
    txt_volume->setFont(font);
    txt_volume->setDefaultTextColor(Qt::white);
    txt_volume->setPos(100, 140);

    /*deal with buttons */
    btn_to_menu = new QPushButton;
    setUpButton(btn_to_menu, "media/btnBackMenu.png");
    connect(btn_to_menu, SIGNAL(clicked(bool)), SLOT(slotBtnToMenuClicked()));


    /*allocate memory and set up the volume slider*/
    volume_slider = new QSlider;
    volume_slider->setStyleSheet(
                       "QSlider::groove:horizontal {"
                           "height: 30px;"
                           "min-width: 500px;"
                           "background-color: #586d8b;"
                        "}"

                       "QSlider::handle:horizontal {"
                           "background-color: lightblue;"
                           "border: 1px solid #5c5c5c;"
                           "width: 10px;"
                       "}");

    volume_slider->setRange(0, 100);
    volume_slider->setOrientation(Qt::Horizontal);
    volume_slider->setFixedSize(500, 30);
    /*we will transfer signal from slider just to our main class for music
     * (1 lvl higher then we are now)*/
    connect(volume_slider, SIGNAL(valueChanged(int)), SLOT(slotChangeVolume(int)));

    wp_combo_box = new QComboBox;
    wp_combo_box->addItem("Classic (dark space and battlecruiser)");
    wp_combo_box->addItem("Custom (zergs and damaged battlecruiser)");
    wp_combo_box->setStyleSheet(
                "QComboBox {"
                    "border: 1px solid gray;"
                    "border-radius: 3px;"
                    "padding: 1px 18px 1px 3px;"
                    "min-width: 6em;"
                    "background-color: #586d8b;"
                    "color: white;"
                "}"

                "QComboBox:editable {"
                    "background: white;"
                    "background-color: #586d8b;"
                "}"
                "QComboBox QAbstractItemView {"
                    "border: 2px solid darkgray;"
                    "color: white;"
                    "selection-background-color: lightblue;"
                    "background-color: #586d8b;"
            "}");

    connect(wp_combo_box, SIGNAL(currentIndexChanged(int)), SLOT(slotWpChangeApplied(int)));

    /*Notifications en/dis check box:*/
    ntf_check_box = new QCheckBox;
    ntf_check_box->setText("Enable tips");
    ntf_check_box->setStyleSheet(
                "QCheckBox {"
                    "spacing: 5px;"
                "}"
                "QCheckBox::indicator {"
                    "width: 13px;"
                    "height: 13px;"
                "}"
                ""
                ""
                ""
                "");

    /*Combo box undertext*/
    QGraphicsTextItem *txt_combo_box = pstgs_scene->addText("Choose background theme:");
    txt_combo_box->setFont(font);
    txt_combo_box->setDefaultTextColor(Qt::white);
    txt_combo_box->setPos(100, 210);


    /*make widgets proxy to place it in scene*/
    QGraphicsProxyWidget *proxy_slider = pstgs_scene->addWidget(volume_slider);
    QGraphicsProxyWidget *proxy_btn = pstgs_scene->addWidget(btn_to_menu);
    QGraphicsProxyWidget *proxy_combo_box = pstgs_scene->addWidget(wp_combo_box);
    QGraphicsProxyWidget *proxy_check_box = pstgs_scene->addWidget(ntf_check_box);
    proxy_btn->setPos(50, 50);
    proxy_slider->setPos(100, 170);
    proxy_combo_box->setPos(100, 240);
    proxy_check_box->setPos(100, 310);

    /*allocating memory and set up mediaplayer for
     * sound of clicking on button*/
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile(SELECT_SOUND));

    timer_before_change = new QTimer(this);

    /*We read user settings*/
    readSettings();

    /*Set up state widget*/
    state_widget = new QWidget;
    state_widget->setFixedSize(wwidth, wheight);
    state_widget->setLayout(lout);
}

SettingsState::~SettingsState()
{
    writeSettings();
    delete lout;
    delete player;
    delete pstgs_scene;
    delete pgraphics_view;
}

QWidget *SettingsState::getStateWidget() const
{
    return state_widget;
}

void SettingsState::slotChangeVolume(int v)
{
    /*this slot transfer volume change to gamewindow*/
    emit signalChangeVolume(v);
}

void SettingsState::slotBtnToMenuClicked()
{
    player->play();
    connect(timer_before_change, SIGNAL(timeout()), SLOT(slotMenuState()));
    timer_before_change->start(CHANGE_T_MS);
}

void SettingsState::slotMenuState()
{
    timer_before_change->stop();
    player->stop();
    game_window->setState(State::MainMenu);
}

void SettingsState::readSettings()
{
    settings.beginGroup("/Settings");

    volume_slider->setValue(settings.value("/volume", 100).toInt());
    wp_combo_box->setCurrentIndex(settings.value("/bg_index", 0).toInt());

    settings.endGroup();
}

void SettingsState::writeSettings()
{
    settings.beginGroup("/Settings");

    settings.setValue("/volume", volume_slider->value());
    settings.setValue("/bg_index", _last_background_index);

    settings.endGroup();
}

void SettingsState::slotWpChangeApplied(int idx)
{
    _last_background_index = idx;
    emit signalChangeWallpaper(idx);
}

int SettingsState::Volume() const
{
    return volume_slider->value();
}

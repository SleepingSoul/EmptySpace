#include "settingsstate.h"
#include "gamewindow.h"
#include "settingsscene.h"
#include "sizes.h"
#include <QGraphicsProxyWidget>
#include "sounds.h"

#define CHANGE_T_MS 250

SettingsState::SettingsState(const int vol)
{
    /*allocate memory for new scene*/
    pstgs_scene = new SettingsScene(WWIDTH, WHEIGHT);
    pstgs_scene->setSceneRect(0, 0, WWIDTH, WHEIGHT);

    /*allocating memory and set up the view*/
    pgraphics_view = new QGraphicsView;
    pgraphics_view->setRenderHint               (QPainter::Antialiasing);
    pgraphics_view->setVerticalScrollBarPolicy  (Qt::ScrollBarAlwaysOff);
    pgraphics_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pgraphics_view->setScene(pstgs_scene);

    /*deal with layout*/
    lout = new QVBoxLayout;
    lout->setContentsMargins(0, 0, 0, 0);
    lout->addWidget(pgraphics_view);

    /*deal with "Volume" label*/
    lbl_volume = new QLabel("Volume: ");
    QFont font;
    font.setBold(true);
    font.setFamily("Arial Black");
    lbl_volume->setFont(font);
    lbl_volume->setFixedSize(100, 50);

    /*deal with button "Back to menu"*/
    btn_to_menu = new QPushButton;
    btn_to_menu->setIcon(QIcon(QPixmap("btn_tomenu.png")));
    btn_to_menu->setIconSize(QSize(175, 50));
    btn_to_menu->setFixedSize(175, 50);
    connect(btn_to_menu, SIGNAL(clicked(bool)), SLOT(slotBtnToMenuClicked()));

    /*allocate memory and set up the slider for volume*/
    volume_slider = new QSlider;
    volume_slider->setFixedSize(300, 50);
    volume_slider->setRange(0, 100);
    volume_slider->setSingleStep(1);
    volume_slider->setOrientation(Qt::Horizontal);
    volume_slider->setValue(vol);
    /*we will transfer signal from slider just to our main class for music
     * (1 lvl higher then we are now)*/
    connect(volume_slider, SIGNAL(valueChanged(int)), SLOT(slotChangeVolume(int)));

    /*make widgets proxy to place it in scene*/
    QGraphicsProxyWidget *proxy_slider = pstgs_scene->addWidget(volume_slider);
    QGraphicsProxyWidget *proxy_lbl = pstgs_scene->addWidget(lbl_volume);
    QGraphicsProxyWidget *proxy_btn = pstgs_scene->addWidget(btn_to_menu);
    proxy_btn->setPos(30, 30);
    proxy_slider->setPos(100, 100);
    proxy_lbl->setPos(100, 80);

    /*allocating memory and set up mediaplayer for
     * sound of clicking on button*/
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile(SELECT_SOUND));

    timer_before_change = new QTimer(this);
}

SettingsState::~SettingsState()
{
    //delete bg;
    delete lout;
    delete player;
    delete pstgs_scene;
    delete pgraphics_view;
    qDebug() << gwd->children().size();
}

void SettingsState::buildWindowState(GameWindow *gwd)
{
    this->gwd = gwd;
    gwd->setLayout(lout);
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
    gwd->setState(State::MainMenu);
}

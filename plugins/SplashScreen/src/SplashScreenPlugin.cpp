#include "SplashScreenPlugin.h"
#include "PluginManager.h"

#include <QPixmap>
#include <iostream>
#include <QTimer>

namespace Eagle
{
SplashScreenPlugin::SplashScreenPlugin()
{
    m_splashScreen = new QSplashScreen(QPixmap("://splash.png"));
}

bool  SplashScreenPlugin::init(const PluginManager *manager)
{
    bool  res = false;

    if (nullptr != manager)
    {
        std::cout << "SplashScreenPlugin plugin load !" << std::endl;

        m_splashScreen->show();

        connect(manager, SIGNAL(done()), this, SLOT(done()) );

        res = true;
    }

    return res;
}

void SplashScreenPlugin::done()
{
    QTimer::singleShot(2000, this, [this]()
    {
        m_splashScreen->close();
    });

}
}

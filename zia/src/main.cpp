/*
** EPITECH PROJECT, 2021
** Zia
** File description:
** main
*/

#include "ZIApplication.hpp"
#include "ZServer.hpp"
#include "ModuleLoader.hpp"
#include "Mediator.hpp"

int main(int argc, char **argv)
{
    WApplication app(argc, argv);
    /// Set clean exit for ZIA
    app.setCleanExit();
    /// Test load Zia config
    app.init();

    /// Test TCP Connection
    //ZServer myServer;
    //Mediator *mediator = new Mediator();
    //myServer.start("ZIA Server", 8080, mediator);

    //Load Module(s)
    //ModuleLoader mLoader(mediator);

    return app.exec();
}

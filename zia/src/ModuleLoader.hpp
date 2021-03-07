/*
** EPITECH PROJECT, 2021
** Zia
** File description:
** ModuleLoader
*/

#ifndef MODULELOADER_HPP_
#define MODULELOADER_HPP_

#include "IModule.hpp"
#include "Mediator.hpp"
#include <QObject>
#include <QPluginLoader>
#include <QString>

class ModuleLoader {
    public:
        ModuleLoader(Mediator *mediator);
        ~ModuleLoader();

    protected:
    private:
        IModule *_plugin;
};

#endif /* !MODULELOADER_HPP_ */

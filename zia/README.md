B-YEP-500-TLS-5-1-zia-remi.deschamps

## Compilation
#### Linux
##### Prérequis
Avant tout, il faut avoir CMake d'installé sur son poste.
* \$ sudo apt-get cmake

Ainsi que conan.
* \$ pip install conan

##### Commandes
* Ensuite il suffit de compiler avec le fichier :
* \$> ./set_up_conan_linux.bat
* \$> ./build_linux.sh
* L'exécutable se trouve dans /build/bin/WZIA
* Les modules se trouvent dans /build/lib/

#### Windows
##### Prérequis

Afin de pouvoir compiler il faut avoir Visual Studio 2019.
* Télécharger le programme d'installation en prenant la version "Community" suivant : https://visualstudio.microsoft.com/fr/downloads/?rr=https%3A%2F%2Fwww.google.com%2F
* Ensuite installer la version 2019 de Visual Studio

Ainsi que cmake.
* Télécharger le programme d'installation en prenant "Windows win64-x64 Installer" la version .msi : https://cmake.org/download/
* /!\ IMPORTANT /!\ Pour l'installation il faudra cocher la case "add cmake to the system PATH for the current user" /!\ IMPORTANT /!\

Et pour finir vous aurez besoin de conan.
* Télécharger le programme d'installation en prenant la version Windows : https://conan.io/downloads.html
* /!\ IMPORTANT /!\ Pendant l'installation il faudra cocher la case "add conan to the current user path" /!\ IMPORTANT /!\

##### Commandes

* Ensuite il suffit de compiler avec le fichier :
* \$> ./set_up_conan_windows.bat
* \$> ./build_windows_release.bat
* L'exécutable se trouve dans /build/bin/WZIA.exe
* Les modules se trouvent dans /build/bin/

## /!\ IMPORTANT /!\
TOUJOURS mettre le dossier build/ dans le .gitignore

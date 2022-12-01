# LibRobots

Une librairie pour le projet des robots.
Ici on va ajouter au fur et à mesure des outils pour faciliter la programmation des robots.
Pour le moment il y a la définition de la class virtuelle pour les robots, et un outil pour
séparer un string en plusieurs parties.

Pour utiliser la librairie, ajoutez les lignes suivantes dans votre `CMakeLists.txt`:

```cmake
include(FetchContent) # once in the project to include the module

FetchContent_Declare(librobots
        GIT_REPOSITORY https://github.com/HEIGVD-PRG1-F-2022/librobots.git
        GIT_TAG v0.1.1
        )
FetchContent_MakeAvailable(librobots)

# Here are your other declarations, like `add_executable`

# Replace `PROJECT` with the name of your executable
target_link_libraries(PROJECT PRIVATE librobots)
```

Après vous pouvez utiliser la librairie en l'important et déclarant votre classe comme
implémentant la classe abstraite `Robot`:

```c++
#include <librobots.h>

class MyRobot : public Robot {
    // Implement all virtual methods here
}

int main(){
    vector<Robot> robots = {new MyRobot()};
    // Utiliser le vecteur 'robots'
    return 0;
}
```

Pour un exemple plus complet, voir [exemple](example/main.cpp).
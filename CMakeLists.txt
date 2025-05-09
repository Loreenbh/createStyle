cmake_minimum_required(VERSION 3.10)  # Spécifie la version minimale de CMake
project(MonJeu)                      # Nom de ton projet

# Si SFML_DIR est défini, on l'utilise pour indiquer où se trouve SFML
option(SFML_DIR "Chemin vers le répertoire de SFML" "")

# Si SFML_DIR est défini, utilise ce répertoire pour les includes et lib de SFML
if(SFML_DIR)
    set(SFML_INCLUDE_DIR "${SFML_DIR}/include")
    set(SFML_LIB_DIR "${SFML_DIR}/build/lib")
else()
    message(FATAL_ERROR "SFML n'est pas trouvé. Veuillez spécifier le chemin de SFML avec SFML_DIR ou compiler SFML.")
endif()

# Ajout des fichiers sources de ton jeu
add_executable(MonJeu
    srcs/main.cpp
    srcs/Game.cpp
    srcs/Graphic.cpp
    srcs/GraphicMenu.cpp
    srcs/GraphicHelp.cpp
    # Ajoute ici d'autres fichiers .cpp si nécessaire
)


# Inclure les fichiers d'en-tête de SFML et de ton propre projet
target_include_directories(MonJeu PRIVATE
    ${SFML_INCLUDE_DIR}            # Include des fichiers SFML
    ${CMAKE_SOURCE_DIR}/includes   # Include de tes fichiers .hpp locaux
)

# Lier les bibliothèques statiques de SFML et autres dépendances
target_link_libraries(MonJeu PRIVATE
    ${SFML_LIB_DIR}/libsfml-graphics-s.a
    ${SFML_LIB_DIR}/libsfml-window-s.a
    ${SFML_LIB_DIR}/libsfml-system-s.a
    -lX11 -lXrandr -lXcursor -lGL -lfreetype -ljpeg -lpthread 
    -ludev -lXi
)
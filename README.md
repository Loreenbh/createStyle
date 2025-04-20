# Mon Jeu

## Prérequis

Avant de compiler le projet, assurez-vous d'avoir SFML installé sur votre machine. Vous pouvez soit :

<!-- git clone --branch 2.5.1 https://github.com/SFML/SFML.git SFML-2.5.1
cd SFML-2.5.1
 -->
1. **Utiliser une version précompilée de SFML** (il suffit de télécharger et de spécifier le chemin avec `SFML_DIR` dans CMake).
2. **Compiler SFML vous-même** :
   - Clonez le dépôt SFML :  
     `git clone --recursive https://github.com/SFML/SFML.git`
   - Compilez SFML en statique :
     ```bash
     cd SFML
     mkdir build
     cd build
     cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=FALSE -DSFML_DIR=/chemin/vers/SMFL ou export
     make -j$(nproc)
     ```
   - Utilisez CMake dans votre projet pour lier les bibliothèques SFML statiques.

## Compilation

Clonez ce projet, puis compilez-le avec CMake :
```bash
git clone https://github.com/ton_utilisateur/MonJeu.git
cd MonJeu
mkdir build
cd build
cmake ..
make

# git clone --branch 2.5.1 https://github.com/SFML/SFML.git SFML-2.5.1

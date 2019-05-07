YaJuGo, jeu d'exploration de donjon rogue-like. Projet réalisé dans le cadre de l'UE LIFAP4 (UCBL).
Auteurs : GROSJEAN Justin, HAMDI Yacine et MESSINA Hugo
Numéros étudiants : p1709013, p1709958, p1703726

Sources graphiques et audio : Toutes les images ont été réalisées par le groupe.
Les musiques et bruitages appartiennent à SQUARE-ENIX.

Conseils d'utilisation : Il est conseillé de compiler ce programme sous Linux.

Comment compiler et lancer le jeu :
- Ouvrir un terminal à la racine du dossier
- Exécuter la commande "make" pour compiler le programme
- Pour lancer la version de votre choix (texte ou graphique), exécuter la commande "./bin/yajugo_txt.exe" ou "./bin/yajugo_sfml.exe"
- Pour nettoyer le dossier des fichiers objets et exécutables, exécuter la commande "make clean"

A propos du jeu :
- Le principe du jeu consiste en l'exploration de donjons : vous devez sortir sain et sauf du donjon choisi, sans vous faire tuer par les nombreux monstres qui peuplent les étages.
- Vous avez le choix entre trois types de héros aux compétences et statistiques distinctes : Guerrier, Mage ou Voleur.
- Le jeu possède une dimension RPG au tour par tour : vous devez surveiller vos points de vie pour survivre et vos points de magie pour lancer vos compétences.
- Vaincre des monstres vous rapporte de l'expérience. Accumulez de l'expérience pour monter de niveau.
- En montant de niveau, vous débloquerez parfois des compétences propres à votre type de héros.
- Pour visualiser une compétence, appuyez sur C. Pour ouvrir votre inventaire, appuyez sur I.
- Trois fichiers de sauvegardes sont mis à votre disposition pour vous permettre de tester les 3 types de héros si vous le souhaitez.
- Vous aurez le choix entre différents donjons, classés par difficulté croissante. Un niveau minimal est demandé pour pouvoir accéder à chaque donjon.
- Les donjons sont composés de plusieurs étages. Vous devrez trouver l'escalier de chaque étage pour avancer dans le donjon.
- Au dernier étage, il est question d'achever tous les ennemis pour pouvoir sortir du donjon (Boss de fin de niveau)
- Chaque étage est généré aléatoirement, donc chacune de vos parties sera unique.

Touches : (vérifiez que les majuscules soient désactivées)
- z/q/s/d ou haut/gauche/bas/droit pour vous déplacer. Une rotation ne fait pas passer votre tour, tandis qu'un déplacement si.
- c : menu des compétences. Naviguez dans le menu grâce aux touches de déplacement et appuyez sur Espace pour utiliser une compétence.
- i : inventaire. Naviguez dans le menu grâce aux touches de déplacement et appuyez sur Espace pour utiliser un objet, et J pour en poser au sol sans l'utiliser.

Organisation du dossier :
- bin/ : les fichiers exécutables du jeu, "yajugo_txt.exe" (version texte) et "yajugo_sfml.exe" (version graphique).
Un programme de test regression "test.exe" est également disponible pour mettre en avant les différents modules du projet.
- src/ : l'ensemble des fichiers sources du jeu (*.cpp). Le moteur du jeu se trouve dans "core/" et les différentes solutions d'affichages dans "txt/" et "sfml/"
- obj/ : l'ensemble des fichiers objets crées lors de la compilation. (*.o)
- extern/ : les bibliothèques externes utilisées : "Linux/" contient l'installation de SFML pour Linux.
- data/ : l'ensemble des données du jeu : les listes de données (compétences, objets, donjons...), les images, les musiques/bruitages, les sauvegardes, les salles (pour la génération procédurale)
- doc/ : la documentation des fichiers sources. Ouvrir index.html pour la visualiser.

Une démo de gameplay est diponible sur youtube : https://youtu.be/xw8vGe3CO0k

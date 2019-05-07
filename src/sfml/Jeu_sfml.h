#ifndef JEU_SFML
#define JEU_SFML

#include <cstdlib> /*! \headerfile cstdlib */
#include <SFML/Graphics.hpp> /*! \headerfile "SFML/Graphics.hpp" */
#include <SFML/Audio.hpp> /*! \headerfile "SFML/Audio.hpp" */
#include "../core/Jeu.h" /*! \headerfile "../core/Jeu.h" */
#define LARGEUR 1920 /*! \def LARGEUR */
#define HAUTEUR 1080 /*! \def HAUTEUR */
//#define LARGEUR 3840 /*! \def LARGEUR_4K */
//#define HAUTEUR 2160 /*! \def HAUTEUR_4K */
#define TAILLE_SPRITE 100 /*! \def TAILLE_SPRITE */
#define NB_SPRITES 57 /*! \def NB_SPRITES */
/*!
 * \file Jeu_sfml.h
 * \brief Fichier en-tête pour SFML
 * \author J. Grosjean, Y. Hamdi, H. Messina
 * \version 1.0
 * \date 15/04/2019
 */

struct ListeTextures{ // charger toutes les textures afin d'en dclarer le moins possible = performances ++
/*!
 * \struct ListeTextures
 * \brief Liste des textures du jeu
 */
unsigned int nbTextures;/*!< Nombre de textures */
sf::Texture * textures;/*!< Pointeur vers un tableau de textures */
};

/*!
 * \class Jeu_sfml Jeu_sfml.h
 * \brief Classe de SFML
 */
class Jeu_sfml{
public:
/*!
 * \brief Construteur
 */
  Jeu_sfml();
  /*!
   * \brief Destructeur
   */
  ~Jeu_sfml();
  /*!
  * \fn void boucleSFML()
  * \brief Procédure: Provoque une boucle qui fait dérouler le jeu tel qu'il a été initialisé.
  * \details La procédure n'est appelé qu'une seule fois
  */
  void boucleSFML();
  bool demanderContinuer();
  bool fenetreOuverte();

private:
  Jeu jeu;
  ListeTextures ltex;
  sf::RenderWindow * fenetre;
  sf::Music musique;
  sf::SoundBuffer buffer, buffer2, buffer3;
  sf::Sound son, son2, son3;
  unsigned int choixSauvegarde;
  unsigned int choixDonjon;

  sf::Texture image_curseur, im_fond, im_menu, im_console;
  sf::Sprite curseur, fond, menu, console;
  sf::Font police;
  sf::Text texte;
  void initialiserListeTextures();
  void effacerListeTextures();
  unsigned int selectionnerJoueur();
  unsigned int selectionnerDonjon();
  void saisirInfosNouvellePartie();
  void afficherSFML();
  void ecrireConsole(string message);
  void afficherMessageConsole(string message, char ok = 'E');
  bool questionConsole(string message, string option1="Oui", string option2="Non");
  void afficherCompetences(unsigned int choix);
  void afficherInventaire(unsigned int choix);
  char lireTouche();
};

#endif // JEU_SFML

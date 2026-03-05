# BTTF Shooter 

**BTTF Shooter** est un jeu de tir (Shoot 'em up) dynamique développé en **C++** utilisant la bibliothèque **SFML**. Plongez dans des combats intenses, gérez vos ressources et utilisez des technologies futuristes pour vaincre des vagues d'ennemis et des boss redoutables.

---

##  Fonctionnalités Clés

- **Système d'Armes Abstrait** : Utilisation d'une classe de base `Weapon` avec plusieurs types (Blaster, Gravity Launcher) possédant leurs propres mécaniques et munitions.
- **Gestion des Munitions & Reload** : Système de recharge avec la touche `R` pour le Blaster.
- **Mécanique de "Gravity Bubble"** : Utilisable avec le Launcher (Switch via `TAB`), attire les ennemis et les fait exploser.
- **Sélection d'Appareils** : Choisissez votre vaisseau avant de partir en mission.
- **Power-Ups** : Récupérez des bonus de **Vie** ou de **Force** sur le champ de bataille pour survivre plus longtemps.
- **Gestion des Boss** : Affrontez des boss uniques avec des patterns d'attaque spécifiques.
- **Audio Immersif** : Système de sons et musiques dynamiques qui s'adaptent à l'état du jeu (Menu, Combat, Boss).
- **Interface Complète** : Menus de réglages (Volume, Plein écran), Aide, et écrans de Victoire/Défaite.

---

##  Commandes

| Action | Commande |
| :--- | :--- |
| **Se déplacer** | `W`, `A`, `S`, `D` |
| **Viser** | Mouvement de la Souris |
| **Tirer** | Clique Gauche |
| **Recharger** | Touche `R` |
| **Changer d'arme** | Touche `TAB` |
| **Pause / Retour** | Interaction via les menus |

---

##  Installation et Compilation

### Prérequis
- Compilateur C++ (GCC/G++)
- Bibliothèque **SFML 2.5+** installée sur votre système.

### Compilation
Le projet utilise un `Makefile` pour simplifier la compilation. Ouvrez un terminal à la racine du projet et lancez :

```bash
make
```

### Exécution
Une fois compilé, lancez le binaire généré :

```bash
./game
```

---

## Architecture Technique

Le projet suit une architecture orientée objet modulaire :

- **`main.cpp`** : Point d'entrée, gère la machine à états globale (Menu -> Jeu -> Game Over).
- **`Level`** : Gère l'orchestration du gameplay, le spawn des entités et les collisions.
- **`Player` & `Enemy`** : Classes de base pour les entités mobiles avec gestion des stats et du rendu.
- **`GravityBubble`** : Module physique spécial gérant l'attraction vectorielle des ennemis.
- **`Sounds`** : Singleton gérant le mixage audio et les ressources sonores.

---

## Structure du Projet

```text
.
├── src/            # Fichiers sources (.cpp)
├── include/        # Fichiers d'en-tête (.hpp)
├── sprites/        # Assets graphiques (textures, effets)
├── Makefile        # Script de compilation
└── README.md       # Documentation du projet
```

---

##  À venir
- Nouveaux types d'ennemis et de patterns.
- Progression sur plusieurs niveaux avec une difficulté croissante.
- Système de score en ligne.

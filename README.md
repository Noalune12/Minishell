### Table des matières
- [Minishell](#minishell)
		- [Table des matières](#table-des-matières)
	- [Ressources pour travailler en groupe avec Git](#ressources-pour-travailler-en-groupe-avec-git)
	- [Git ressources](#git-ressources)
	- [Ligne directrice de nos commits/push/reviews](#ligne-directrice-de-nos-commitspushreviews)
	- [Qu'est-ce que Minishell ?](#quest-ce-que-minishell-)
	- [Autres ressources](#autres-ressources)
		- [Garbage Collector](#garbage-collector)
	- [Fonctions autorisées](#fonctions-autorisées)
	- [Quelques rendus avec erreurs](#quelques-rendus-avec-erreurs-)
	- [Random](#random)

# Minishell

*This project is about creating a simple shell.
Yes, your own little bash.
You will learn a lot about processes and file descriptors.*

---

## Ressources pour travailler en groupe avec Git

## Git ressources
- [Commit nomenclature](https://buzut.net/cours/versioning-avec-git/bien-nommer-ses-commits) *pas une norme mais une bonne pratique*
- [Git branching/merge commandes basiques avec schémas (doc en francais)](https://git-scm.com/book/fr/v2/Les-branches-avec-Git-Branches-et-fusions%C2%A0:-les-bases)
	- [Plus de documentation](https://www.varonis.com/blog/git-branching)
	- [Spécifique au merge](https://www.atlassian.com/git/tutorials/using-branches/git-merge)
	- [Liste de commandes utiles pour les déplacements entre branches](https://www.nobledesktop.com/learn/git/git-branches)
	- [Encore de la doc](https://gist.github.com/Alinaprotsyuk/3d58f8cd52eb03a11283d64beb0e083e) *pas vraiment utile étant donné qu'on a quasi décidé de notre façon de travailler*
- [GitHub pull review (documentation imagée des options disponibles lors des reviews)](https://docs.github.com/fr/pull-requests/collaborating-with-pull-requests/reviewing-changes-in-pull-requests/reviewing-proposed-changes-in-a-pull-request)

---

## Ligne directrice de nos commits/push/reviews

Dans l'ensemble, j'aimerais qu'on suive cette ligne directrice :
- Travailler dans des branches différentes (pour l'instant personnelles)
- Merge ensemble via les pull requests/reviews (au maximum pour les implémentations lourdes)
  - Dans la limite du raisonnable, on n'a pas besoin de request pour des changements mineurs (norme, etc.).
  - ***Toujours prévenir l'autre de pull lorsqu'on a push des modifications dans son coin sans recourir aux requests***
- Ne pas hésiter à mettre des commentaires partout
- Suivre une nomenclature claire pour les commits, au moins préciser le **type** de commit. Pour le sujet et le corps du message, ne pas hésiter à détailler un minimum les fonctionnalités ou changements ajoutés.
- ***whatelse??***
---


### Qu'est-ce que Minishell ?
- [Vidéo YouTube : Introduction à Minishell](https://www.youtube.com/watch?v=yTR00r8vBH8)
- [Documentation sur la création d'un shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
- [Architecture de Minishell](https://whimsical.com/minishell-architecture-big-picture-7b9N8PL3qHrddbs977mQ2J)

---
## Autres ressources
### Garbage Collector
Pas sûr si c'est nécessaire pour le projet, mais voici quelques ressources :
- [Écrire un simple Garbage Collector en C](https://maplant.com/2020-04-25-Writing-a-Simple-Garbage-Collector-in-C.html)
- [BDWGC : Garbage Collector pour C](https://github.com/ivmai/bdwgc)

---

### Random

Décomposition **"./program_name"**
- Dans un chemin (`PATH`), le `/` sépare les répertoires et fichiers dans un système (UNIX/Linux)
- Le point `.` représente le `répertoire actuel`
- `./program_name` indique explicitement ou ce trouve le programme
- `../program_name` ira chercher dans le dossier `parent` au `répertoire actuel`
- **Chemins absolus et chemins relatifs**
  - Chemin absolu:
    - comment toujours par `/` (racine du fichier)
    - exemple : `/bin/ls`
  - Chemin relatif:
    - Ne commence pas par `/`
    - Dépend du `répertoire actuel`
- `.` et `..` permettent d'executer un programme qui n'est pas dans le `PATH`

**Pourquoi `.` n'est pas dans `PATH` par defaut**
- N'importe quel fichier exécutable dans le répertoire courant pourrait etre exécuté sans précaution.

---
### Valgrind and `readline()` leaks

Options a utiliser avec valgrind pour masquer les leaks de `readline()` : **make valgrind**

`valgrind --supressions=.valgrind_suppress.txt --leak-check=full --trace-children=yes --track-fds=yes -- show-leak-kinds=all`

## Fonctions autorisées

**TO DO**

## Quelques rendus avec erreurs :
- [Rendu de Minishell avec erreurs (Push invalidés)](https://projects.intra.42.fr/1331/aascedu)
- [Autre rendu avec erreurs](https://projects.intra.42.fr/projects/42cursus-minishell/projects_users/3658701)
- [Encore un autre rendu](https://projects.intra.42.fr/projects/42cursus-minishell/projects_users/3676106)

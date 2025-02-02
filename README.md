# Minishell

*This project is about creating a simple shell.
Yes, your own little bash.
You will learn a lot about processes and file descriptors.*

---

### Table des matières
- [Minishell](#minishell)
		- [Table des matières](#table-des-matières)
	- [Ressources pour travailler en groupe avec Git](#ressources-pour-travailler-en-groupe-avec-git)
    	- [Git ressources](#git-ressources)
    	- [Ligne directrice de nos commits/push/reviews](#ligne-directrice-de-nos-commitspushreviews)
	- [Qu'est-ce que Minishell ?](#quest-ce-que-minishell-)
	- [Autres ressources](#autres-ressources)
		- [Garbage Collector](#garbage-collector)
    	- [Valgrind and readline() leaks](#valgrind-and-readline-leaks)
	- [Fonctions autorisées](#fonctions-autorisées)
	- [Quelques rendus avec erreurs](#quelques-rendus-avec-erreurs-)
	- [Random](#random)


## Ressources pour travailler en groupe avec Git

### Git ressources
- [Commit nomenclature](https://buzut.net/cours/versioning-avec-git/bien-nommer-ses-commits) *pas une norme mais une bonne pratique*
- [Git branching/merge commandes basiques avec schémas (doc en francais)](https://git-scm.com/book/fr/v2/Les-branches-avec-Git-Branches-et-fusions%C2%A0:-les-bases)
	- [Plus de documentation](https://www.varonis.com/blog/git-branching)
	- [Spécifique au merge](https://www.atlassian.com/git/tutorials/using-branches/git-merge)
	- [Liste de commandes utiles pour les déplacements entre branches](https://www.nobledesktop.com/learn/git/git-branches)
	- [Encore de la doc](https://gist.github.com/Alinaprotsyuk/3d58f8cd52eb03a11283d64beb0e083e) *pas vraiment utile étant donné qu'on a quasi décidé de notre façon de travailler*
- [GitHub pull review (documentation imagée des options disponibles lors des reviews)](https://docs.github.com/fr/pull-requests/collaborating-with-pull-requests/reviewing-changes-in-pull-requests/reviewing-proposed-changes-in-a-pull-request)

---

### Ligne directrice de nos commits/push/reviews

Dans l'ensemble, j'aimerais qu'on suive cette ligne directrice :
- Travailler dans des branches différentes (pour l'instant personnelles)
- Merge ensemble via les pull requests/reviews (au maximum pour les implémentations lourdes)
  - Dans la limite du raisonnable, on n'a pas besoin de request pour des changements mineurs (norme, etc.).
  - ***Toujours prévenir l'autre de pull lorsqu'on a push des modifications dans son coin sans recourir aux requests***
- Ne pas hésiter à mettre des commentaires partout
- Suivre une nomenclature claire pour les commits, au moins préciser le **type** de commit. Pour le sujet et le corps du message, ne pas hésiter à détailler un minimum les fonctionnalités ou changements ajoutés.
- ***whatelse??***

---


## Qu'est-ce que Minishell ?
- [Vidéo YouTube : Introduction à Minishell](https://www.youtube.com/watch?v=yTR00r8vBH8)
- [Documentation sur la création d'un shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
- [Architecture de Minishell](https://whimsical.com/minishell-architecture-big-picture-7b9N8PL3qHrddbs977mQ2J)

---


## Fonctions autorisées

- **Pour toutes les fonctions de GNU Readline, tout est expliqué dans la doc du MIT** : [Programming with GNU Readline](https://web.mit.edu/gnu/doc/html/rlman_2.html)
### `readline()`
- Fais parti de la bibliothèque `GNU Readline`, permet de gérer l'entrée utilisateur avec des fonctionnalité avancées comme l'édition de ligne et l'historique.
- `readline()` récupère une ligne de texte.
- prototype : `char *readline(const char prompt);`
  - **prompt** est la chaine affichée avant l'entrée utilisateur (**pour notre minishell pourquoi pas le pwd actuel (ou uniquement le dossier courant + le nom de la branche git actuelle ?**)) *ALORS: mettre de la couleur cest un enfer + ca nous causera des soucis, peut etre commencer avec quelque chose de simple et a la fin si on veut pimper notre prompt on le ferra (cest du detail)*
  - Elle retourne un pointeur **vers la ligne lue (entrée par l'utilisateur)**, alloué dynamiquement
  - Si l'utilisateur envoie `Ctrl+D`, `readline()` retourne `NULL` (EOF). `Ctrl+D = SIG???` [Ctrl-D behavior detailed](https://stackoverflow.com/questions/1516122/how-to-capture-controld-signal)
  - Tout input dans `readline()` doit etre libéré avec `free()`
  - **Fonctionnalités avancées de `readline()`**
    - Edition de ligne : flèches directionnelles pour se balader et modifier l'entrée.

###  `rl_clear_history()`
- [manpage ???]()
- Permet de supprimer l'historique des commandes stockées par `readline()`
- prototype : `void rl_clear_history(void);`
- Supprime toutes les commandes enregistrées avec ``add_history()``
- **add_history(input)** ajoute une commande a l'historique
- **rl_clear_history()** efface toutes les commandes de l'historique

### `rl_on_new_line()`

---

## Quelques rendus avec erreurs :
- [Rendu de Minishell avec erreurs (Push invalidés)](https://projects.intra.42.fr/1331/aascedu)
- [Autre rendu avec erreurs](https://projects.intra.42.fr/projects/42cursus-minishell/projects_users/3658701)
- [Encore un autre rendu](https://projects.intra.42.fr/projects/42cursus-minishell/projects_users/3676106)

#### Résumé des erreurs trouvées :

- leaks/segfault en jouant avec les export/expands
- leaks/segfault quand on quitte sans executer de commandes
- heredocS
- commandes inconnues
- cd dans un dossier dont le parent à été supprimé
- executer une commande si le PATH à été supprimé mais que le binaire est dans le dossier courant
- "echo |" ??
- env | env | env ...
- "heredoc seul sans commande" ?
- `faire en sorte que ">export a='-l -a'" puis "ls $a" == 'ls -l -a'`
- `env -i ... == export $OLD_PWD=''` *pas du tout sur de moi*
- `./minishell | ./minishell` -> `isatty` *same shit je note sans savoir vraiment le comportement pour linstant*
- `< Makefile cat -e` *exemple de test*
- `grep "something" < infile > outfile` *encore un test*
- `>>>` `>>>>` `>>>><` `|` `|ls` `<|` *et encore*
- **Redirection !!** `echo bonjour > a > b > c` *en bash bonjour je sera ecrit QUE dans c. Si un des fichiers dans la redirection n'existe pas il sera créé. De plus, si l'un des fichiers de la chaine ne possede pas les droits, rien ne ce passe.*
- idée pour les heredoc :  `O_TEMP` option d'`open()`
- `fork cree une copie des variables du programme parent. Donc il faut bien penser a free les variables qui ont ete malloc avant de fork a la fois dans le parent et dans les enfants.`


![alt text](image.png)

---

### Random

Décomposition **"./program_name"**
- Dans un chemin (`PATH`), le `/` sépare les répertoires et fichiers dans un système (UNIX/Linux)
- Le point `.` représente le `répertoire actuel`
- `./program_name` indique explicitement ou ce trouve le programme
- `../program_name` ira chercher dans le dossier `parent` au `répertoire actuel`
- **Chemins absolus et chemins relatifs**
  - Chemin absolu:
    - commence toujours par `/` (racine du fichier)
    - exemple : `/bin/ls`
  - Chemin relatif:
    - Ne commence pas par `/`
    - Dépend du `répertoire actuel`
- `.` et `..` permettent d'executer un programme qui n'est pas dans le `PATH`

**Pourquoi `.` n'est pas dans `PATH` par défaut**
- N'importe quel fichier exécutable dans le répertoire courant pourrait etre exécuté sans précaution.

---
### Valgrind and `readline()` leaks

Options a utiliser avec valgrind pour masquer les leaks de `readline()` : **make valgrind**

`valgrind --supressions=.valgrind_suppress.txt --leak-check=full --trace-children=yes --track-fds=yes -- show-leak-kinds=all`

---

### Random attributs et optimisations

`__attribute__((noreturn))`
- Contexte: Utile pour les fonctions qui une fois appelées, ne reviennent jamais (`exit`).
- **Optimisation** -> le compilateur peut éliminer du code mort qui suivrait un appel a cette fonction.
- **Sécurité** -> Prévenir certains avertissements liés aux chemins de code non atteints.


`__attribute__((always_inline))`
- Contexte: Utile pour les fonctions courtes et souvent appelées (`ft_isspace()` etc pour le parsing)
- Le compilateur insère le code directement à l'endroit ou la fonction est appelée.
- **Performance** -> réduit le surcout d'appel de fonction.

`__attribute__((nonnull (indices)))`
- Contexte: Utile pour indiquer que certains arguments d'une fonctions ne doivent pas etre `NULL`
- Pas sur que ca reproduise le comportement d'un shell je pense pas que ca nous soit utile.

### Autres ressources
### Garbage Collector
Pas sûr si c'est nécessaire pour le projet, mais voici quelques ressources :
- [Écrire un simple Garbage Collector en C](https://maplant.com/2020-04-25-Writing-a-Simple-Garbage-Collector-in-C.html)
- [BDWGC : Garbage Collector pour C](https://github.com/ivmai/bdwgc)

---

liens sur lesquels jetais en train de travailler avant de partir samedi soir:

[minishell tuto ??](https://github.com/achrafelkhnissi/minishell)

[write your own shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)


[personal chatgpt history](https://chatgpt.com/c/6797e03d-6c84-8004-a112-5acbcc432f34)

[42gitbook](https://42-cursus.gitbook.io/guide/rank-03/minishell/functions)

[GNU redirection](https://www.gnu.org/software/bash/manual/bash.html#Redirections)

[GNU pipelines](https://www.gnu.org/software/bash/manual/bash.html#Pipelines)

[shell options (built-in ??)](https://www.quennec.fr/trucs-astuces/syst%C3%A8mes/gnulinux/programmation-shell-sous-gnulinux/param%C3%A9trer-son-environnement-de-travail/les-options-du-shell)


[Parsing #1](https://eli.thegreenplace.net/2012/08/02/parsing-expressions-by-precedence-climbing)

[Parsing #2 - Shunting-Yard algo 1](https://brilliant.org/wiki/shunting-yard-algorithm/)

[Parsing #2 - Shunting-Yard algo 2](https://fr.wikipedia.org/wiki/Algorithme_Shunting-yard)

[Parsing #2 - Shunting-Yard algo 3](https://www.reddit.com/r/ProgrammingLanguages/comments/llc2i3/modifying_the_shuntingyard_algorithm_for_logical/?tl=fr&rdt=38434)

[Abstract syntax tree](https://en.wikipedia.org/wiki/Abstract_syntax_tree)

[Aller à une section spécifique d'un autre Markdown](XXX.md#nom-de-la-section)

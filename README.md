# Minishell

*This project is about creating a simple shell.
Yes, your own little bash.
You will learn a lot about processes and file descriptors.*

## Installation et utilisation

Pour utiliser ce projet sur votre machine locale :

```bash
# Cloner le dépôt
git clone https://github.com/Noalune12/Minishell.git

# Se placer dans le répertoire du projet
cd Minishell

# Compiler le projet
make

# Exécuter le shell
./minishell
```

# Manifeste

Avant de continuer la lecture de ce **README**, voici quelques explications de ce qu'il en est et pourquoi.

**À tout lecteur apeuré par l'ampleur du projet, la lecture de cette partie ne peut qu'être recommandée.**

Nous avons décidé de ne partager que les ressources que nous avons utilisées pour venir à bout de notre *Minishell*.
Au départ, nous pensions détailler la réflexion sur l'implémentation de chaque feature en plus de lister les notions et les outils pour les mettre en place. Avec du recul, nous avons décidé de ne pas le faire : chaque *Minishell* est différent, ce repo n'est et ne sera jamais un guide. Nous n'avons pas la prétention d'en faire un. Voyez le plutôt comme un retour d'expérience et une source de documentation.

Maintenant que le contexte est posé, voici comment se sont passés nos deux mois sur le projet.

Dès le départ, nous avions en tête de rendre le projet le plus complet possible, avec des features supplémentaires que nous trouvions soit intéressantes, soit fun. *Deux mois, c'est long, et se limiter à faire des choses sans prendre du plaisir aurait été pesant.* Nous avons pris le plus tôt possible des décisions sur la façon dont nous allions travailler et faisions des points plusieurs fois par semaine sur l'avancement du projet, les choses à faire et/ou ne pas faire.

Grâce à *Minishell*, nous avons **appris** à tenir une certaine rigueur, mais aussi à mettre en place un travail de groupe efficace au possible ! Avec dès le départ des règles assez strictes :
- Sur le nom de nos branches, la nomenclature de nos commits
- Des pull requests récurrentes
- Puis plus tard la mise en place de Github Actions *(et par la même occasion des tests unitaires)*

Tous ces petits détails ont fait que travailler à deux n'a jamais impacté négativement l'autre mais, au contraire, a permis de constater rapidement son avancée.

> **Un conseil** : prenez à **deux** des décisions rapidement, **tenez-y vous**, et faites le point **régulièrement** sur ce que vous faites ou avez fait !

Concernant la répartition du travail, même si comme beaucoup de groupes nous avons séparé en deux parties (*lexing/parsing - exec*), au final nous avons tous les deux touché aux deux. Il y a eu un gros travail de recherche en amont, une bonne semaine de recherche avant de taper les premières lignes de code qui resteront jusqu'au bout du projet. Cette partie de recherche est propre à chacun : certains fonctionnent en testant, d'autres en mettant en pratique la théorie. Sur ce point, nous avons été assez complémentaires. C'est grâce à cela que nous avons rendu un projet dont la construction repose sur des logiques globales vues lors des recherches et non pas sur du *"recopiage"* de ce que nous avons observé lors de nos phases de tests.

Pour terminer, servez-vous des ressources que nous avons mises à disposition si vous le souhaitez, mais ne vous arrêtez pas là : nous avons en réalité vu tellement plus de choses...

# Table des Matières

- [Minishell](#minishell)
  - [Installation et utilisation](#installation-et-utilisation)
- [Manifeste](#manifeste)
- [Table des Matières](#table-des-matières)
  - [Ressources pour travailler en groupe avec Git](#ressources-pour-travailler-en-groupe-avec-git)
  - [Ressources utilisées/vues](#ressources-utiliséesvues)
    - [Books](#books)
      - [Analyse Lexicale/Parsing](#analyse-lexicaleparsing)
      - [Random links](#random-links)
      - [Man pages](#man-pages)
  - [Informations dump](#informations-dump)
    - [Valgrind and `readline()` leaks](#valgrind-and-readline-leaks)
    - [Attributs et optimisations](#attributs-et-optimisations)
    - [Garbage Collector](#garbage-collector)
    - [Terminal modes](#terminal-modes)
      - [Mode interactif](#mode-interactif)
      - [Mode non interactif](#mode-non-interactif)
      - [Pourquoi faire des distinctions entre les modes](#pourquoi-faire-des-distinctions-entre-les-modes)
  - [Décomposition des concepts](#décomposition-des-concepts)
    - [Analyse lexicale (Lexing) : Découper l'input utilisateur en tokens](#analyse-lexicale-lexing--découper-linput-utilisateur-en-tokens)
    - [Analyse syntaxique (Parsing) : Organiser les tokens](#analyse-syntaxique-parsing--organiser-les-tokens)
    - [Interprétation et exécution](#interprétation-et-exécution)
    - [**Exécution des commandes**](#exécution-des-commandes)


## Ressources pour travailler en groupe avec Git

- [Commit nomenclature](https://buzut.net/cours/versioning-avec-git/bien-nommer-ses-commits)
- [Git branching/merge commandes basiques avec schémas (doc en français)](https://git-scm.com/book/fr/v2/Les-branches-avec-Git-Branches-et-fusions%C2%A0:-les-bases)
	- [Plus de documentation](https://www.varonis.com/blog/git-branching)
	- [Spécifique au merge](https://www.atlassian.com/git/tutorials/using-branches/git-merge)
	- [Liste de commandes utiles pour les déplacements entre branches](https://www.nobledesktop.com/learn/git/git-branches)
- [GitHub pull review (documentation imagée des options disponibles lors des reviews)](https://docs.github.com/fr/pull-requests/collaborating-with-pull-requests/reviewing-changes-in-pull-requests/reviewing-proposed-changes-in-a-pull-request)
- [Github Actions](https://docs.github.com/fr/actions/about-github-actions/understanding-github-actions?learn=getting_started&learnProduct=actions)

---

## Ressources utilisées/vues

- [Write your own shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
- [The Architecture of Open Source Applications (Volume 1)](https://aosabook.org/en/v1/bash.html)

### Books

- [Crafting Interpreters by Robert Nystrom](https://www.google.fr/books/edition/Crafting_Interpreters/q0c6EAAAQBAJ?hl=fr&gbpv=0)
- [The Linux Programming Interface by Michael Kerrisk](https://www.google.fr/books/edition/The_Linux_Programming_Interface/2SAQAQAAQBAJ?hl=fr&gbpv=0)
- [Programmation Shell sous Unix/Linux by Christine Deffaix Rémy](https://www.google.fr/books/edition/Programmation_shell_sous_Unix_Linux/d7l2hA1fAn8C?hl=fr&gbpv=0)

#### Analyse Lexicale/Parsing

- [Compiler/lexical analyzer](https://rosettacode.org/wiki/Compiler/lexical_analyzer#C)
- [Compiler/syntax analyzer](https://rosettacode.org/wiki/Compiler/syntax_analyzer#C)
- [Parsing expressions by precedence climbing](https://eli.thegreenplace.net/2012/08/02/parsing-expressions-by-precedence-climbing)
- [Shunting Yard Algorithm #1](https://brilliant.org/wiki/shunting-yard-algorithm/)
- [Shunting Yard Algorithm #2](https://fr.wikipedia.org/wiki/Algorithme_Shunting-yard)
- [ASTree Graphical Representation](https://github.com/fraqioui/minishell/blob/main/tree.png)
- [Shunting Yard Algorithm Calculator Representation](https://www.youtube.com/watch?v=unh6aK8WMwM)
- [Comp Sci in 5: Shunting Yard Algorithm Calculator Representation (goofy guy video)](https://www.youtube.com/watch?v=Wz85Hiwi5MY)

#### Random links

- [3-3 Signaux (et plus)](https://mtodorovic.developpez.com/linux/programmation-avancee/?page=page_3)
- [Pipes (ma synthèse préférée (de loin!))](https://www.idc-online.com/technical_references/pdfs/information_technology/How_Linux_pipes_work_under_the_hood.pdf)
- [Understanding Shell Expansion (explication plus poussée que le manuel Bash)](https://effective-shell.com/part-6-advanced-techniques/understanding-shell-expansion/)
- [Shell Program Explained](https://youtu.be/ubt-UjcQUYg?si=xo-UOU1YY5098p3t)
- [Recursive Descent Parsing (suite du lien ci-dessus)](https://youtu.be/SToUyjAsaFk?si=7pwlKfqdbji8I_o9)

#### Man pages

- [Complete manpages guide](https://medium.com/better-programming/man-pages-the-complete-guide-800ad93425fe)
- [Generate manpages](https://roperzh.github.io/grapse/)

**Pour toutes les autres notions nécessaires au projet, se référer aux manuels officiels**

- [Bash Reference Manual](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html)
- [Bash Posix](https://pubs.opengroup.org/onlinepubs/9799919799/)

---

## Informations dump

Décomposition **"./program_name"**
- Dans un chemin (`PATH`), le `/` sépare les répertoires et fichiers dans un système (UNIX/Linux)
- Le point `.` représente le `répertoire actuel`
- `./program_name` indique explicitement où se trouve le programme
- `../program_name` ira chercher dans le dossier `parent` au `répertoire actuel`
- **Chemins absolus et chemins relatifs**
  - Chemin absolu:
    - commence toujours par `/` (racine du fichier)
    - exemple : `/bin/ls`
  - Chemin relatif:
    - Ne commence pas par `/`
    - Dépend du `répertoire actuel`
- `.` et `..` permettent d'exécuter un programme qui n'est pas dans le `PATH`

**Pourquoi `.` n'est pas dans `PATH` par défaut**
- N'importe quel fichier exécutable dans le répertoire courant pourrait être exécuté sans précaution.

### Valgrind and `readline()` leaks

Options à utiliser avec valgrind pour masquer les leaks de `readline()` : ```make valgrind```

`valgrind --suppressions=.valgrind_suppress.txt --leak-check=full --trace-children=yes --track-fds=yes --show-leak-kinds=all`


### Attributs et optimisations

`__attribute__((noreturn))`
- Contexte: Utile pour les fonctions qui une fois appelées, ne reviennent jamais (`exit`).
- **Optimisation** -> le compilateur peut éliminer du code mort qui suivrait un appel à cette fonction.
- **Sécurité** -> Prévenir certains avertissements liés aux chemins de code non atteints.


`__attribute__((always_inline))`
- Contexte: Utile pour les fonctions courtes et souvent appelées (`ft_isspace()` etc pour le parsing)
- Le compilateur insère le code directement à l'endroit où la fonction est appelée.
- **Performance** -> réduit le surcoût d'appel de fonction.

`__attribute__((nonnull (indices)))`
- Contexte: Utile pour indiquer que certains arguments d'une fonction ne doivent pas être `NULL`

### Garbage Collector
- [Écrire un simple Garbage Collector en C](https://maplant.com/2020-04-25-Writing-a-Simple-Garbage-Collector-in-C.html)
- [BDWGC : Garbage Collector pour C](https://github.com/ivmai/bdwgc)


### Terminal modes

#### Mode interactif
- Définition: Un programme s'exécute en mode interactif lorsqu'il communique directement avec l'utilisateur via un terminal.
  - **Un prompt est affiché** : invite l'utilisateur à saisir des commandes
  - **Les entrées et sorties** sont directement reliées à un terminal (tty)
  - **Les signaux** sont gérés de manière à permettre à l'utilisateur d'interagir avec le prompt
- Identifier le mode interactif:
  - [isatty](#isatty) sur la `STDIN` (et la `STDOUT`),

#### Mode non interactif
- Définition: Un programme s'exécute en mode non interactif lorsqu'il n'est pas directement lié à un terminal pour l'entrée et/ou la sortie. Dans ce mode:
  - **Pas de prompt interactif** : Le programme ne présente pas de prompt à l'utilisateur, car il lit ses commandes à partir d'un fichier, d'un pipe ou d'une redirection.
  - **Traitement en lot** : Lorsqu'un script shell est exécuté, Bash lit le contenu du fichier de commandes et l'exécute séquentiellement sans intervention manuelle.
  - **Différentes gestions de signaux** : `Ctrl+C` et les autres signaux n'ont pas le même comportement.

#### Pourquoi faire des distinctions entre les modes

- **Fonctionnalités interactives** : Dans le mode interactif, le shell peut activer des fonctionnalités avancées (édition en ligne, historique...) et gérer les interruptions de façon spécifique.
- **Adaptation du comportement** : Si le programme détecte qu'il est en mode non interactif, il peut désactiver l'affichage du prompt ou adopter un comportement différent pour éviter d'afficher des messages qui ne seraient pas utiles.
- **Gestion des erreurs et des signaux** : Comme spécifié dans le mode non interactif, les signaux peuvent avoir des comportements différents entre les modes.
---

## Décomposition des concepts

### Analyse lexicale (Lexing) : Découper l'input utilisateur en tokens

L'input utilisateur, une chaîne de caractères doit être "décomposée" en morceaux significatifs : **tokens**

*Turning the input of characters into a stream of tokens*

**Objectifs de l'analyse lexicale (qu'on appellera Lexer)**
- **Identifier** et **extraire** les éléments syntaxiques (mots, opérateurs, séparateurs, variables d'environnements ?) qui constituent la commande.
- **Types de tokens**
  - **Commandes**: `ls`, `echo`, `cd` ... comprend les commandes **et** les built-in
  - **Arguments**: Les chaînes qui suivent la commande et précisent les paramètres (options pour les fonctions, `-la`, `"Directory..."`, etc). Finalement également considéré comme des commandes.
  - **Opérateurs spéciaux**: Opérateurs logiques `||`, `&&` ; Redirections `>`, `<`, `>>`, `<<` ; pipes `|` ...
  - **Espaces et séparateurs**: Les espaces peuvent séparer des tokens mais peuvent aussi faire partie des chaînes de caractères `" "`
  - **Gestion des guillemets et échappements**: Cas particuliers comme les chaînes de caractères entre guillemets ou les caractères échappés `\` (par exemple) ne doivent pas couper un argument qui contient des espaces ou des caractères spéciaux. La gestion de l'échappement n'étant pas demandée, propre à chacun de s'y atteler.

### Analyse syntaxique (Parsing) : Organiser les tokens

Comprendre la relation des tokens entre eux.

**Objectif du Parser**
- Vérifier la syntaxe (s'assure que la commande est correctement formée) et créer une structure représentant la hiérarchie et les relations entre les tokens. *Référence aux **AST** [Arbre syntaxique abstrait](https://en.wikipedia.org/wiki/Abstract_syntax_tree)* (ou tout autre représentation similaire qui sépare par exemple la commande principale des redirections et des pipes).
- **Structure d'un AST dans Minishell**
  - **Nœud commande**: Représente la commande principale et ses arguments
  - **Nœud opérateur**: Représente les relations qui connecte la sortie d'une commande à l'entrée d'une autre, ou les redirections qui indiquent où lire/écrire les données.
- **Hiérarchie et priorité**: Le parser doit tenir compte des priorités.
  - **Exemple**: `cat file.txt | grep "motif" > output.txt` -> le pipe relie `cat` et `grep`, la redirection s'applique à la sortie de `grep`
  - **Exemple complexe**: `(ls -la > files.txt && cat < files.txt | grep "txt") || (echo "Erreur" >> log.txt)` -> les parenthèses isolent deux groupes de commandes liés par `||`. Dans le premier groupe, `ls` redirige vers un fichier puis `&&` exécute `cat` suivi d'un pipe vers `grep` seulement si `ls` réussit. Si tout le premier groupe échoue, le deuxième groupe s'exécute et redirige sa sortie vers `log.txt` en mode ajout.
- **Validation de la syntaxe**: Implique la vérification de la syntaxe (pas de redirections mal placées ou opérateurs isolés sans commandes associées)

### Interprétation et exécution

Une fois l'**AST** ou la structure des commandes construite, on passe à l'exécution

### **Exécution des commandes**

Pour chaque commande dans l'AST, le shell doit :
- Localiser l'exécutable: Rechercher le chemin complet en utilisant la variable d'environnement `PATH` (et/ou chercher dans le répertoire courant le binaire)
- Créer des processus: `fork()` et `execve()`
- Gérer la communication entre processus: S'il y a `pipe`, connecter la `stdout` d'un processus à la `stdin` du suivant
- Redirections: Modifier les descripteurs de fichiers pour rediriger les entrées/sorties vers/depuis des fichiers, en fonction des opérateurs (`>`, `<`)

> Fonctionnement détaillé et outils nécessaires à l'exécution de commande dans [pipex](https://github.com/AzehLM/pipex/blob/master/README.md)

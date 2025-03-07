### Ce qu'on fait actuellement:

- **Tokenisation** de l'input en separent chaque parametre dans la liste chainee token, **sans** attribué de type a ce token.
- **Split des operateurs** en plusieurs nodes si il y en a plusieurs a la suite colés (`>>>>` devient `>>` , `>>` et `>|<&&` devient `>`, `|`, `<`,`&&`)
- **Check de syntaxe** de la totalite de l'input utilisateur (pas fais mais theoriquement on voulais le mettre la)
- **Gestion des heredocs** si pas d'erreurs de syntaxe
- **Creation de l'arbre** (c'est ici que tu attribue un type a des node)
- **Execution de l'arbre**


### Ce qu'il faut faire (je pleure deja)

## Table des matières
- [Processus de Parsing en Bash POSIX](#processus-de-parsing-en-bash-posix)
- [Stratégie d'Implémentation Recommandée](#stratégie-dimplémentation-recommandée)
- [Avantages du Typage Précoce](#avantages-du-typage-précoce)
- [Exemples de Cas à Gérer](#exemples-de-cas-à-gérer)

## Processus de Parsing en Bash POSIX

Le processus standard utilisé par bash POSIX se déroule en trois phases principales :

### 1. Analyse Lexicale (Lexing)
- Découpe l'entrée utilisateur en tokens distincts
- **Attribue un type** à chaque token (mot, opérateur, etc.)
- Gère les caractères spéciaux comme les quotes et les caractères d'échappement

### 2. Analyse Syntaxique (Parsing)
- Vérifie la grammaire et la syntaxe
- Construit l'AST (Arbre Syntaxique Abstrait) basé sur les types des tokens
- Détecte les erreurs de syntaxe (opérateurs consécutifs, parenthèses non équilibrées, etc.)

### 3. Analyse Sémantique & Exécution
- Effectue l'expansion des variables, wildcards, etc.
- Exécute les commandes selon l'AST généré

## Stratégie d'Implémentation Recommandée

Pour implémenter efficacement votre minishell, voici une approche améliorée par rapport à la tokenization simple sans typage :

### 1. Tokenization avec Typage
```
Créez une énumération de types de tokens :
- WORD        : Mot simple (commande ou argument)
- QUOTED_WORD : Mot entre guillemets (simples ou doubles)
- OPERATOR    : Opérateur shell (avec sous-types)
  - REDIR_IN  : Redirection d'entrée (<)
  - REDIR_OUT : Redirection de sortie (>)
  - APPEND    : Redirection en mode append (>>)
  - HEREDOC   : Here-document (<<)
  - PIPE      : Pipe (|)
  - AND_IF    : ET logique (&&)
  - OR_IF     : OU logique (||)
  - PAREN_OPEN: Parenthèse ouvrante (()
  - PAREN_CLOSE: Parenthèse fermante ())
```

Lors de la tokenization, attribuez immédiatement le type approprié à chaque token.

### 2. Vérification de Syntaxe
Parcourez la liste de tokens typés pour vérifier les règles de syntaxe :
- Un token REDIR_IN/REDIR_OUT/APPEND/HEREDOC doit être suivi d'un token WORD
- Un token PIPE ne peut pas être suivi d'un autre opérateur (sauf PAREN_OPEN)
- Les tokens AND_IF et OR_IF ne peuvent pas être suivis d'un opérateur (sauf PAREN_OPEN)
- Les parenthèses doivent être équilibrées

### 3. Construction de l'AST
Utilisez les types pour guider la construction de l'arbre :
- Les opérateurs deviennent des nœuds internes
- Les mots simples deviennent des feuilles
- Les commandes complexes (avec pipes, redirections) sont structurées selon la hiérarchie appropriée

## Avantages du Typage Précoce

1. **Clarté du Code**
   - Le code de vérification syntaxique devient plus lisible et maintenable
   - Les vérifications sont basées sur des types plutôt que des comparaisons de chaînes

2. **Séparation des Préoccupations**
   - Chaque phase a une responsabilité claire et délimitée
   - La tokenization s'occupe uniquement de l'identification des tokens
   - La vérification syntaxique se concentre sur les règles grammaticales

3. **Meilleure Gestion des Erreurs**
   - Détection précise des erreurs syntaxiques
   - Messages d'erreur plus spécifiques et utiles pour l'utilisateur

4. **Flexibilité**
   - Architecture plus facile à étendre pour ajouter de nouvelles fonctionnalités
   - Support simplifié pour des constructions shell avancées

## Exemples de Cas à Gérer

### Opérateurs Entre Guillemets
Un caractère opérateur placé entre guillemets (simples ou doubles) n'est plus considéré comme un opérateur mais comme un caractère littéral :
```bash
cat ">" file      # Cherche à lire un fichier nommé ">" puis un fichier "file"
ls "|" cat        # Cherche à lister des fichiers nommés "|" et "cat"
echo "<< EOF"     # Affiche littéralement "<< EOF", pas un heredoc
```

### Opérateurs Consécutifs Invalides
```bash
cat > |          # Erreur: redirection suivie d'un pipe
cat < >          # Erreur: redirection suivie d'une autre redirection
ls && |          # Erreur: && suivi d'un pipe
```

### Opérateurs en Fin de Ligne
```bash
cat >            # Erreur: redirection sans cible
echo |           # Erreur: pipe sans commande suivante
ls &&            # Erreur: && sans commande suivante
```

---

En suivant ces directives, votre implémentation du parsing sera robuste et fidèle au comportement de bash POSIX, tout en maintenant un code clair et maintenable.

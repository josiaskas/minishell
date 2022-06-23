# MINISHELL


## 1. Loop (in interactive mode)

#### 1.1 signals
```C
int	minishell_loop(void)
{
  //...
	while (1)
	{
      activate_signal_handling(); // À chaque fois dans la boucle (tous les signaux sont désactivés par certains bout de code)
    //...
  }
   //...
}

void	activate_signal_handling(void)
{
	setup_signal(SIGINT, handle_sigint);
	setup_signal(SIGQUIT, SIG_IGN);
}
```
##### info (readline lib)

Malheureusement `handle_sigint` fait appelle a la fonction `rl_replace_line`, fonction qui est une source de problème pour la librairie readline utiliser sur les Mac (Pour des raisons de licence).

libreadline.a (celle dans le dossier est compilé pour Catelina) est une version spéciale. Le Makefile a été ajuster pour pointer vers le bon chemin.

J'ai délibérément pas voulu prendre les fichiers .h de la lib (42 norminette), j'ai ajouté dans status.h la definition de cette fonction.
```C
void	rl_replace_line(const char *text, int clear_undo);
```

Si vous compilez sous linux il faudra changer les flags ***-L*** dans le Makefile

## 2. Parsing

#### 2.1 tokenizer et lexer

Pour le parsing j'ai choisi de le faire en 3 étapes. Deux d'entre elles sont liées, tokenization et l’analyse lexicale. 
Normalement sur le plan scientifique, c'est sensé designer la meme chose à peu près, [Analyse lexicale](https://fr.wikipedia.org/wiki/Analyse_lexicale). Ce qui est certain, c'est la première partie une partie de mon [Analyseur syntaxique](https://fr.wikipedia.org/wiki/Analyse_syntaxique).

![parser part 1](https://github.com/josiaskas/minishell/blob/5875426d0ce06758f582b8f407b1d7ba1aea160e/github/Parser_part1.jpeg)

- Plus de details sur le tokenizer ici [Tokenizer wiki](https://github.com/josiaskas/minishell/wiki/Tokenizer)
- Plus de details sur le lexer ici [Lexer wiki](https://github.com/josiaskas/minishell/wiki/Lexer)

Le tokenizer peut simplement être modifié en ajoutant des caractères special.

#### 2.2 Le parser

Il permet la création des t_command, une structure, qui va par la suite aider à l'exécution. En cas de problème, par exemple un token inattendu une erreur est créé puis remonte tout l'arbre des t_command. Elle devient ensuite une erreur du parseur. 
- Si le créateur de commande rencontre un token de type pipe. Il commence la creation d'une autre commande, un appel récursif est fait, la commande créer est ensuite mise dans `cmd->pipe`
- Pour le bonus il faudra faire la même chose avec `cmd->next` et set les conditions d'exécutions de `cmd->next`

![parser part 2](https://github.com/josiaskas/minishell/blob/5875426d0ce06758f582b8f407b1d7ba1aea160e/github/parser_minishell_board.jpeg)

- Plus de details sur le lexer ici [Parser wiki](https://github.com/josiaskas/minishell/wiki/Parser)

## 3 Execution

#### 3.1 Redirections

#### 3.2 Heredoc

#### 3.3 Pipeline

by josiaskas
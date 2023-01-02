# Projet Teeko IF2


# Instructions de Compilation


Pour compiler le projet il faut disposer de MinGW, puis exécuter la commande suivante:


```batch
gcc src/*.c -I include -o bin/main -L lib -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf
```

puis pour éxecuter le code:

```batch
bin\main.exe
```

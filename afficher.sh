#!/bin/sh

if [ "$1" = "--help" ]
then
    echo
    echo "Pour générer un .dot et le png d'un arbre, utiliser"
    echo "$0 [-t] <nom_fichier_arbre> <nom_fichier_dest (sans extension)>"
    echo
    echo "Si le fichier .dot a déjà été géneré, utiliser"
    echo "$0 -a [-t] <nom_fichier_dot (sans extension)>"
    echo
    echo "Si le paramètre -t est précisé, le script utilisera twopi au lieu de dot pour générer l'image"
    exit 0
fi

if [ "$1" = "--clean" ]
then 
    rm *.dot *.png
    exit 0
fi

if [ $# -lt 2 ]
then
    echo "Arguments manquants"
    exit 0
fi

# Simplement afficher un arbre au format dot
if [ "$1" = "-a" ]
then
    if [ "$1" = "-t" ]
    then
        twopi -Tpng -o $3.png $3.dot
        code $3.png
    else 
        dot -Tpng -o $2.png $2.dot
        code $2.png
    fi
    exit 0;
fi

make generer_affichage
# Générer puis afficher un arbre au format dot
if [ "$1" = "-t" ]
then
    ./generer_affichage "$2" "$3.dot"
    twopi -Tpng -o $3.png $3.dot
    code $3.png
else 
    ./generer_affichage "$1" "$2.dot"
    dot -Tpng -o $2.png $2.dot
    code $2.png
fi

make clean

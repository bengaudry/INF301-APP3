#!/bin/sh

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

make generer_affichage
# Générer puis afficher un arbre au format dot
if [ "$1" = "-t" ]
then
    ./generer_affichage "$2" "$3.dot"
    twopi -Tpng -o $3.png $3.dot
else 
    ./generer_affichage "$1" "$2.dot"
    dot -Tpng -o $2.png $2.dot
fi

make clean

Little library for compatible vectors with every type/struct

repo : https://github.com/MatthSy/modular_vectors_C

****Work in progress****

.

.

.

.

.

stocker les données en void * ?
(les copier en allouant de la place pour chaque donnée ? pour éviter de perdre la main dessus)

ou en char (1 octet) en enregistrant la taille des objet stockés
-> demande toujours un void* en entrée mais à l'intérieur c'est géré par des char
pas besoin de réallouer de la place pour chaque case (pb du void*)

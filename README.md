# red-black-tree

Cada nodo en un red-black tree tiene un bit extra de información que determina si el nodo es color rojo o negro.

Usando esta información, un red-black tree debe cumplir 5 condiciones que garantizarán que el árbol esté balanceado:

1. Cada nodo es de color rojo o negro
2. La raíz es de color negro
3. Cada hoja es de color negro (los nodos nulos se consideran de color negro)
4. Si un nodo es de color rojo, sus dos hijos deben ser de color negro
5. Para cada nodo, todos los caminos desde el nodo hasta las hojas contienen la misma cantidad de nodos de color negro

Si se cumplen estas condiciones, entonces el camino más largo desde la raíz hasta alguna hoja va a ser a lo mucho el doble que la distancia más corta desde la raíz hasta alguna hoja. Esto significa que la altura del árbol será como máximo 2log(n + 1).

# ToyFactory
Animacion de una fabrica de juguetes usando OpenGL, en la que el usuario pueda elegir una escena u otra para personalizar su robot(grafo) (escenas en un arbol). Tematica navideña.

Secuencia del programa:

- Se le pregunta al usuario por el tipo de robot: constructor (torso grueso, reforzado) / explorador (torso sencillo, delgado)

- Se le pregunta al usuario el color del bloque (torso plastico del robot) verde o azul

- sale un bloque plastico de una caja magica del color y tipo seleccionado

...

Y asi sucesivamente, hasta que el usuario construya su robot. Los modulos del robot estan conectados entre si por medio de grafos/arboles, como Torso->brazo->mano->herramienta, Torso->pierna->pie->propulsor(opcional), Torso->cabeza->casco, lentes

La simulacion seria 3d, pero en un "isometric tilemap".

El primer ambiente es una fabrica como de juguetes de santa, y cuando acaba el usuario de hacer su robot, el usuario puede controlarlo en un mapa generado proceduralmente.

## Requirements
wget https://raw.githubusercontent.com/nothings/stb/master/stb_image.h

# Nota Bene:

Ahora estoy intrigada.

Saludos.

Atte.

Profa.Yuliana Berumen

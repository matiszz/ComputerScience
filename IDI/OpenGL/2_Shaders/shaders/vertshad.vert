#version 330 core

in vec3 vertex;
in vec3 color; // Le llega los colores del .cpp
out vec3 fcolor; // Saca el fcolor

void main()  {
    gl_Position = vec4 (vertex, 1.0); // Aqui és el tamany del triangle.
    fcolor = color; // Decirle que es lo mismo
}

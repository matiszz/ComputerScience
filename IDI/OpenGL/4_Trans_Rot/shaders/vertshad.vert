#version 330 core

in vec3 vertex;
in vec3 color; // Le llega los colores del .cpp
out vec3 fcolor; // Saca el fcolor
uniform float val;
uniform mat4 TG;

void main()  {
   // gl_Position = vec4 (vertex, 1.0); // Aqui és el tamany del triangle.
    fcolor = color; // Decirle que es lo mismo

   // gl_Position = vec4 (vertex * val, 1.0); // Posar el Uniform. EX 0, size.
    gl_Position = TG * vec4 (vertex * val, 1.0); // EX 1, translation
}

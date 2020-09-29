#version 330 core

out vec4 FragColor;
in vec3 fcolor; // Le llega este vec3 del vs.vert

void main() {
    FragColor = vec4(fcolor,1.); // Lo pinta con el fcolor que le ha llegado.
}


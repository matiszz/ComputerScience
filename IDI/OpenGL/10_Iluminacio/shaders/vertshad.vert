#version 330 core

in vec3 vertex;
in vec3 normal;

in vec3 matamb;
in vec3 matdiff;
in vec3 matspec;
in float matshin;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;

// Valors per als components que necessitem dels focus de llum
uniform vec3 colFocus;
uniform vec3 llumAmbient;
uniform vec3 posFocus;

out vec3 fcolor;

vec3 Lambert (vec3 NormSCO, vec3 L) {
    // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats

    // Inicialitzem color a component ambient
    vec3 colRes = llumAmbient * matamb;

    // Afegim component difusa, si n'hi ha
    if (dot (L, NormSCO) > 0)
      colRes = colRes + colFocus * matdiff * dot (L, NormSCO);
    return (colRes);
}

vec3 Phong (vec3 NormSCO, vec3 L, vec4 vertSCO) {
    // Els vectors estan normalitzats

    // Inicialitzem color a Lambert
    vec3 colRes = Lambert (NormSCO, L);

    // Calculem R i V
    if (dot(NormSCO,L) < 0)
      return colRes;  // no hi ha component especular

    vec3 R = reflect(-L, NormSCO); // equival a: normalize (2.0*dot(NormSCO,L)*NormSCO - L);
    vec3 V = normalize(-vertSCO.xyz);

    if ((dot(R, V) < 0) || (matshin == 0))
      return colRes;  // no hi ha component especular
    
    // Afegim la component especular
    float shine = pow(max(0.0, dot(R, V)), matshin);
    return (colRes + matspec * colFocus * shine); 
}

void main() {
  
    // Els hem de normalitzar i tot aixo perque les funcions
    // esperen que els vectors arribin normalitzats.
    mat3 NormalMatrix = inverse( transpose( mat3(view*TG) ) );
    vec3 normSCO = normalize(NormalMatrix*normal);
    vec4 vertSCO = view * TG * vec4(vertex,1.0);
    vec4 focSCO = view * vec4(posFocus, 1.0);
    vec3 L = focSCO.xyz - vertSCO.xyz;
    L = normalize(L);

    // fcolor = Lambert(normSCO, L);
    fcolor = Phong(normSCO, L, vertSCO);

    gl_Position = proj * view * TG * vec4 (vertex, 1.0);
}

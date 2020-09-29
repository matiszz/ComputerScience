#version 330 core

in vec3 fcolor;
out vec4 FragColor;

// M'arriba tot aixo del vertex
in vec3 matamb_o;
in vec3 matdiff_o;
in vec3 matspec_o;
in float matshin_o;
in vec3 NormSCO_o;
in vec4 VertSCO_o;

// Aixo em podria arribar del vertex, però ho vaig a buscar al uniform perquè es mes fàcil
uniform vec3 colFocus;
uniform vec3 llumAmbient;
uniform vec4 posFocus;


vec3 Lambert (vec3 NormSCO, vec3 L) {
    // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats

    // Inicialitzem color a component ambient
    vec3 colRes = llumAmbient * matamb_o;

    // Afegim component difusa, si n'hi ha
    if (dot (L, NormSCO) > 0)
      colRes = colRes + colFocus * matdiff_o * dot (L, NormSCO);
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

    if ((dot(R, V) < 0) || (matshin_o == 0))
      return colRes;  // no hi ha component especular
    
    // Afegim la component especular
    float shine = pow(max(0.0, dot(R, V)), matshin_o);
    return (colRes + matspec_o * colFocus * shine); 
}

void main() {	
	// Normalitzar NormSCO, perquè tot i estar normalitzada al vertex, s'ha de tornar a fer
	vec3 normSCO_o = normalize(NormSCO_o);

	// Calcular L
	vec4 focSCO = posFocus;
	vec3 L = focSCO.xyz - VertSCO_o.xyz;
	L = normalize(L);

	// Cridar phong
	vec3 fcolor = Phong(normSCO_o, L, VertSCO_o);

	FragColor = vec4(fcolor,1);	
}

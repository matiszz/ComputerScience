#version 330 core

out vec4 FragColor;
in vec3 fcolor; // Le llega este vec3 del vs.vert

void main() {
    FragColor = vec4(fcolor,1.); // Lo pinta con el fcolor que le ha llegado.
    
    /*
    if ( gl_FragCoord .x < 357.) {
		FragColor = vec4 (1. ,0. ,0. ,1.);
		if ( gl_FragCoord .y < 357.)
			FragColor = vec4 (1. ,1. ,0. ,1.);
	}
	else {
		FragColor = vec4 (0. ,0. ,1. ,1.);
		if ( gl_FragCoord .y < 357.)
			FragColor = vec4 (0. ,1. ,0. ,1.);
	}*/
	
	// if ( int(gl_FragCoord.y)%20 > 10) discard;
	// if ( int(gl_FragCoord.x)%20 > 10) discard;
}


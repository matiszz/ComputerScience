#include "MyGLWidget.h"
#include <iostream>

// Constructora
MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent) {
     setFocusPolicy(Qt::ClickFocus);  // per rebre events de teclat
     scale = 1.0f;
}

// Destructora
MyGLWidget::~MyGLWidget () { 
     if (program != NULL) delete program;
}

// Inicialitzar
void MyGLWidget::initializeGL () {

     initializeOpenGLFunctions();  

     glClearColor(0.5, 0.7, 1.0, 1.0); // Color de fons
     carregaShaders();
     crearHomer();

     FOV = 2*float(M_PI/4.0);
     rav = 1.0;
     rotateP = 0.0;

     projectTransform();
     viewTransform ();

     glEnable (GL_DEPTH_TEST);

}

// Pintar
void MyGLWidget::paintGL () {

     glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Esborrar GLBuffer

     modelTransform ();
     glBindVertexArray (VAO_Homer); // Activar el VAO

     // Pintar
     glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);
     glDrawArrays (GL_TRIANGLES, 0, homer.faces ().size () * 3);

     glBindVertexArray (0);

}

// Calcular la TG
void MyGLWidget::modelTransform () {

     // Matriu de transformació de model
     glm::mat4 TG (1.0f);
     TG = glm::rotate(glm::mat4(1.0f),
                      rotateP,
                      glm::vec3(0.,1.,0.));
     glm::vec3 centreCapsa((capsaMin.x + capsaMax.x)/2,
                           (capsaMin.y + capsaMax.y)/2,
                           (capsaMin.z + capsaMax.z)/2);

     TG = glm::scale(TG, glm::vec3(scale));
     TG = glm::translate(TG, -centreCapsa);

     glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);

}

// Resize del Window sense deformacio
void MyGLWidget::resizeGL (int w, int h) {

     rav = float(w)/float(h);
     if(rav < 1) FOV = 2*atan(tan(float(M_PI/4.0))/rav);

     glViewport(0, 0, w, h);
     projectTransform();

}

// Per quan presionem una tecla
void MyGLWidget::keyPressEvent(QKeyEvent* event) {

     makeCurrent();
     switch (event->key()) {
          case Qt::Key_S: // escalar a més gran
               scale += 0.01;
               break;
          case Qt::Key_D: // escalar a més petit
               scale -= 0.01;
               break;
          case Qt::Key_R:
               rotateP += M_PI/20;
               break;
          default: event->ignore(); break;
     }
     update();

}

// Crea el Objecte Homer
void MyGLWidget::crearHomer () {

	// Carregar el model de Homer
	homer.load("../models/HomerProves.obj");
     CalculaCapsa(homer, capsaMin, capsaMax);
	int cares = homer.faces().size();

	// Creació del Vertex Array Object per pintar
	glGenVertexArrays(1, &VAO_Homer);
	glBindVertexArray(VAO_Homer);

	glGenBuffers(1, &VBO_HomerPos);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_HomerPos);
	
     // Posició
	glBufferData(GL_ARRAY_BUFFER,	sizeof(GLfloat)*cares*3*3, homer.VBO_vertices(), GL_STATIC_DRAW);
	
	// Activem l'atribut vertexLoc
	glVertexAttribPointer(homerLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(homerLoc);

	glGenBuffers(1, &VBO_HomerCol);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_HomerCol);

     // Color
	glBufferData(GL_ARRAY_BUFFER,	sizeof(GLfloat)*cares*3*3, homer.VBO_matdiff(), GL_STATIC_DRAW);
				 
	// Activem l'atribut colorLoc
	glVertexAttribPointer(homerCol, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(homerCol);


	glBindVertexArray (0);
}

// Carregar tots els Shaders
void MyGLWidget::carregaShaders () {

     // Creem els shaders per al fragment shader i el vertex shader
     QOpenGLShader fs (QOpenGLShader::Fragment, this);
     QOpenGLShader vs (QOpenGLShader::Vertex, this);

     // Carreguem el codi dels fitxers i els compilem
     fs.compileSourceFile("shaders/fragshad.frag");
     vs.compileSourceFile("shaders/vertshad.vert");

     // Creem el program
     program = new QOpenGLShaderProgram(this);

     // Li afegim els shaders corresponents
     program->addShader(&fs);
     program->addShader(&vs);

     // Linkem el program
     program->link();

     // Indiquem que aquest és el program que volem usar
     program->bind();

     // Obtenim identificador per a l'atribut “vertex” del vertex shader
     homerLoc = glGetAttribLocation (program->programId(), "vertex");
     // Obtenim identificador per a l'atribut “color” del vertex shader
     homerCol = glGetAttribLocation (program->programId(), "color");
     // Uniform locations
     transLoc = glGetUniformLocation(program->programId(), "TG");
     // Uniform location per la matriu de projeccio
     projLoc = glGetUniformLocation(program->programId(), "proj");
     // Uniform location per al view
     viewLoc = glGetUniformLocation(program->programId(), "view");
}

// Calcular PM
void MyGLWidget::projectTransform () {

	// glm::perspective (FOV en radians, ra window, znear, zfar)
     FOV = 2*atan((capsaMax.y - capsaMin.y)/3);

     float zN = float(1.5+(capsaMax.z-capsaMin.z));
	glm::mat4 Proj = glm::perspective (FOV, rav, 1.5f, zN);
	glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);

}

// Calcular VM
void MyGLWidget::viewTransform () {
     // glm::lookAt (OBS, VRP, UP)
	glm::mat4 View = glm::lookAt (glm::vec3(0.,0.,((capsaMax.z-capsaMin.z)/2+1.5)),
	                              glm::vec3(0.,0.,0.),
							      glm::vec3(0.,1.,0.));
	glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

// Calcular Capsa Mínima Contenidora
void MyGLWidget::CalculaCapsa(const Model& m, glm::vec3& min, glm::vec3& max) {
    min.x = max.x = m.vertices()[0];
    min.y = max.y = m.vertices()[1];
    min.z = max.z = m.vertices()[2];

    for (unsigned int i = 3; i < m.vertices().size(); i+=3) {
        double x = m.vertices()[i];
        double y = m.vertices()[i+1];
        double z = m.vertices()[i+2];

        if (x < min.x) min.x = x;
        else if (x > max.x) max.x = x;
        
        if (y < min.y) min.y = y;
        else if (y > max.y) max.y = y;
        if(z < min.z) min.z = z;
        else if (z > max.z) max.z = z;
    }
}
#include "MyGLWidget.h"

#include <iostream>

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent)
{
  setFocusPolicy(Qt::ClickFocus);  // per rebre events de teclat
  scale = 1.0f;
}

MyGLWidget::~MyGLWidget ()
{
  if (program != NULL)
    delete program;
}

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();  

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
 // createBuffers();
  crearHomer();
  
  projectTransform();
  viewTransform ();
  
  glEnable (GL_DEPTH_TEST);
}

void MyGLWidget::paintGL () 
{
  // Esborrem el frame-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Carreguem la transformació de model
  modelTransform ();

  // Activem el VAO per a pintar la caseta 
 // glBindVertexArray (VAO_Casa);
  glBindVertexArray (VAO_Homer);

  // pintem
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);
  glDrawArrays (GL_TRIANGLES, 0, homer.faces ().size () * 3);

  glBindVertexArray (0);
}

void MyGLWidget::modelTransform () 
{
  // Matriu de transformació de model
  glm::mat4 transform (1.0f);
  transform = glm::scale(transform, glm::vec3(scale));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::resizeGL (int w, int h) 
{
  glViewport(0, 0, w, h);
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) 
{
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_S: { // escalar a més gran
      scale += 0.05;
      break;
    }
    case Qt::Key_D: { // escalar a més petit
      scale -= 0.05;
      break;
    }
    default: event->ignore(); break;
  }
  update();
}

void MyGLWidget::crearHomer ()
{
	// Carregar el homer
	homer.load("/dades/matias.szarfer/IDI/OpenGL/models/HomerProves.obj");
	int cares = homer.faces().size();

	// Creació del Vertex Array Object per pintar
	glGenVertexArrays(1, &VAO_Homer);
	glBindVertexArray(VAO_Homer);

	glGenBuffers(1, &VBO_HomerPos);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_HomerPos);
	
	glBufferData(GL_ARRAY_BUFFER,	// Posició
				 sizeof(GLfloat)*cares*3*3,
			     homer.VBO_vertices(),
			     GL_STATIC_DRAW);
	
	// Activem l'atribut vertexLoc
	glVertexAttribPointer(homerLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(homerLoc);

	glGenBuffers(1, &VBO_HomerCol);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_HomerCol);

	glBufferData(GL_ARRAY_BUFFER,	 // Color
				 sizeof(GLfloat)*cares*3*3,
				 homer.VBO_matdiff(),
				 GL_STATIC_DRAW);
				 
	// Activem l'atribut colorLoc
	glVertexAttribPointer(homerCol, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(homerCol);


	glBindVertexArray (0);
}

void MyGLWidget::createBuffers () 
{
  // Dades de la caseta
  // Dos VBOs, un amb posició i l'altre amb color
  glm::vec3 posicio[5] = {
	glm::vec3(-0.5, -1.0, -0.5),
	glm::vec3( 0.5, -1.0, -0.5),
	glm::vec3(-0.5,  0.0, -0.5),
	glm::vec3( 0.5,  0.0, -0.5),
	glm::vec3( 0.0,  0.6, -0.5)
  }; 
  glm::vec3 color[5] = {
	glm::vec3(1,0,0),
	glm::vec3(0,1,0),
	glm::vec3(0,0,1),
	glm::vec3(1,0,0),
	glm::vec3(0,1,0)
  };
  
  // Creació del Vertex Array Object per pintar
  glGenVertexArrays(1, &VAO_Casa);
  glBindVertexArray(VAO_Casa);

  glGenBuffers(1, &VBO_CasaPos);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_CasaPos); //VBO_HomerPos
  glBufferData(GL_ARRAY_BUFFER, sizeof(posicio), posicio, GL_STATIC_DRAW);
  
  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  glGenBuffers(1, &VBO_CasaCol);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_CasaCol);
  glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
  
  // Activem l'atribut colorLoc
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

  glBindVertexArray (0);
}

void MyGLWidget::carregaShaders ()
{
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
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");
  homerLoc = glGetAttribLocation (program->programId(), "vertex");
  // Obtenim identificador per a l'atribut “color” del vertex shader
  colorLoc = glGetAttribLocation (program->programId(), "color");
  homerCol = glGetAttribLocation (program->programId(), "color");
  // Uniform locations
  transLoc = glGetUniformLocation(program->programId(), "TG");
  // Uniform location per la matriu de projeccio
  projLoc = glGetUniformLocation(program->programId(), "proj");
  // Uniform location per al view
  viewLoc = glGetUniformLocation(program->programId(), "view");
}

// Metode per calcular la transformacio de la projeccio i
// envia el uniform amb la matriu al vertshad.
void MyGLWidget::projectTransform ()
{
	              // glm::perspective (FOV en radians, ra window, znear, zfar)
	glm::mat4 Proj = glm::perspective ((float)M_PI/1.5f, 1.0f, 0.4f, 3.0f);
	glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

// Mètode per calcular la transformació del punt de vista,
// view i envia al vertshad.
void MyGLWidget::viewTransform ()
{
				  // glm::lookAt (OBS, VRP, UP)
	glm::mat4 View = glm::lookAt (glm::vec3(0,0,1),
	                              glm::vec3(0,0,0),
								  glm::vec3(0,1,0));
	glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

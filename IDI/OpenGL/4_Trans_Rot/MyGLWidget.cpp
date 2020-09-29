#include "MyGLWidget.h"

#include <iostream>

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent) {

  setFocusPolicy(Qt::ClickFocus);  // per rebre events de teclat

}

MyGLWidget::~MyGLWidget () {

  if (program != NULL)
    delete program;

}

void MyGLWidget::initializeGL () {

  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();
  
  glClearColor (0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  createBuffers();

  //  Donar valor al uniform (cal fer-ho cada cop que es vulgui canviar el valor del paràmetre scl)
  scl = 0.5;
  glUniform1f (varLoc, scl); // scl variable que conté el valor que es vol per “val”

}

void MyGLWidget::paintGL () {

  glClear (GL_COLOR_BUFFER_BIT);  // Esborrem el frame-buffer

  // Activem l'Array a pintar 
  glBindVertexArray(VAO);
  modelTransform(); // EX 1. Translation
  modelGir(); // EX 2. Rotation

  // Pintem l'escena
  glDrawArrays(GL_TRIANGLES, 0, 3);

  // Desactivem el VAO
  glBindVertexArray(0);

}

void MyGLWidget::resizeGL (int w, int h) {

  glViewport (0, 0, w, h);

}

void MyGLWidget::createBuffers () {

  glm::vec3 Vertices[3];  // Tres vèrtexs amb X, Y i Z
  Vertices[0] = glm::vec3(-1.0, -1.0, 0.0);
  Vertices[1] = glm::vec3(1.0, -1.0, 0.0);
  Vertices[2] = glm::vec3(0.0, 1.0, 0.0);
  
  // Creació del Vertex Array Object (VAO) que usarem per pintar
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // Creació del buffer amb les dades dels vèrtexs
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  // Activem l'atribut que farem servir per vèrtex	// Tres vèrtexs amb X, Y i Z
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);
  
  // Per el color: Hemos de declarar otro VBO con la informacion de cada color 
  //			   para cada vértice.
  glm::vec3 Color[3]; 
  Color[0] = glm::vec3(1.0, 0.0, 0.0);
  Color[1] = glm::vec3(0.0, 1.0, 0.0);
  Color[2] = glm::vec3(0.0, 0.0, 1.0);
  
  glGenBuffers(1, &VBO_Color);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Color);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Color), Color, GL_STATIC_DRAW);
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

  // Desactivem el VAO
  glBindVertexArray(0);

}

void MyGLWidget::carregaShaders() {

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
  // Obtener identificador para el "color"
  colorLoc = glGetAttribLocation (program->programId(), "color");

  //  Associar identificador al shader (només cal fer-ho un cop)
  varLoc = glGetUniformLocation (program->programId (), "val"); //Canal
  transLoc = glGetUniformLocation (program->programId(), "TG"); // EX 1. Translation

  transRot = glGetUniformLocation (program->programId(), "TG"); // EX 2. Rotation
}

// Funcio de keyPressEvent
void MyGLWidget::keyPressEvent (QKeyEvent *e) {
    makeCurrent ();
    switch ( e->key() ) {
        case Qt::Key_S :
            scl += 0.05;
            glUniform1f (varLoc, scl); // Passar scl a traves de varLoc (que te el canal) cap al Shader
            break;
        case Qt::Key_D :
            scl -= 0.05;
            glUniform1f (varLoc, scl);
            break;

        // EX 1. Translation
        case Qt::Key_Up:
            ty += 0.05;
            break;
        case Qt::Key_Down:
            ty -= 0.05;
            break;
        case Qt::Key_Left:
            tx -= 0.05;
            break;
        case Qt::Key_Right:
            tx += 0.05;
            break;
        default: e->ignore (); // propagar al pare
    }
    update ();
}

// EX 1. Translation
void MyGLWidget::modelTransform () {
    glm::mat4 TG (1.0); // Matriu de transformació, inicialment identitat
    TG = glm::translate (TG, glm::vec3 (tx, ty, 0.0));
    glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

// EX 2. Rotation
void MyGLWidget::modelGir () {
    glm::mat4 TG (1.0); // Matriu de transformació, inicialment identitat
    TG = glm::rotate(TG, 0.5f, glm::vec3 (0.f, 0.f, 0.f));
    glUniformMatrix4fv (transRot, 1, GL_FALSE, &TG[0][0]);
}

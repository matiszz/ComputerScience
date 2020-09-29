#include "MyGLWidget.h"
#include <iostream>
#include <cmath>

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
    glEnable (GL_DEPTH_TEST);

    patricio.load("../models/Patricio.obj");
    CalculaCapsa(patricio, capsaMin, capsaMax);
    capsaEscena(escenaMin, escenaMax);

    FOV = 2*atan((capsaMax.y - capsaMin.y)/3);
    rav = 1.0;
    rotateP = 0.0;
    scale = 1.0f;
    sx = sy = 0.0f;
    zoom = 0;

    glClearColor(0.5, 0.7, 1.0, 1.0); // Color de fons
    carregaShaders();
    crearBuffers();
    modelTransformPat();
    modelTransformTerra();
    projectTransform();
    viewTransform();
    setMouseTracking(true);
}

// Pinta el Patricio només (com si fos dins de PaintGL)
void MyGLWidget::pintaPatricio() {
    
    modelTransformPat();
    glBindVertexArray(VAO_Pat);
    glDrawArrays (GL_TRIANGLES, 0, patricio.faces().size() * 3);
    
    // modelTransformPat();
    // glBindVertexArray(VAO_Pat);
    // glDrawArrays (GL_TRIANGLES, 0, patricio.faces().size() * 3);

}

// Pinta el Terra només (com si fos dins de PaintGL)
void MyGLWidget::pintaTerra() {

    modelTransformTerra();
    glBindVertexArray(VAO_Terra);
    glDrawArrays (GL_TRIANGLE_STRIP, 0, 4);
}

// Pintar
void MyGLWidget::paintGL () {

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Esborrar GLBuffer
    pintaPatricio();
    pintaTerra(); 
    glBindVertexArray (0);

}

// Calcular la TG
void MyGLWidget::modelTransformPat () {

    // Matriu de transformació de model
    glm::vec3 CBP ((capsaMin.x+capsaMax.x)/2, capsaMin.y, (capsaMin.z+capsaMax.z)/2);
    glm::mat4 TGpat (1.0f);
    TGpat = glm::translate(TGpat, glm::vec3(0.f, 0.f, 0.f));
    TGpat = glm::scale(TGpat, glm::vec3(0.5, 0.5, 0.5));
    // TGpat = glm::rotate(TGpat, rot, glm::vec3 (0.f, 1.f, 0.f));
    TGpat = glm::translate(TGpat, -CBP);
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TGpat[0][0]);

}

// Calcular la TG
void MyGLWidget::modelTransformTerra () {

    // Matriu de transformació de model
    glm::vec3 CBP ((capsaMin.x+capsaMax.x)/2, capsaMin.y, (capsaMin.z+capsaMax.z)/2);
    glm::mat4 TGterra (1.0f);
    TGterra = glm::translate(TGterra, glm::vec3(-10.f, 3.f, 0.f));
    // TGterra = glm::rotate(TGterra, rot, glm::vec3 (0.f, 1.f, 0.f));
    TGterra = glm::translate(TGterra, -CBP);
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TGterra[0][0]);

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
        case Qt::Key_R: // rotar
            rotateP += M_PI/20;
            break;
        case Qt::Key_Z: // zoom in
            FOV -= 0.05;
            viewTransform();
            projectTransform();
            break;
        case Qt::Key_X: // zoom out
            FOV += 0.05;
            viewTransform();
            projectTransform();
            break;
        default: event->ignore(); break;
    }
    update();

}

// Per quan movem el mouse
void MyGLWidget::mouseMoveEvent(QMouseEvent *e) {

    makeCurrent();

    int xnew = e->x();
    int ynew = e->y();

         if (rx < xnew) sx += 0.025;
    else if (rx > xnew) sx -= 0.025;
         if (ry < ynew) sy += 0.025;
    else if (ry > ynew) sy -= 0.025;

    viewTransform();
    update();

    rx = xnew;
    ry = ynew;
}

// Crea tots els buffers necessaris
void MyGLWidget::crearBuffers () {
    
    // ############### Patricio 1 ######################
    int cares = patricio.faces().size();

    // Creació del Vertex Array Object per pintar
    glGenVertexArrays(1, &VAO_Pat);
    glBindVertexArray(VAO_Pat);

    glGenBuffers(1, &VBO_PatPos);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_PatPos);                                              // Posició
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*cares*3*3, patricio.VBO_vertices(), GL_STATIC_DRAW);

    // Activem l'atribut vertexLoc
    glVertexAttribPointer(patLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(patLoc);

    glGenBuffers(1, &VBO_PatCol);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_PatCol);                                               // Color
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*cares*3*3, patricio.VBO_matdiff(), GL_STATIC_DRAW);
                
    // Activem l'atribut colorLoc
    glVertexAttribPointer(patCol, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(patCol);

    // ############### Terra ######################

    glm::vec3 Terra[4];
    Terra[0] = glm::vec3(2.0, 0.0, 2.0);
    Terra[1] = glm::vec3(2.0, 0.0, -2.0);
    Terra[2] = glm::vec3(-2.0, 0.0, 2.0);
    Terra[3] = glm::vec3(-2.0, 0.0, -2.0);
    // Creació del Vertex Array Object per pintar
    glGenVertexArrays(1, &VAO_Terra);
    glBindVertexArray(VAO_Terra);

    glGenBuffers(1, &VBO_TerraPos);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_TerraPos);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Terra), Terra, GL_STATIC_DRAW); // Posició

    // Activem l'atribut vertexLoc
    glVertexAttribPointer(terraLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(terraLoc);

    Color[0] = glm::vec3(0.0, 0.0, 0.0);
    Color[1] = glm::vec3(0.0, 0.5, 0.5);
    Color[2] = glm::vec3(0.7, 0.0, 0.0);
    Color[3] = glm::vec3(0.0, 0.0, 0.0);

    glGenBuffers(1, &VBO_TerraCol);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_TerraCol);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Color), Color, GL_STATIC_DRAW); // Color
                
    // Activem l'atribut colorLoc
    glVertexAttribPointer(terraCol, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(terraCol);

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
    patLoc = glGetAttribLocation (program->programId(), "vertex");
    // Obtenim identificador per a l'atribut “color” del vertex shader
    patCol = glGetAttribLocation (program->programId(), "color");
    // Obtenim identificador per a l'atribut “vertex” del vertex shader
    terraLoc = glGetAttribLocation (program->programId(), "vertex");
    // Obtenim identificador per a l'atribut “color” del vertex shader
    terraCol = glGetAttribLocation (program->programId(), "color");

    // Uniform locations
    transLoc = glGetUniformLocation(program->programId(), "TG");
    // Uniform location per la matriu de projeccio
    projLoc = glGetUniformLocation(program->programId(), "proj");
    // Uniform location per al view
    viewLoc = glGetUniformLocation(program->programId(), "view");
}

// Calcular PM
void MyGLWidget::projectTransform () {

    glm::vec3 CBPescena ((escenaMin.x+escenaMax.x)/2, (escenaMin.y+escenaMax.y)/2, (escenaMin.z+escenaMax.z)/2);
    // Ha de ser la caixa de l'escena, no dels models!! 

    float x = escenaMax.x - CBPescena.x;
    float y = escenaMax.y - CBPescena.y;
    float z = escenaMax.z - CBPescena.z;
    float Radi = sqrt(x*x+y*y+z*z);

    glm::mat4 Proj = glm::perspective(FOV, rav, Radi, Radi*3); // Radi es zFar
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &Proj[0][0]);

}

// Calcular VM
void MyGLWidget::viewTransform () {

    glm::vec3 CBPescena ((escenaMin.x+escenaMax.x)/2, (escenaMin.y+escenaMax.y)/2, (escenaMin.z+escenaMax.z)/2);
    // Ha de ser la caixa de l'escena, no dels models!! 

    float x = escenaMax.x - CBPescena.x;
    float y = escenaMax.y - CBPescena.y;
    float z = escenaMax.z - CBPescena.z;
    float Radi = sqrt(x*x+y*y+z*z);
    Radi = -Radi*2;

    glm::mat4 View(1.0f); 
    View = glm::translate(View, glm::vec3(0.,0.,Radi));
    View = glm::rotate(View, sy, glm::vec3(1,0,0));
    View = glm::rotate(View, -sx, glm::vec3(0,1,0));
    View = glm::translate(View, -CBPescena);

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &View[0][0]);
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

// Calcular Capsa que conté l'escena. Ara mateix es manual
void MyGLWidget::capsaEscena(glm::vec3& min, glm::vec3& max) {
    min.x = -2.0;
    min.y = 0.0;
    min.z = -2.0;

    max.x = 2.0;
    max.y = 1.0;
    max.z = 2.0;
}

void MyGLWidget::canviaColor() {
    makeCurrent();
    FOV -= 0.05;
    viewTransform();
    projectTransform();
}
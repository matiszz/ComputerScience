#define GLM_FORCE_RADIANS
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include "model.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core 
{
  Q_OBJECT

  public:
    MyGLWidget (QWidget *parent=0);
    ~MyGLWidget ();

  protected:
    virtual void initializeGL ( );
    virtual void paintGL ( );
    virtual void resizeGL (int width, int height);
    virtual void keyPressEvent (QKeyEvent *event);

  private:
    void createBuffers ();
    void carregaShaders ();
    void modelTransform ();
    void projectTransform ();
    void viewTransform ();
    void crearHomer ();
    void CalculaCapsa(const Model& m, glm::vec3& min, glm::vec3& max);

    // Attribute Locations
    GLuint vertexLoc, colorLoc;

    // Uniform Locations
    GLuint transLoc, projLoc, viewLoc;

    // VAO i VBO
    GLuint VAO_Casa, VBO_CasaPos, VBO_CasaCol;

    // Program
    QOpenGLShaderProgram *program;

    // Variables internes
    float scale, FOV, rav, rotateP;
    glm::vec3 pos, capsaMin, capsaMax;
    
    // Per al Homer
    Model homer;
    GLuint VAO_Homer, VBO_HomerPos, VBO_HomerCol;
    GLuint homerLoc, homerCol;

};


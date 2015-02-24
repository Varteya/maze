#include <QtOpenGL>

#include <fstream>
#include "glwidget.h"

GLWidget::GLWidget(Field field, Player player, QWidget *parent) :
        QGLWidget(parent),
        timer(this),
        mapField(field),
        p(player) {
    timer.setSingleShot(false);
}

QSize GLWidget::minimumSizeHint() const {
    return QSize(500, 500);
}

QSize GLWidget::sizeHint() const {
    return QSize(700, 700);
}

void GLWidget::initializeGL() {
    initializeGLFunctions();
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    initTextures();

    projection.perspective(60.0f, 1.0f, 0.1f, 100.0f);
    view.lookAt(QVector3D(mapField.size/2, mapField.size/2, 15.0f), QVector3D(mapField.size/2, mapField.size/2, 0), QVector3D(0, 1, 0));

    currentShader = new QGLShaderProgram();
    initShaders();
}

void GLWidget::initShaders() {
    // Overriding system locale until shaders are compiled
    setlocale(LC_NUMERIC, "C");

    // Compiling vertex shader
    if (!currentShader->addShaderFromSourceFile(QGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compiling fragment shader
    if (!currentShader->addShaderFromSourceFile(QGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Linking shader pipeline
    if (!currentShader->link())
        close();

    // Binding shader pipeline for use
    if (!currentShader->bind())
        close();

    // Restore system locale
    setlocale(LC_ALL, "");
}

void GLWidget::initTextures() {
    glGenTextures(2, texture);
    texture[0] = bindTexture(QImage(":/brickwork-texture.jpg"));
    texture[1] = bindTexture(QImage(":/12.png"));

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void GLWidget::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Up) {
        p.move(Player::UP);
    } else if (event->key() == Qt::Key_Down) {
        p.move(Player::DOWN);
    } else if (event->key() == Qt::Key_Left) {
        p.move(Player::LEFT);
    } else if (event->key() == Qt::Key_Right) {
        p.move(Player::RIGHT);
    }
    if (p.isEscaped()){
        QMessageBox msgBox;
        msgBox.setText("Congratulations! You won! Application will be closed.");
        msgBox.exec();
        exit(0);
    } else {
        updateGL();
    }
}

void GLWidget::paintGL() {
    glClearColor(0, 0, 0, 1.0f);
    glClearDepth(1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    currentShader->setUniformValue("mvp", projection * view * model);
    currentShader->setUniformValue("number_of_squares", mapField.size);

    currentShader->setUniformValue("texture", 0);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    paintMap();
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    paintPlayer();
}

void GLWidget::paintPlayer() {
    currentShader->setUniformValue("is_player", true);
    GLuint buffer;
    glGenBuffers(1, &buffer);
    VertexData vertices[6];
    int x = p.getXCoord();
    int y = p.getYCoord();
    vertices[0] = {QVector2D(x, y), QVector2D(0, 0)};
    vertices[1] = {QVector2D(x + 1, y), QVector2D(1, 0)};
    vertices[2] = {QVector2D(x, y + 1), QVector2D(0, 1)};
    vertices[3] = {QVector2D(x + 1, y), QVector2D(1, 0)};
    vertices[4] = {QVector2D(x + 1, y + 1), QVector2D(1, 1)};
    vertices[5] = {QVector2D(x, y + 1), QVector2D(0, 1)};

    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(VertexData), vertices, GL_STATIC_DRAW);

    int vertexLocation = currentShader->attributeLocation("vertex");
    currentShader->enableAttributeArray(vertexLocation);
    glVertexAttribPointer(vertexLocation, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void *) 0);

    int textcoordLocation = currentShader->attributeLocation("a_texcoord");
    currentShader->enableAttributeArray(textcoordLocation);
    glVertexAttribPointer(textcoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void *) sizeof(QVector2D));

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    currentShader->disableAttributeArray("vertex");
}

void GLWidget::paintMap() {
    currentShader->setUniformValue("is_player", false);
    QGLBuffer buffer(QGLBuffer::VertexBuffer);
    std::vector<float> vertices(8 * mapField.numberOfWalls);
    int wallsDone = 0;
    for (int i = 0; i < mapField.size; ++i) {
        for (int j = 0; j < mapField.size; ++j) {
            if (mapField.readValue(i, j) == Field::typeOfPlace::WALL) {
                vertices[wallsDone] = i;
                wallsDone++;
                vertices[wallsDone] = j;
                wallsDone++;
                vertices[wallsDone] = i + 1;
                wallsDone++;
                vertices[wallsDone] = j;
                wallsDone++;
                vertices[wallsDone] = i + 1;
                wallsDone++;
                vertices[wallsDone] = j + 1;
                wallsDone++;
                vertices[wallsDone] = i;
                wallsDone++;
                vertices[wallsDone] = j + 1;
                wallsDone++;
            }
        }
    }

    buffer.create();
    buffer.setUsagePattern(QGLBuffer::StaticDraw);
    buffer.bind();
    buffer.allocate(vertices.data(), vertices.size() * sizeof(float));

    currentShader->setAttributeBuffer("vertex", GL_FLOAT, 0, 2);
    currentShader->enableAttributeArray("vertex");
    glDrawArrays(GL_QUADS, 0, 8 * mapField.numberOfWalls);
    buffer.release();
    currentShader->disableAttributeArray("vertex");
}


void GLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

#include "cubewidget.h"
#include "material.h"

#include <QMouseEvent>
#include <QColor>

#include <QtMath>
#include <cmath>

void CubeWidget::directLightToggle(int state)
{
    bool bstate = state > 0 ? true : false;
    directLight.switchState(bstate);
}

void CubeWidget::directLightChangeX(float newX)
{
    auto currDir = directLight.getDirection();
    directLight.setDirection(QVector3D(newX, currDir.y(), currDir.z()));
}

void CubeWidget::directLightChangeY(float newY)
{
    auto currDir = directLight.getDirection();
    directLight.setDirection(QVector3D(currDir.x(), newY, currDir.z()));
}

void CubeWidget::directLightChangeZ(float newZ)
{
    auto currDir = directLight.getDirection();
    directLight.setDirection(QVector3D(currDir.x(), currDir.y(), newZ));
}

void CubeWidget::directLightIntensityChange(float intensity)
{
    directLight.setIntensity(intensity);
}

void CubeWidget::directLightColorChange(QColor color)
{
    directLight.setColor(QVector3D(color.redF(), color.greenF(), color.blueF()));
}


void CubeWidget::pointLightToggle(int state)
{
    bool bstate = state > 0 ? true : false;
    pointLight.switchState(bstate);
}

void CubeWidget::pointLightChangeX(float newX)
{
    auto currPos = pointLight.getPosition();
    pointLight.setPosition(QVector3D(newX, currPos.y(), currPos.z()));
}

void CubeWidget::pointLightChangeY(float newY)
{
    auto currPos = pointLight.getPosition();
    pointLight.setPosition(QVector3D(currPos.x(), newY, currPos.z()));
}

void CubeWidget::pointLightChangeZ(float newZ)
{
    auto currPos = pointLight.getPosition();
    pointLight.setPosition(QVector3D(currPos.x(), currPos.y(), newZ));
}

void CubeWidget::pointLightIntensityChange(float intensity)
{
    pointLight.setIntensity(intensity);
}

void CubeWidget::pointLightColorChange(QColor color)
{
    pointLight.setColor(QVector3D(color.redF(), color.greenF(), color.blueF()));
}


void CubeWidget::projectorLightToggle(int state)
{
    bool bstate = state > 0 ? true : false;
    projectorLight.switchState(bstate);
}

void CubeWidget::projectorLightCutOffChange(float angle)
{
    projectorLight.setCutOff(angle);
}

void CubeWidget::projectorLightOuterCutOffChange(float angle)
{
    projectorLight.setOuterCutOff(angle);
}

void CubeWidget::projectorLightIntensityChange(float intensity)
{
    projectorLight.setIntensity(intensity);
}

void CubeWidget::projectorLightColorChange(QColor color)
{
    projectorLight.setColor(QVector3D(color.redF(), color.greenF(), color.blueF()));
}

void CubeWidget::sceneNumObjChange(int newNum)
{
    scene->setNumCubes(newNum);
}

void CubeWidget::sceneMaterialChange(QString newMat)
{
    auto currMat = scene->getCube()->getMaterial();

    if(newMat == "White")
        currMat = MaterialFactory::createWhite();
    if(newMat == "Red Rubber")
        currMat = MaterialFactory::createRedRubber();
    if(newMat == "Jade")
        currMat = MaterialFactory::createJade();

    scene->getCube()->setMaterial(currMat);
}

void CubeWidget::showPath(bool state)
{
    //build path before showing
    if(state)
    {
        double fractPart, intPart;
        QVector3D pos = godModeFlag ? historyCameraPos : camera.getCameraPos();

        fractPart = modf(pos.x()/scene->getCube()->getFacetSideLength(), &intPart);
        int row = fractPart < 0.5 ? int(intPart) : int(intPart) + 1;
        fractPart = modf(-pos.z()/scene->getCube()->getFacetSideLength(), &intPart);
        int col = fractPart < 0.5 ? int(intPart) : int(intPart) + 1;

        int row_to = scene->getFinish().row;
        int col_to = scene->getFinish().col;


        scene->setPath(PathFinder::findPath(scene->getData(), row, col, row_to, col_to));
    }

    scene->setShowPathFlag(state);

}

void CubeWidget::godMode(bool state)
{
    godModeFlag = state;

    if (godModeFlag)
    {
        historyCameraPos = camera.getCameraPos();
        historyCameraFront = camera.getCameraFront();
        historyCameraUp = camera.getCameraUp();
        historyYaw = camera.getYaw();
        historyPitch = camera.getPitch();
    } else
    {
        camera.setCameraPos(historyCameraPos);
        camera.setCameraFront(historyCameraFront);
        camera.setCameraUp(historyCameraUp);
        camera.setYaw(historyYaw);
        camera.setPitch(historyPitch);
    }
}

void CubeWidget::restartScene()
{
    scene->reload();
    scene->setShowPathFlag(false);
    godModeFlag = false;

    emit setShowPathFlag(false);
    emit setGodModeFlag(false);

    camera.setCameraPos(QVector3D(scene->getCube()->getFacetSideLength(), 0, -scene->getCube()->getFacetSideLength()));
    camera.setCameraFront({0.f, 0.f, -1.f});
    camera.setCameraUp({0.f, 1.f, 0.f});
    camera.setYaw(- M_PI / 2);
    camera.setPitch(0.f);
    historyCameraPos = camera.getCameraPos();
    historyCameraFront = camera.getCameraFront();
    historyCameraUp = camera.getCameraUp();
    historyYaw = camera.getYaw();
    historyPitch = camera.getPitch();
}

void CubeWidget::resizeScene(int newSize)
{
    scene->init(newSize);
    restartScene();
}

void CubeWidget::collisionDetection(int currRow, int currCol)
{
    auto maze = scene->getData();
    float side = scene->getCube()->getFacetSideLength();
    float walkingZone = side * 0.4;

    auto currPos = camera.getCameraPos();

    if(maze[currRow+1][currCol].cellType == WALL && currPos.x() > side * currRow + walkingZone)
        camera.setCameraPos(QVector3D(side * currRow + walkingZone, currPos.y(), currPos.z()));

    if(maze[currRow-1][currCol].cellType == WALL && currPos.x() < side * currRow - walkingZone)
        camera.setCameraPos(QVector3D(side * currRow - walkingZone, currPos.y(), currPos.z()));

    currPos = camera.getCameraPos();
    if(maze[currRow][currCol+1].cellType == WALL && currPos.z() < -side * currCol - walkingZone)
        camera.setCameraPos(QVector3D(currPos.x(), currPos.y(), -side * currCol - walkingZone));

    if(maze[currRow][currCol-1].cellType == WALL && currPos.z() > -side * currCol + walkingZone)
        camera.setCameraPos(QVector3D(currPos.x(), currPos.y(), -side * currCol + walkingZone));

}


void CubeWidget::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());

    if (e->buttons() & Qt::RightButton)
    {
        mouseLastPosition = QVector2D(e->pos());
    }
}

void CubeWidget::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}

void CubeWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::RightButton)
    {
        QVector2D diff = QVector2D(e->pos()) - mouseLastPosition;
        diff *= 0.001f;
        camera.rotate(diff.x(), diff.y());
    }
    mouseLastPosition = QVector2D(e->pos());
}

void CubeWidget::timerEvent(QTimerEvent *)
{
    doMovement();
    update();

    auto secElapsed = static_cast<int>(timeRecord.elapsed() / 1000);
    emit secsElapsed(secElapsed % 60);
    emit minsElapsed(secElapsed / 60);
}

void CubeWidget::keyPressEvent(QKeyEvent *e)
{
    if(e->key() < 1024)
        keys[e->key()] = true;
}

void CubeWidget::keyReleaseEvent(QKeyEvent *e)
{
    if(e->key() < 1024)
        keys[e->key()] = false;
}

void CubeWidget::wheelEvent(QWheelEvent *e)
{
    fov += e->angleDelta().y() / 45.f;
}

void CubeWidget::doMovement()
{
    float length = cameraSpeed * deltaTimeMsec / 1000.f;

    if (keys[Qt::Key_W])
        camera.move(Camera::directions::FORWARD, length);
    if (keys[Qt::Key_S])
        camera.move(Camera::directions::BACKWARD, length);
    if (keys[Qt::Key_D])
        camera.move(Camera::directions::RIGHT, length);
    if (keys[Qt::Key_A])
        camera.move(Camera::directions::LEFT, length);
    if (keys[Qt::Key_Space])
        camera.move(Camera::directions::UP, length);
    if (keys[Qt::Key_Z])
        camera.move(Camera::directions::DOWN, length);

    double fractPart, intPart;
    fractPart = modf(camera.getCameraPos().x()/scene->getCube()->getFacetSideLength(), &intPart);
    int row = fractPart < 0.5 ? int(intPart) : int(intPart) + 1;

    fractPart = modf(-camera.getCameraPos().z()/scene->getCube()->getFacetSideLength(), &intPart);
    int col = fractPart < 0.5 ? int(intPart) : int(intPart) + 1;

    if(!godModeFlag)
    {
        camera.setCameraPos(QVector3D{camera.getCameraPos().x(), 0, camera.getCameraPos().z()});
        collisionDetection(row, col);
        scene->update(row, col);
    }

}


void CubeWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.f, 0.f, 0.f, 1.f);

    initShaders();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);
    pointLightCube = std::make_shared<Cube>();
    scene = std::make_shared<Scene>();
    scene->init();

    arrow = std::make_shared<Arrow>();
    arrowTex = Texture::loadTexture(R"(D:\NSU\6 semester\Graphics\amazing_maze\arrow.jpg)");

    camera.setZNear(zNear);
    camera.setZFar(zFar);
    camera.setCameraPos(QVector3D(scene->getCube()->getFacetSideLength(), 0, -scene->getCube()->getFacetSideLength()));

    directLight = DirectLightSource();
    pointLight = PointLightSource();
    projectorLight = ProjectorLightSource(camera.getCameraPos(), camera.getCameraFront());

    glActiveTexture(GL_TEXTURE0);

    n = 0;
    // Use QBasicTimer because its faster than QTimer
    timer.start(deltaTimeMsec, this);
    timeRecord.start();
}

//! [3]
void CubeWidget::initShaders()
{
    // Compile vertex shader for objects
    if (!objectShader.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader for objects
    if (!objectShader.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!objectShader.link())
        close();

    // Compile vertex shader for objects
    if (!lightShader.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader_light.glsl"))
        close();

    // Compile fragment shader for objects
    if (!lightShader.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!lightShader.link())
        close();

    // Bind shader pipeline for use
    if (!objectShader.bind())
        close();
}


void CubeWidget::resizeGL(int w, int h)
{
    camera.setAspectRatio(float(w) / float(h ? h : 1));
}


void CubeWidget::paintGL()
{
    auto start = stopwatch.currentTime();

    // Clear color and depth buffer
    if(directLight.getState()) {
        auto backgroundColor = directLight.getColor();
        auto backgroundIntensity = directLight.getIntensity();
        glClearColor(backgroundIntensity * backgroundColor.x(),
                     backgroundIntensity * backgroundColor.y(),
                     backgroundIntensity * backgroundColor.z(),
                     1.f);
    } else {
        glClearColor(0.0f, 0.0f, 0.0f, 1.f);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    objectShader.bind();

    if(godModeFlag)
    {
        QMatrix4x4 mat;
        mat.translate(historyCameraPos);

        auto a = QVector3D{0.f, 0.f, -1.f};
        a.normalize();
        auto b = QVector3D{historyCameraFront.x(), 0.f, historyCameraFront.z()};
        b.normalize();

        auto angle = qRadiansToDegrees(qAcos(QVector3D::dotProduct(a, b)));
        mat.rotate(-angle, QVector3D{0.f, 1.f, 0.f});

        objectShader.setUniformValue(0, mat);
        arrowTex->bind();
        arrow->render(&objectShader);
    }

    camera.setFOV(fov);

    projectorLight.setPosition(camera.getCameraPos());
    projectorLight.setDirection(camera.getCameraFront());

    objectShader.bind();
    objectShader.setUniformValue(1, camera.getViewMatrix());
    objectShader.setUniformValue(2, camera.getProjectionMatrix());
    objectShader.setUniformValue(3, camera.getCameraPos());

    glActiveTexture(GL_TEXTURE0);

    scene->getCube()->getMaterial()->uploadToShader(&objectShader);
    directLight.uploadToShader(&objectShader);
    pointLight.uploadToShader(&objectShader);
    projectorLight.uploadToShader(&objectShader);

    // Draw cube geometry
    scene->drawScene(&objectShader);

    if(pointLight.getState()) {
        QMatrix4x4 modelMatLight;
        modelMatLight.translate(pointLight.getPosition());

        lightShader.bind();
        lightShader.setUniformValue(0, modelMatLight);
        lightShader.setUniformValue(1, camera.getViewMatrix());
        lightShader.setUniformValue(2, camera.getProjectionMatrix());
        lightShader.setUniformValue("lightColor", pointLight.getIntensity() * pointLight.getColor());

        pointLightCube->render(&lightShader);
    }

    auto stop = stopwatch.currentTime();

    fps += 1.f / (start.msecsTo(stop));
    ++n;
    if (n >= 100) {
        n = 0;
        emit fpsChanged(static_cast<double>(1000 * fps / 100));
        fps = 0;
    }
}

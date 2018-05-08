#include "glwidget.h"

#include <QDebug> 
#include <QOpenGLShaderProgram>
#include <QMouseEvent> 

#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1
 
GLWidget::GLWidget(QWidget* parent /* = Q_NULLPTR */)
	: program(Q_NULLPTR),
	QOpenGLWidget(parent),
	clearColor(Qt::black) {
		 
}


GLWidget::~GLWidget() {
	makeCurrent();
	vbo.destroy(); 
	if (program != nullptr) {
		delete program;
	}
	doneCurrent();
}

void GLWidget::setClearColor(const QColor &color) {
	clearColor = color;
	update();
}

void GLWidget::initializeGL() {
	initializeOpenGLFunctions();
	makeObject(); 

	QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
	const char *vsrc =
		"attribute highp vec4 vertex;\n"
		"attribute mediump vec4 texCoord;\n"
		"varying mediump vec4 texc;\n"
		"uniform mediump mat4 view;\n"
		"void main(void)\n"
		"{\n"
		"    gl_Position = view * vertex;\n"
		"    texc = texCoord;\n"
		"}\n";
	vshader->compileSourceCode(vsrc);

	QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
	const char *fsrc =
		"uniform sampler2D texture;\n"
		"varying mediump vec4 texc;\n"
		"void main(void)\n"
		"{\n"
		"    gl_FragColor = texture2D(texture, texc.st);\n"
		"}\n";
	fshader->compileSourceCode(fsrc);

	program = new QOpenGLShaderProgram;
	program->addShader(vshader);
	program->addShader(fshader);
	program->bindAttributeLocation("vertex", PROGRAM_VERTEX_ATTRIBUTE);
	program->bindAttributeLocation("texCoord", PROGRAM_TEXCOORD_ATTRIBUTE);
	program->link();

	program->bind();
	program->setUniformValue("texture", 0);
	program->setUniformValue("view", mModelView);
}

void GLWidget::paintGL() {
	glClearColor(clearColor.redF(), clearColor.greenF(), clearColor.blueF(), clearColor.alphaF());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
	program->enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
	program->enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
	program->setAttributeBuffer(PROGRAM_VERTEX_ATTRIBUTE, GL_FLOAT, 0, 3, 5 * sizeof(GLfloat));
	program->setAttributeBuffer(PROGRAM_TEXCOORD_ATTRIBUTE, GL_FLOAT, 3 * sizeof(GLfloat), 2, 5 * sizeof(GLfloat));

	texture->bind(); 
	program->setUniformValue("view", mModelView);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); 
}

void GLWidget::resizeGL(int width, int height) { 
	GLfloat aspectRatio = (GLfloat)width / (GLfloat)height;
	glViewport(0, 0, width, height);
	mModelView.setToIdentity();
	if (width >= height) {
		mModelView.ortho(-1.0f, 1.0f, -1.0f*aspectRatio, 1.0f*aspectRatio, 0.0f, 100.0f);
	}
	else {
		mModelView.ortho(-1.0f*height / width, 1.0f*height / width, -1.0f, 1.0f, 0.0f, 100.0f);
	}  
}

void GLWidget::createTexture(int width, int height) {
	texture = new QOpenGLTexture(QOpenGLTexture::Target2D);
	texture->create();
	texture->setSize(width, height);
	texture->setFormat(QOpenGLTexture::TextureFormat::RGB8_UNorm);
	texture->setWrapMode(QOpenGLTexture::ClampToEdge);
	texture->setMipLevels(texture->maximumMipLevels());
	texture->setAutoMipMapGenerationEnabled(true);
	texture->setMagnificationFilter(QOpenGLTexture::Linear);
	texture->setMinificationFilter(QOpenGLTexture::Linear);
	texture->allocateStorage(QOpenGLTexture::BGR, QOpenGLTexture::UInt8); 
}

void GLWidget::setFrameData(QOpenGLTexture::PixelFormat sourceFormat,
	QOpenGLTexture::PixelType sourceType, const void *data, int width, int height) {
	if (texture->width() != width || texture->height() != height) {
		texture->destroy();
		delete texture;
		createTexture(width, height);
	}
	texture->setData(sourceFormat, sourceType, data);
	update();
}

void GLWidget::makeObject() {
	static const int coords[4][3] = {
		{ 1, -1, 0 },{ -1, -1, 0 },{ -1, +1, 0 },{ +1, +1, 0 } 
	};

	createTexture();
	QVector<GLfloat> vertData; 
	for (int j = 0; j < 4; ++j) {
		// vertex position
		vertData.append(coords[j][0]);
		vertData.append(coords[j][1]);
		vertData.append(coords[j][2]);
		// texture coordinate
		vertData.append(j == 0 || j == 3);
		vertData.append(j == 0 || j == 1);
	} 

	vbo.create();
	vbo.bind();
	vbo.allocate(vertData.constData(), vertData.count() * sizeof(GLfloat));
}  
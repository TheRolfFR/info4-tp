#include <OpenGL/shader.h>

#include <iostream>
#include <fstream>

#include <QOpenGLFunctions>
#include <QFileInfo>

using namespace std;

int isExtensionSupported(const char *extension)
{
    const GLubyte *extensions = NULL;
    const GLubyte *start;
    GLubyte *where, *terminator;

    /* Extension names should not have spaces. */
    where = (GLubyte *) strchr(extension, ' ');
    if (where || *extension == '\0')
        return 0;
    extensions = glGetString(GL_EXTENSIONS);
    /* It takes a bit of care to be fool-proof about parsing the
       OpenGL extensions string. Don't be fooled by sub-strings,
       etc. */
    start = extensions;
    for (;;) {
        where = (GLubyte *) strstr((const char *) start, extension);
        if (!where)
            break;
        terminator = where + strlen(extension);
        if (where == start || *(where - 1) == ' ')
            if (*terminator == ' ' || *terminator == '\0')
                return 1;
        start = terminator;
    }
    return 0;
}

Shader::Shader(std::string shaderName): m_programID(),
										m_vertexID(),
										m_geometryID(),
										m_fragmentID(),
                                        m_usingGeometryShader(false)
{
    /*
    std::string version = "400";
    if(!isExtensionSupported("ARB_shader_subroutine")) {
        version = 300
    }
    */
    m_vertexShaderFile = "Shaders/" + shaderName + "/vertex.glsl";
    m_geometryShaderFile = "Shaders/" + shaderName + "/geometry.glsl";
    m_fragmentShaderFile = "Shaders/" + shaderName + "/fragment.glsl";
}


Shader::~Shader()
{



}


bool Shader::load()
{
    // Destruction d'un éventuel ancien Shader
	if (glIsProgram(m_programID) == GL_TRUE)
		glDeleteProgram(m_programID);

	if (glIsShader(m_vertexID) == GL_TRUE)
		glDeleteShader(m_vertexID);

	if (glIsShader(m_geometryID) == GL_TRUE)
		glDeleteShader(m_geometryID);

	if (glIsShader(m_fragmentID) == GL_TRUE)
		glDeleteShader(m_fragmentID);

	// Compilation des shaders
	if (!compilerShader(m_vertexID, GL_VERTEX_SHADER, m_vertexShaderFile))
		return false;

    QFileInfo geometryFile(QString::fromStdString(m_geometryShaderFile));
    if (geometryFile.exists() && geometryFile.isFile()) {
        m_usingGeometryShader = true;
    }

    if(m_usingGeometryShader) {
        if (!compilerShader(m_geometryID, GL_GEOMETRY_SHADER, m_geometryShaderFile))
            return false;
    }

	if (!compilerShader(m_fragmentID, GL_FRAGMENT_SHADER, m_fragmentShaderFile))
		return false;

	// Création du programme
	m_programID = glCreateProgram();

	// Association des shaders
	glAttachShader(m_programID, m_vertexID);
    //if(m_usingGeometryShader)
	//    glAttachShader(m_programID, m_geometryID);
	glAttachShader(m_programID, m_fragmentID);

	// Verrouillage des entrées shader
	glBindAttribLocation(m_programID, 0, "in_Vertex");
	glBindAttribLocation(m_programID, 1, "in_UV");
	glBindAttribLocation(m_programID, 3, "in_Type");
	glBindAttribLocation(m_programID, 4, "in_Alpha");

	// Linkage du programme
	glLinkProgram(m_programID);

	// Vérification du linkage
	GLint erreurLink(0);
	glGetProgramiv(m_programID, GL_LINK_STATUS, &erreurLink);

	// S'il y a eu une erreur
	if (erreurLink != GL_TRUE)
	{
		// Récupération de la taille de l'erreur
		GLint tailleErreur(0);
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &tailleErreur);

		// Allocation de mémoire
		char *erreur = new char[tailleErreur + 1];

		// Récupération de l'erreur
		glGetShaderInfoLog(m_programID, tailleErreur, &tailleErreur, erreur);
		erreur[tailleErreur] = '\0';

		// Affichage de l'erreur
		cout << "Shader error: " << erreur << endl;

		// Libération de la mémoire et retour du booléen false
		delete[] erreur;
		glDeleteProgram(m_programID);

		return false;
	} else { // Sinon c'est que tout s'est bien passé
		return true;
	}
}


void Shader::bind()
{
    glUseProgram(m_programID);
}


void Shader::unbind()
{
	glUseProgram(0);
}


bool Shader::compilerShader(GLuint &shader, GLenum type, string const &fichierSource)
{
	// Création du shader
	shader = glCreateShader(type);

	// Vérification du shader
	if (shader == 0) {
		std::cout << "Erreur, le type de shader (" << type << ") n'existe pas" << std::endl;
		return false;
	}

	// Flux de lecture
	ifstream fichier(fichierSource.c_str());

	// Test d'ouverture
	if (!fichier) {
		std::cout << "Erreur le fichier " << fichierSource << " est introuvable" << std::endl;
		glDeleteShader(shader);
		return false;
	}

	// Strings permettant de lire le code source
	std::string ligne;
	std::string codeSource;

	// Lecture
	while (getline(fichier, ligne))
		codeSource += ligne + '\n';

	// Fermeture du fichier
	fichier.close();

	// Récupération de la chaine C du code source
	const GLchar* chaineCodeSource = codeSource.c_str();

	// Envoi du code source au shader
	glShaderSource(shader, 1, &chaineCodeSource, 0);

	// Compilation du shader
	glCompileShader(shader);

	// Vérification de la compilation
	GLint erreurCompilation(0);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &erreurCompilation);

	// S'il y a eu une erreur
	if (erreurCompilation != GL_TRUE) {
		// Récupération de la taille de l'erreur
		GLint tailleErreur(0);
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &tailleErreur);

		// Allocation de mémoire
		char *erreur = new char[tailleErreur + 1];

		// Récupération de l'erreur
		glGetShaderInfoLog(shader, tailleErreur, &tailleErreur, erreur);
		erreur[tailleErreur] = '\0';

		// Affichage de l'erreur
		std::cout << erreur << std::endl;

		// Libération de la mémoire et retour du booléen false
		delete[] erreur;
		glDeleteShader(shader);

		return false;
	} else // Sinon c'est que tout s'est bien passé
	    return true;
}

    
GLuint Shader::getSubroutineIndex(GLenum shader_type, std::string name) {
   return glGetSubroutineIndex(m_programID, shader_type, name.c_str());
}

    
void Shader::bindSubroutine(GLenum shader_type, GLuint index) {
    glUniformSubroutinesuiv(shader_type, 1, &index);
}


void Shader::setUniformValue(string name, int &i) {
	int location = glGetUniformLocation(m_programID, name.c_str());
    glUniform1i(location, i);
}


void Shader::setUniformValue(string name, long unsigned int &i) {
	int location = glGetUniformLocation(m_programID, name.c_str());
    glUniform1ui(location, i);
}


void Shader::setUniformValue(string name, float &f) {
	int location = glGetUniformLocation(m_programID, name.c_str());
    glUniform1f(location, f);
}


void Shader::setUniformValue(string name, QVector2D &v) {
	int location = glGetUniformLocation(m_programID, name.c_str());
    glUniform2f(location, v.x(), v.y());
}


void Shader::setUniformValue(string name, QVector3D &v) {
	int location = glGetUniformLocation(m_programID, name.c_str());
    glUniform3f(location, v.x(), v.y(), v.z());
}


void Shader::setUniformValue(string name, QVector4D &v) {
	int location = glGetUniformLocation(m_programID, name.c_str());
    glUniform4f(location, v.x(), v.y(), v.z(), v.w());
}


void Shader::setUniformValue(string name, QMatrix4x4 &m) {
	int location = glGetUniformLocation(m_programID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, m.data());
}


void Shader::setUniformValues(string name, GLuint size, float* f) {
	int location = glGetUniformLocation(m_programID, name.c_str());
    glUniform2fv(location, size, f);
}

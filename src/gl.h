#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "blib/blib.h"
#include "blib/blib_math.h"
#include "blib/blib_math3d.h"
#include "blib/blib_file.h"

DECLARE_LIST(GLint)
DECLARE_LIST(GLuint)

void error_callback(const int error, const char *description);

void key_callback(
		GLFWwindow *window, 
		const int key, 
		const int scancode, 
		const int action, 
		const int mods);

void APIENTRY glDebugOutput(
	const GLenum source, 
	const GLenum type, 
	const unsigned int id, 
	const GLenum severity, 
	const GLsizei length, 
	const char *message, 
	const void *userParam);

GLuint texture_create(const char *imageFile);

GLuint shader_create(const char *vertexShaderSourcePath, const char *fragmentShaderSourcePath);
void shader_setUniformM4(GLuint shader, const char *uniformName, mat4_t *m);
void shader_setUniformV3(GLuint shader, const char *uniformName, vec3_t v);
void shader_setUniformV4(GLuint shader, const char* uniformName, const vec4_t color);
void shader_setUniformFloat(GLuint shader, const char *uniformName, GLfloat f);
void shader_setUniformInt(GLuint shader, const char *uniformName, GLuint i);

typedef struct pointLight {
	float constant;
	float linear;
	float quadratic;
	vec3_t diffuse;
	vec3_t specular;
} pointLight_t;
DECLARE_LIST(pointLight_t)

typedef struct {
	vec3_t position;
	vec2_t texCoord;
	vec3_t normal;
} vertex_t;
DECLARE_LIST(vertex_t)

typedef struct {
	bool enabled;
  GLuint VAO;
  GLuint VBO;
  GLuint EBO;
  vertex_t *vertices;
  GLuint vertices_length;
  GLuint *indices;
  GLuint indices_length;
  bool use_wire_frame;
} mesh_t;
DECLARE_LIST(mesh_t)

typedef struct {
	GLuint shader;
	GLuint diffuseMap;
	GLuint specularMap;
} material_t;
	
typedef struct {
  mat4_t matrix;
  vec3_t position;
  quat_t rotation;
  vec3_t scale;
} transform_t;
DECLARE_LIST(transform_t)

void transform_calculate_matrix(transform_t *t);
void transform_calculate_view_matrix(transform_t *t);
vec3_t transform_basis_forward(transform_t t, float magnitude);
vec3_t transform_basis_up(transform_t t, float magnitude);
vec3_t transform_basis_right(transform_t t, float magnitude);
vec3_t transform_basis_back(transform_t t, float magnitude);
vec3_t transform_basis_down(transform_t t, float magnitude);
vec3_t transform_basis_left(transform_t t, float magnitude);

typedef struct {
  transform_t transform;
mat4_t projection;
  float lookSensitivity;
  float lastX;
  float lastY;
} camera_t;

#define MESH_QUAD_NUM_VERTICES 4
#define MESH_QUAD_NUM_INDICES 6
#define MESH_CUBE_NUM_VERTICES 24
#define MESH_CUBE_NUM_INDICES 36

static vertex_t mesh_quad_vertices[MESH_QUAD_NUM_VERTICES] = {
	//positions         //tex	      //normal
	{ { 0.5f,  0.5f, 0.0f }, { 1.0f, 1.0f }, { 0.0,  1.0,  0.0 } },// top right
	{ { 0.5f, -0.5f, 0.0f }, { 1.0f, 0.0f }, { 0.0,  1.0,  0.0 } },// bottom right
	{ {-0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f }, { 0.0,  1.0,  0.0 } },// bottom left
	{ {-0.5f,  0.5f, 0.0f }, { 0.0f, 1.0f }, { 0.0,  1.0,  0.0 } },// top left 
};

static unsigned int mesh_quad_indices[MESH_QUAD_NUM_INDICES] = {
	3, 1, 0,  // first Triangle
	3, 2, 1   // second Triangle
};

static vertex_t mesh_cube_vertices[MESH_CUBE_NUM_VERTICES] = {
	// position            //tex          //normal
	{ {-0.5,  0.5,  0.5 }, { 0.0,  1.0 }, { 0.0,  1.0,  0.0 } },
	{ {-0.5,  0.5, -0.5 }, { 0.0,  0.0 }, { 0.0,  1.0,  0.0 } },
	{ { 0.5,  0.5, -0.5 }, { 1.0,  0.0 }, { 0.0,  1.0,  0.0 } },
	{ { 0.5,  0.5,  0.5 }, { 1.0,  1.0 }, { 0.0,  1.0,  0.0 } },
	{ {-0.5,  0.5,  0.5 }, { 0.0,  1.0 }, {-1.0,  0.0,  0.0 } },
	{ {-0.5, -0.5,  0.5 }, { 0.0,  0.0 }, {-1.0,  0.0,  0.0 } },
	{ {-0.5, -0.5, -0.5 }, { 1.0,  0.0 }, {-1.0,  0.0,  0.0 } },
	{ {-0.5,  0.5, -0.5 }, { 1.0,  1.0 }, {-1.0,  0.0,  0.0 } },
	{ {-0.5,  0.5, -0.5 }, { 0.0,  1.0 }, { 0.0,  0.0, -1.0 } },
	{ {-0.5, -0.5, -0.5 }, { 0.0,  0.0 }, { 0.0,  0.0, -1.0 } },
	{ { 0.5, -0.5, -0.5 }, { 1.0,  0.0 }, { 0.0,  0.0, -1.0 } },
	{ { 0.5,  0.5, -0.5 }, { 1.0,  1.0 }, { 0.0,  0.0, -1.0 } },
	{ { 0.5,  0.5, -0.5 }, { 0.0,  1.0 }, { 1.0,  0.0,  0.0 } },
	{ { 0.5, -0.5, -0.5 }, { 0.0,  0.0 }, { 1.0,  0.0,  0.0 } },
	{ { 0.5, -0.5,  0.5 }, { 1.0,  0.0 }, { 1.0,  0.0,  0.0 } },
	{ { 0.5,  0.5,  0.5 }, { 1.0,  1.0 }, { 1.0,  0.0,  0.0 } },
	{ { 0.5,  0.5,  0.5 }, { 0.0,  1.0 }, { 0.0,  0.0,  1.0 } },
	{ { 0.5, -0.5,  0.5 }, { 0.0,  0.0 }, { 0.0,  0.0,  1.0 } },
	{ {-0.5, -0.5,  0.5 }, { 1.0,  0.0 }, { 0.0,  0.0,  1.0 } },
	{ {-0.5,  0.5,  0.5 }, { 1.0,  1.0 }, { 0.0,  0.0,  1.0 } },
	{ {-0.5, -0.5, -0.5 }, { 0.0,  1.0 }, { 0.0, -1.0,  0.0 } },
	{ {-0.5, -0.5,  0.5 }, { 0.0,  0.0 }, { 0.0, -1.0,  0.0 } },
	{ { 0.5, -0.5,  0.5 }, { 1.0,  0.0 }, { 0.0, -1.0,  0.0 } },
	{ { 0.5, -0.5, -0.5 }, { 1.0,  1.0 }, { 0.0, -1.0,  0.0 } },
};

static GLuint mesh_cube_indices[MESH_CUBE_NUM_INDICES] = {
	0,1,2,    0,2,3,    4,5,6,    4,6,7,    8,9,10,   8,10,11,
	12,13,14, 12,14,15, 16,17,18, 16,18,19, 20,21,22, 20,22,23,
};

mesh_t mesh_alloc(vertex_t* vertices, GLuint vertices_length,
		GLuint* indices, GLuint num_vertices);
mesh_t mesh_alloc_cube(void);
mesh_t mesh_alloc_quad(void);

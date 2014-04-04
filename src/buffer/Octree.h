/*
 * Octree.h
 *
 *  Created on: 20/11/2013
 *      Author: remnanjona
 */

#ifndef OCTREE_H_
#define OCTREE_H_



#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Buffer.h"

namespace std {

struct Node {
	int child[8];
};

struct OctreeBuffer {
	Node n[3000000];
};

class Octree {
public:
	GLuint addr;
	unsigned int levels;

	Octree(unsigned int);
	virtual ~Octree();

	int genNode(glm::ivec3, glm::ivec3);

	void bind(GLuint);

private:
	Buffer<OctreeBuffer> ob;
	int free_ind;
};

} /* namespace std */
#endif /* OCTREE_H_ */

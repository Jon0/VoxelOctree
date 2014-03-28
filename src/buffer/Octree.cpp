/*
 * Texture.cpp
 *
 *  Created on: 20/11/2013
 *      Author: remnanjona
 */

#include <stdlib.h>

#include "Octree.h"

namespace std {

struct uc_rgba {
	unsigned char r, g, b, a;
};

void makeSphere(uc_rgba *image_data, int levels, glm::vec3 mid, float radius) {
	for (int i = 0; i < levels; ++i) {
		for (int j = 0; j < levels; ++j) {
			for (int k = 0; k < levels; ++k) {
				float dist = glm::distance(mid, glm::vec3(i,j,k));
				if (dist < radius) {
					glm::vec3 n =  glm::vec3(i,j,k) - mid;
					if (glm::length(n) > 0) n = glm::normalize(n);
					image_data[i + j * levels + k * levels * levels] = {128 + 128*n.x, 128 + 128*n.y, 128 + 128*n.y, 255};
				}
			}
		}
	}
}

Octree::Octree(unsigned int l) {
	levels = l;
	glGenTextures(1, &addr);
	glBindTexture(GL_TEXTURE_3D, addr);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);

	uc_rgba *image_data = new uc_rgba [levels*levels*levels]();

	for (int s = 0; s < 20; ++s) {
		glm::vec3 mid = glm::vec3(levels/4.0f + rand()%levels/2.0f,
				levels/4.0f + rand()%levels/2.0f,
				levels/4.0f + rand()%levels/2.0f);

		float radius = rand() % levels/10.0f;
		makeSphere(image_data, levels, mid, radius);
	}


	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA8, levels, levels, levels, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, image_data);

	//glGenerateMipmap(GL_TEXTURE_3D);

}

Octree::~Octree() {
	// TODO Auto-generated destructor stub
}

void Octree::bind(GLuint i) {
	glBindImageTexture(i, addr, 0, GL_TRUE, 0, GL_READ_WRITE, GL_RGBA8);
}

} /* namespace std */

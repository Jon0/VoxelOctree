/*
 * Renderer.cpp
 *
 *  Created on: 24/03/2014
 *      Author: remnanjona
 */


#include "../pipeline/Pipeline.h"
#include "../shader/Shader.h"
#include "Renderer.h"

namespace std {

Renderer::Renderer(): buff(GL_ARRAY_BUFFER) {

	vector<texvec> data = {
			{glm::vec4(-1,-1,0,1), glm::vec2(0,0)}, {glm::vec4(1,-1,0,1), glm::vec2(1,0)},
			{glm::vec4(-1,1,0,1), glm::vec2(0,1)}, {glm::vec4(1,1,0,1), glm::vec2(1,1)}
	};

    // Init Pipeline
    Shader test_vert("glsl/test.vert", GL_VERTEX_SHADER);
    Shader test_frag("glsl/test.frag", GL_FRAGMENT_SHADER);
    tex_pipeline.addStage(test_vert, GL_VERTEX_SHADER_BIT);
    tex_pipeline.addStage(test_frag, GL_FRAGMENT_SHADER_BIT);
}

Renderer::~Renderer() {
	// TODO Auto-generated destructor stub
}

void Renderer::draw() {
	glBindProgramPipeline(tex_pipeline.name);

	glBindBuffer( GL_ARRAY_BUFFER, buff.location );
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(texvec) * 4, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(texvec) * 4, (GLvoid*)sizeof(glm::vec4));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindTexture(GL_TEXTURE_RECTANGLE_NV, t.texture);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

} /* namespace std */

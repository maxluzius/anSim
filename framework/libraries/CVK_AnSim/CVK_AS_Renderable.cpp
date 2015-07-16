#include "CVK_AS_Renderable.h"

CVK::Renderable::Renderable()
{
	m_color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

	setupBuffers();
}

CVK::Renderable::~Renderable()
{
	glDeleteBuffers(1, m_vertexBuffer);
	glDeleteVertexArrays(1, m_vao);
}

void CVK::Renderable::setupBuffers()
{
	glGenBuffers(4, m_vertexBuffer);
	glGenVertexArrays(4, m_vao);
	glBindVertexArray(m_vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[0]);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(m_vao[1]);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[1]);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(m_vao[2]);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[2]);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(m_vao[3]);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[3]);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}


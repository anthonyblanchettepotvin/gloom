#include "Mesh.h"

#include <glad/glad.h>

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, Material* material)
	: vertices(vertices), indices(indices), material(material)
{
	SetupMesh();
}

void Mesh::Draw(Shader* shader)
{
	if (material)
	{
		material->Bind(shader);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}

void Mesh::SetupMesh()
{
	/* We create a Vertex Array Object (VAO). Any subsequent vertex attribute calls
	from that point on will be stored inside the VAO (including the VBAs associated
	with the vertex attributes based on the calls). Also, the last call to
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ...), which is used to bind an EBO,
	is stored in the VAO. We can simply bind the VAO to automatically bind the VBO,
	make the EBO binding call and all the vertex attribute calls. */
	/* Note that usually, when you have multiple object to draw, you first generate and
	configurate all the VAOs (and thus the required VBO, EBO and attribute pointers) and
	store those for later use. */
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	/* We create a Vertex Buffer Object (VBO) that contains all the vertices that we
	want to send to the GPU's memory for fast access. */
	/* Note that sending data to the GPU from the CPU is slow, so we want to send as much
	data as possible at once. */
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	/* The following function is targeted to copy user-defined data into the currently
	bound buffer. */
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	/* Here, we indicate how OpenGL should interpret the vertex data. */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoordinates));
	glEnableVertexAttribArray(2);

	/* Here, we create the Element Buffer Object (EBO) that contains the order, using the
	vertices' index, in which OpenGL should draw our triangles. */
	/* Once again, sending data to the GPU from the CPU is slow, so we want to send as much
	data as possible at once. */
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	/* All the configuration made until this point should be between bind/unbind calls. */
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	/* Note that the VAO stores the last glBindBuffer call when the target is
	GL_ELEMENT_ARRAY_BUFFER, which means it stores the unbind calls too (i.e., we call
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) to unbind the EBO). That said, it's important
	to unbind the VAO before the EBO. Otherwise, when we later bind the VAO,
	the VAO's EBO binding call is corresponding to glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0),
	leading to an unconfigured EBO. */
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

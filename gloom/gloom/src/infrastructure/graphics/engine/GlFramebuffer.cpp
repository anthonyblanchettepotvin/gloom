#include "GlFramebuffer.h"

#include <iostream>

#include <glad/glad.h>

#include "../texture/GlTexture.h"

#include "GlRenderbuffer.h"

GlFramebuffer::GlFramebuffer(size_t width, size_t height)
{
	// Framebuffer
	/* Framebuffers are useful for post-rendering effects or fancy effects like mirrors or portals.
	As usual, we generate a framebuffer object and bind it so all subsequent calls on the GL_FRAMEBUFFER
	target (or whatever target has been specified) applies to the currently bound framebuffer object.
	When the framebuffer object is complete, all subsequent rendering calls will render into the
	currently bound framebuffer object. */
	glGenFramebuffers(1, &m_Id);
}

void GlFramebuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_Id);
}

void GlFramebuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

bool GlFramebuffer::CheckStatus()
{
	Bind();

	/* Check if all the conditions to a complete framebuffer are met.
	The list of conditions can be found at https://learnopengl.com/Advanced-OpenGL/Framebuffers. */
	bool isValid = glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE;

	Unbind();

	return isValid;
}

void GlFramebuffer::BindRenderbuffer(const GlRenderbuffer& renderbuffer)
{
	Bind();

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer.GetId());

	Unbind();
}

void GlFramebuffer::BindTexture(const GlTexture& texture)
{
	Bind();

	// Texture attachment
	/* We attach the texture to the framebuffer
	as a color attachment. Note that we can attach a texture as a depth and/or stencil attachment too.
	In that case, we would need to change the texture's format accordingly. */
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.GetId(), 0);

	Unbind();
}

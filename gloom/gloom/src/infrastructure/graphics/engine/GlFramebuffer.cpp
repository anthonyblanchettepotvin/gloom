#include "GlFramebuffer.h"

#include <iostream>

#include <glad/glad.h>

#include "GlRenderbufferAttachment.h"
#include "GlTextureAttachment.h"

void GlFramebuffer::Initialize()
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

void GlFramebuffer::AttachRenderbuffer(const GlRenderbufferAttachment& renderbufferAttachment)
{
	Bind();

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbufferAttachment.GetId());

	Unbind();
}

void GlFramebuffer::AttachTexture(const GlTextureAttachment& textureAttachment)
{
	Bind();

	// Texture attachment
	/* We attach the texture to the framebuffer
	as a color attachment. Note that we can attach a texture as a depth and/or stencil attachment too.
	In that case, we would need to change the texture's format accordingly. */
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureAttachment.GetId(), 0);

	Unbind();
}

bool GlFramebuffer::IsComplete()
{
	Bind();

	/* Check if all the conditions to a complete framebuffer are met.
	The list of conditions can be found at https://learnopengl.com/Advanced-OpenGL/Framebuffers. */
	bool isComplete = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;

	Unbind();

	return isComplete;
}

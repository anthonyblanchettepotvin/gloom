#include "GlRenderbufferAttachment.h"

#include <glad/glad.h>

GlRenderbufferAttachment::GlRenderbufferAttachment(size_t width, size_t height)
{
	// Renderbuffer attachment
	/* We create a renderbuffer the size of our viewport and we attach the renderbuffer to the framebuffer
	as a depth and stencil attachment. Note that we can attach a renderbuffer as a color attachment too. */
	/* Note that you can sample renderbuffers, but it's slow since they are optimized and designed for writing operations.
	That said, if you plan to sample the framebuffer, it's best to use texture attachments, otherwise you may want
	to use renderbuffer attachments to improve writing latency. That said, we use a renderbuffer for our depth and stencil
	attachment since we only want to sample the color attachment. */
	glGenRenderbuffers(1, &m_Id);
	glBindRenderbuffer(GL_RENDERBUFFER, m_Id);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

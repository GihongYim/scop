#include "context.h"
#include "image.h"

ContextUPtr Context::Create() {
	auto context = ContextUPtr(new Context());
	if (!context->Init())
		return nullptr;
	return std::move(context);
}

bool Context::Init() {

	// float vertices[] = {
	// 	0.5f, 0.5f, 0.0f, // top right
	// 	0.5f, -0.5f, 0.0f, // bottom right
	// 	-0.5f, -0.5f, 0.0f, // bottom left
	// 	-0.5f, 0.5f, 0.0f, // top left
	// };
	// uint32_t indices[] = { // note that we start from 0!
	// 	0, 1, 3, // first triangle
	// 	1, 2, 3, // second triangle
	// };

	// m_vertexLayout = VertexLayout::Create();
	// m_vertexBuffer = Buffer::CreateWithData(GL_ARRAY_BUFFER, GL_STATIC_DRAW,
	// 	vertices, sizeof(float) * 12);

	// m_vertexLayout->SetAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	// m_indexBuffer = Buffer::CreateWithData(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW,
	// 	indices, sizeof(uint32_t) * 6);


	float vertices[] = {
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	};

	m_vertexLayout = VertexLayout::Create();
	m_vertexBuffer = Buffer::CreateWithData(
		GL_ARRAY_BUFFER, GL_STATIC_DRAW,
		vertices, sizeof(float) * 32);

	m_vertexLayout->SetAttrib(0, 3, GL_FLOAT, GL_FALSE,
		sizeof(float) * 8, 0);
	m_vertexLayout->SetAttrib(1, 3, GL_FLOAT, GL_FALSE,
		sizeof(float) * 8, sizeof(float) * 3);
	m_vertexLayout->SetAttrib(2, 2, GL_FLOAT, GL_FALSE,
		sizeof(float) * 8, sizeof(float) * 6);
	

	
	// ShaderPtr vertShader = Shader::CreateFromFile("./shader/simple.vs", GL_VERTEX_SHADER);
	// ShaderPtr fragShader = Shader::CreateFromFile("./shader/simple.fs", GL_FRAGMENT_SHADER);

	ShaderPtr vertShader = Shader::CreateFromFile("./shader/texture.vs", GL_VERTEX_SHADER);
	ShaderPtr fragShader = Shader::CreateFromFile("./shader/texture.fs", GL_FRAGMENT_SHADER);

	if (!vertShader || !fragShader)
		return false;
	SPDLOG_INFO("vertex shader id: {}", vertShader->Get());
	SPDLOG_INFO("fragment shader id: {}", fragShader->Get());
	
	m_program = Program::Create({fragShader, vertShader});
	if (!m_program)
		return false;
	SPDLOG_INFO("program id: {}", m_program->Get());

	auto loc = glGetUniformLocation(m_program->Get(), "color");
	m_program->Use();
	glUniform4f(loc, 1.0f, 1.0f, 0.0f, 1.0f);

	glClearColor(0.1f, 0.2f, 0.3f, 0.0f);

	auto image = Image::Load("./image/container.jpeg");
	if (!image)
		return false;
	SPDLOG_INFO("image: {}x{}, {} channels",
		image->GetWidth(), image->GetHeight(), image->GetChannelCount());
	
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
	    image->GetWidth(), image->GetHeight(), 0,
	    GL_RGB, GL_UNSIGNED_BYTE, image->GetData());
	return true;
}

void Context::Render() {
	glClear(GL_COLOR_BUFFER_BIT);

	m_program->Use();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
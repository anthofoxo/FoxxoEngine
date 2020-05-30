#include "foxepch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"
#include "Texture.h"

#include <glm/gtc/matrix_transform.hpp>

namespace FoxxoEngine
{
	struct Renderer2DData
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> FlatColorShader;

		Ref<Texture2D> DefaultTexture;
	};

	static Renderer2DData* s_Data;

	void Renderer2D::Init()
	{
		s_Data = new Renderer2DData();

		float vertices[] =
		{
			-0.5f, -0.5f,
			0.5f, -0.5f,
			0.5f, 0.5f,
			-0.5f, 0.5f
		};

		unsigned int indices[] =
		{
			0, 1, 2, 2, 3, 0
		};

		s_Data->QuadVertexArray = FoxxoEngine::VertexArray::Create();

		FoxxoEngine::BufferLayout layout = {
			{FoxxoEngine::ShaderDataType::Float2, "position"}
		};

		Ref<VertexBuffer> vbo = FoxxoEngine::VertexBuffer::Create(vertices, sizeof(vertices));
		vbo->SetLayout(layout);

		Ref<IndexBuffer> ibo = FoxxoEngine::IndexBuffer::Create(indices, sizeof(indices));

		s_Data->QuadVertexArray->AddVertexBuffer(vbo);
		s_Data->QuadVertexArray->SetIndexBuffer(ibo);

		s_Data->FlatColorShader = FoxxoEngine::Shader::Create("assets/shaders/flat2D.glsl");

		unsigned char data[] = { 255u, 255u, 255u, 255u };
		s_Data->DefaultTexture = Texture2D::Create(1, 1, data);
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthoCamera& camera)
	{
		FoxxoEngine::RenderCommand::SetClearColor({ 0, 0, 0, 1 });
		FoxxoEngine::RenderCommand::Clear();

		s_Data->FlatColorShader->Bind();
		s_Data->FlatColorShader->UploadUniformMat4f("u_Projection", camera.GetProjectionMatrix());
		s_Data->FlatColorShader->UploadUniformMat4f("u_View", camera.GetViewMatrix());
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad(pos, size, color, s_Data->DefaultTexture);
	}

	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawQuad(pos, size, { 1.0f, 1.0f, 1.0f, 1.0f }, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color, const Ref<Texture2D>& texture)
	{
		DrawQuad(glm::vec3({ pos, 0.0f }), size, color, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad(pos, size, color, s_Data->DefaultTexture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawQuad(pos, size, { 1.0f, 1.0f, 1.0f, 1.0f }, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, const Ref<Texture2D>& texture)
	{
		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, pos);
		transform = glm::scale(transform, { size, 1.0f });

		s_Data->FlatColorShader->Bind();
		s_Data->FlatColorShader->UploadUniformMat4f("u_Model", transform);
		s_Data->FlatColorShader->UploadUniform4f("u_Color", color);
		s_Data->FlatColorShader->UploadUniform1i("u_Diffuse", 0);

		texture->Bind();
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}
}
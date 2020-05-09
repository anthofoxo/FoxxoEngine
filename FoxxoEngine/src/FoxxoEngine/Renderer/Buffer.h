#pragma once

namespace FoxxoEngine
{
	enum struct ShaderDataType
	{
		None = 0,
		Float, Float2, Float3, Float4,
		Mat2, Mat3, Mat4,
		Int, Int2, Int3, Int4,
		Bool
	};

	static uint32_t ShaderDataTypeCount(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:		return 1;
			case ShaderDataType::Float2:	return 2;
			case ShaderDataType::Float3:	return 3;
			case ShaderDataType::Float4:	return 4;
			case ShaderDataType::Mat2:		return 2 * 2;
			case ShaderDataType::Mat3:		return 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4;
			case ShaderDataType::Int:		return 1;
			case ShaderDataType::Int2:		return 2;
			case ShaderDataType::Int3:		return 3;
			case ShaderDataType::Int4:		return 4;
			case ShaderDataType::Bool:		return 1;
		}

		FOXE_CORE_ASSERT(false, "Unknown shader datatype");
		return 0;
	}

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:		return sizeof(float) * 1;
			case ShaderDataType::Float2:	return sizeof(float) * 2;
			case ShaderDataType::Float3:	return sizeof(float) * 3;
			case ShaderDataType::Float4:	return sizeof(float) * 4;
			case ShaderDataType::Mat2:		return sizeof(float) * 2 * 2;
			case ShaderDataType::Mat3:		return sizeof(float) * 3 * 3;
			case ShaderDataType::Mat4:		return sizeof(float) * 4 * 4;
			case ShaderDataType::Int:		return sizeof(int) * 1;
			case ShaderDataType::Int2:		return sizeof(int) * 2;
			case ShaderDataType::Int3:		return sizeof(int) * 3;
			case ShaderDataType::Int4:		return sizeof(int) * 4;
			case ShaderDataType::Bool:		return sizeof(bool) * 1;
		}

		FOXE_CORE_ASSERT(false, "Unknown shader datatype");
		return 0;
	}

	struct BufferElement
	{
		std::string m_Name;
		ShaderDataType m_Type;
		uint32_t m_Size;
		uint32_t m_Offset;
		bool m_Normalized;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: m_Type(type), m_Name(name), m_Size(ShaderDataTypeSize(type)), m_Offset(0), m_Normalized(normalized) {}
	};

	struct BufferLayout
	{
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride;

		BufferLayout()
			: m_Stride(0) {}
		BufferLayout(const std::initializer_list<BufferElement>& elements);

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	};

	struct VertexBuffer
	{
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static VertexBuffer* Create(void* data, size_t size);
	};

	struct IndexBuffer
	{
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual int GetCount() const = 0;

		static IndexBuffer* Create(void* data, size_t size);
	};
}
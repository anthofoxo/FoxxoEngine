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
			case ShaderDataType::Float:		return 1 * 1;
			case ShaderDataType::Float2:	return 1 * 2;
			case ShaderDataType::Float3:	return 1 * 3;
			case ShaderDataType::Float4:	return 1 * 4;
			case ShaderDataType::Mat2:		return 1 * 2 * 2;
			case ShaderDataType::Mat3:		return 1 * 3 * 3;
			case ShaderDataType::Mat4:		return 1 * 4 * 4;
			case ShaderDataType::Int:		return 1 * 1;
			case ShaderDataType::Int2:		return 1 * 2;
			case ShaderDataType::Int3:		return 1 * 3;
			case ShaderDataType::Int4:		return 1 * 4;
			case ShaderDataType::Bool:		return 1 * 1;
		}

		FOXE_CORE_ASSERT(false, "Unknown shader datatype");
		return 0;
	}

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:		return 4 * 1;
			case ShaderDataType::Float2:	return 4 * 2;
			case ShaderDataType::Float3:	return 4 * 3;
			case ShaderDataType::Float4:	return 4 * 4;
			case ShaderDataType::Mat2:		return 4 * 2 * 2;
			case ShaderDataType::Mat3:		return 4 * 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4 * 4;
			case ShaderDataType::Int:		return 4 * 1;
			case ShaderDataType::Int2:		return 4 * 2;
			case ShaderDataType::Int3:		return 4 * 3;
			case ShaderDataType::Int4:		return 4 * 4;
			case ShaderDataType::Bool:		return 1 * 1;
		}

		FOXE_CORE_ASSERT(false, "Unknown shader datatype");
		return 0;
	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		BufferElement(ShaderDataType type, const std::string &name, bool normalized = false)
			: Type(type), Name(name), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		};

	};

	struct BufferLayout
	{
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement> &elements)
			: m_elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			m_stride = 0;

			for (auto &element : m_elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_stride += element.Size;
			}
		}

		std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }

		std::vector<BufferElement> m_elements;
		uint32_t m_stride = 0;
	};

	struct Buffer
	{
		virtual ~Buffer() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout &layout) = 0;

		static Buffer *create(uint32_t type, uint32_t drawMode, void *data, size_t size);
	};
}
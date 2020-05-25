#type vert
#version 330 core

layout (location = 0) in vec3 vert_pos;
layout (location = 1) in vec2 vert_texCoord;

out vec2 frag_texCoord;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * vec4(vert_pos, 1.0);
	frag_texCoord = vert_texCoord;
}

#type frag
#version 330 core

in vec2 frag_texCoord;

layout (location = 0) out vec4 out_color;

uniform sampler2D u_texture;

void main()
{
	out_color = texture(u_texture, frag_texCoord);
}
#type vert
#version 330 core

layout (location = 0) in vec2 vert_pos;

out vec2 frag_textureCoord;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * vec4(vert_pos, 0.0, 1.0);
	frag_textureCoord = vert_pos + 0.5;
}

#type frag
#version 330 core

in vec2 frag_textureCoord;

layout (location = 0) out vec4 out_color;

uniform vec4 u_Color;
uniform sampler2D u_Diffuse;

void main()
{
	out_color = texture(u_Diffuse, frag_textureCoord) * u_Color;
}
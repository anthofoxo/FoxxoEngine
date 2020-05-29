#type vert
#version 330 core

layout (location = 0) in vec3 vert_pos;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * vec4(vert_pos, 1.0);
}

#type frag
#version 330 core

uniform vec3 u_Color;

layout (location = 0) out vec4 out_color;

void main()
{
	out_color = vec4(u_Color, 1.0);
}
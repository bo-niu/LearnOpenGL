#version 330 core

//location = 0 => index of our attribute(match with glVertexAttribPointer)
//use vec4 instead of vec2 for convenience(just use vec4 all time)

layout(location  = 0) in vec4 position;
void main()
{
	gl_Position = position;
};
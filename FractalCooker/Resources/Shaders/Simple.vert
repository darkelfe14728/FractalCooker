attribute highp vec3 vertex;

uniform mediump mat4 projection;
uniform mediump mat4 modelview;

void main(void)
{
	gl_Position = projection * modelview * vec4(vertex, 1.0);
}

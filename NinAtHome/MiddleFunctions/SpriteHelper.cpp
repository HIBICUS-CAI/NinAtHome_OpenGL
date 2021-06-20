#include "SpriteHelper.h"
#include "main.h"

struct VERTEX_3D
{
	Float3 Position;
	Float4 Color;
	Float2 TexCoord;
};

void DrawSprite(float x, float y, float width, float height,
	float tx, float ty, float tw, float th,
	Float4 color)
{
	VERTEX_3D vertex[4];

	float hw, hh;
	hw = width * 0.5f;
	hh = height * 0.5f;

	vertex[0].Position = MakeFloat3(x + hw, y - hh, 0.0f);
	vertex[1].Position = MakeFloat3(x - hw, y - hh, 0.0f);
	vertex[2].Position = MakeFloat3(x + hw, y + hh, 0.0f);
	vertex[3].Position = MakeFloat3(x - hw, y + hh, 0.0f);

	vertex[0].Color = color;
	vertex[1].Color = color;
	vertex[2].Color = color;
	vertex[3].Color = color;

	vertex[0].TexCoord = MakeFloat2(tx + tw, ty);
	vertex[1].TexCoord = MakeFloat2(tx, ty);
	vertex[2].TexCoord = MakeFloat2(tx + tw, ty + th);
	vertex[3].TexCoord = MakeFloat2(tx, ty + th);

#ifdef NIN_AT_HOME
	VERTEX* v = new VERTEX[ARRAYSIZE(vertex)];
	for (int i = 0; i < ARRAYSIZE(vertex); i++)
	{
		v[i].Position = vertex[i].Position;
		v[i].Color = vertex[i].Color;
		v[i].TexCoord = vertex[i].TexCoord;
	}
	SetVertexAttr(v, ARRAYSIZE(vertex));
	delete[] v;
#else
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		sizeof(VERTEX_3D), (GLvoid*)&vertex->Position);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE,
		sizeof(VERTEX_3D), (GLvoid*)&vertex->Color);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
		sizeof(VERTEX_3D), (GLvoid*)&vertex->TexCoord);
#endif // NIN_AT_HOME

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

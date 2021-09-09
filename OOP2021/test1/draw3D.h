struct triangle
{
	vec3d p[3];
	int light;
};
struct mesh
{
	vector<triangle> tris;
};
struct mat4x4
{
	double m[4][4] = { 0 };
};
vec3d Vector_Add(vec3d& v1, vec3d& v2)
{
	return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}
vec3d Vector_Sub(vec3d& v1, vec3d& v2)
{
	return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}
vec3d Vector_Mul(vec3d& v1, float k)
{
	return { v1.x * k, v1.y * k, v1.z * k };
}
vec3d Vector_Div(vec3d& v1, float k)
{
	return { v1.x / k, v1.y / k, v1.z / k };
}
float Vector_DotProduct(vec3d& v1, vec3d& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
float Vector_Length(vec3d& v)
{
	return sqrtf(Vector_DotProduct(v, v));
}
vec3d Vector_Normalise(vec3d& v)
{
	float l = Vector_Length(v);
	return { v.x / l, v.y / l, v.z / l };
}
vec3d Vector_CrossProduct(vec3d& v1, vec3d& v2)
{
	vec3d v;
	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return v;
}
vec3d Matrix_MultiplyVector(mat4x4& m, vec3d& i)
{
	vec3d v;
	v.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + i.w * m.m[3][0];
	v.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + i.w * m.m[3][1];
	v.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + i.w * m.m[3][2];
	v.w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + i.w * m.m[3][3];
	return v;
}
mat4x4 Matrix_MultiplyMatrix(mat4x4& m1, mat4x4& m2)
{
	mat4x4 matrix;
	for (int c = 0; c < 4; c++)
		for (int r = 0; r < 4; r++)
			matrix.m[r][c] = m1.m[r][0] * m2.m[0][c] + m1.m[r][1] * m2.m[1][c] + m1.m[r][2] * m2.m[2][c] + m1.m[r][3] * m2.m[3][c];
	return matrix;
}
mat4x4 Matrix_MakeIdentity()
{
	mat4x4 matrix;
	matrix.m[0][0] = 1.0f;
	matrix.m[1][1] = 1.0f;
	matrix.m[2][2] = 1.0f;
	matrix.m[3][3] = 1.0f;
	return matrix;
}
mat4x4 Matrix_MakeRotationX(float fAngleRad)
{
	mat4x4 matrix;
	matrix.m[0][0] = 1.0f;
	matrix.m[1][1] = cosf(fAngleRad);
	matrix.m[1][2] = sinf(fAngleRad);
	matrix.m[2][1] = -sinf(fAngleRad);
	matrix.m[2][2] = cosf(fAngleRad);
	matrix.m[3][3] = 1.0f;
	return matrix;
}

mat4x4 Matrix_MakeRotationY(float fAngleRad)
{
	mat4x4 matrix;
	matrix.m[0][0] = cosf(fAngleRad);
	matrix.m[0][2] = sinf(fAngleRad);
	matrix.m[2][0] = -sinf(fAngleRad);
	matrix.m[1][1] = 1.0f;
	matrix.m[2][2] = cosf(fAngleRad);
	matrix.m[3][3] = 1.0f;
	return matrix;
}

mat4x4 Matrix_MakeRotationZ(float fAngleRad)
{
	mat4x4 matrix;
	matrix.m[0][0] = cosf(fAngleRad);
	matrix.m[0][1] = sinf(fAngleRad);
	matrix.m[1][0] = -sinf(fAngleRad);
	matrix.m[1][1] = cosf(fAngleRad);
	matrix.m[2][2] = 1.0f;
	matrix.m[3][3] = 1.0f;
	return matrix;
}
mat4x4 Matrix_MakeTranslation(float x, float y, float z)
{
	mat4x4 matrix;
	matrix.m[0][0] = 1.0f;
	matrix.m[1][1] = 1.0f;
	matrix.m[2][2] = 1.0f;
	matrix.m[3][3] = 1.0f;
	matrix.m[3][0] = x;
	matrix.m[3][1] = y;
	matrix.m[3][2] = z;
	return matrix;
}
mat4x4 Matrix_MakeProjection(float fFovDegrees, float fAspectRatio, float fNear, float fFar)
{
	float fFovRad = 1.0f / tanf(fFovDegrees * 0.5f / 180.0f * 3.14159f);
	mat4x4 matrix;
	matrix.m[0][0] = fAspectRatio * fFovRad;
	matrix.m[1][1] = fFovRad;
	matrix.m[2][2] = fFar / (fFar - fNear);
	matrix.m[3][2] = (-fFar * fNear) / (fFar - fNear);
	matrix.m[2][3] = 1.0f;
	matrix.m[3][3] = 0.0f;
	return matrix;
}
void rotateX(triangle& i, triangle& o, double fTheta)
{
	mat4x4 matRotX = Matrix_MakeRotationX(fTheta);
	o.p[0] = Matrix_MultiplyVector(matRotX, i.p[0]);
	o.p[1] = Matrix_MultiplyVector(matRotX, i.p[1]);
	o.p[2] = Matrix_MultiplyVector(matRotX, i.p[2]);
}
void rotateY(triangle& i, triangle& o, double fTheta)
{
	mat4x4 matRotY = Matrix_MakeRotationY(fTheta);
	o.p[0] = Matrix_MultiplyVector(matRotY, i.p[0]);
	o.p[1] = Matrix_MultiplyVector(matRotY, i.p[1]);
	o.p[2] = Matrix_MultiplyVector(matRotY, i.p[2]);
}
void rotateZ(triangle& i, triangle& o, double fTheta)
{
	mat4x4 matRotZ = Matrix_MakeRotationZ(fTheta);
	o.p[0] = Matrix_MultiplyVector(matRotZ, i.p[0]);
	o.p[1] = Matrix_MultiplyVector(matRotZ, i.p[1]);
	o.p[2] = Matrix_MultiplyVector(matRotZ, i.p[2]);
}
void project(triangle& i, triangle& o, double fFovDegrees, double fAspectRatio, double fNear, double fFar)
{
	mat4x4 matProj = Matrix_MakeProjection(fFovDegrees, fAspectRatio, fNear, fFar);
	o.p[0] = Matrix_MultiplyVector(matProj, i.p[0]);
	o.p[1] = Matrix_MultiplyVector(matProj, i.p[1]);
	o.p[2] = Matrix_MultiplyVector(matProj, i.p[2]);
}
void offset(triangle& i, triangle& o, double d)
{
	mat4x4 matTrans = Matrix_MakeTranslation(0, 0, d);
	o.p[0] = Matrix_MultiplyVector(matTrans, i.p[0]);
	o.p[1] = Matrix_MultiplyVector(matTrans, i.p[1]);
	o.p[2] = Matrix_MultiplyVector(matTrans, i.p[2]);
}
void view_space(triangle& i, triangle& o, mat4x4 matView)
{
	o.p[0] = Matrix_MultiplyVector(matView, i.p[0]);
	o.p[1] = Matrix_MultiplyVector(matView, i.p[1]);
	o.p[2] = Matrix_MultiplyVector(matView, i.p[2]);
}
void scale_into_view(triangle& i)
{
	//Projection matrix 送出來的座標 -1 <= x <= 1
	i.p[0].x = WIDTH / 2 * (i.p[0].x + 1);
	i.p[0].y = HEIGHT / 2 * (i.p[0].y + 1);
	i.p[1].x = WIDTH / 2 * (i.p[1].x + 1);
	i.p[1].y = HEIGHT / 2 * (i.p[1].y + 1);
	i.p[2].x = WIDTH / 2 * (i.p[2].x + 1);
	i.p[2].y = HEIGHT / 2 * (i.p[2].y + 1);
}
mat4x4 Matrix_PointAt(vec3d& pos, vec3d& target, vec3d& up)
{
	vec3d newForward = Vector_Sub(target, pos);
	newForward = Vector_Normalise(newForward);

	vec3d a = Vector_Mul(newForward, Vector_DotProduct(up, newForward));
	vec3d newUp = Vector_Sub(up, a);
	newUp = Vector_Normalise(newUp);
	vec3d newRight = Vector_CrossProduct(newUp, newForward);

	mat4x4 matrix;
	matrix.m[0][0] = newRight.x;	matrix.m[0][1] = newRight.y;	matrix.m[0][2] = newRight.z;	matrix.m[0][3] = 0.0f;
	matrix.m[1][0] = newUp.x;		matrix.m[1][1] = newUp.y;		matrix.m[1][2] = newUp.z;		matrix.m[1][3] = 0.0f;
	matrix.m[2][0] = newForward.x;	matrix.m[2][1] = newForward.y;	matrix.m[2][2] = newForward.z;	matrix.m[2][3] = 0.0f;
	matrix.m[3][0] = pos.x;			matrix.m[3][1] = pos.y;			matrix.m[3][2] = pos.z;			matrix.m[3][3] = 1.0f;
	return matrix;
}

mat4x4 Matrix_QuickInverse(const mat4x4& m) // Only for Rotation/Translation Matrices
{
	mat4x4 matrix;
	matrix.m[0][0] = m.m[0][0]; matrix.m[0][1] = m.m[1][0]; matrix.m[0][2] = m.m[2][0]; matrix.m[0][3] = 0.0f;
	matrix.m[1][0] = m.m[0][1]; matrix.m[1][1] = m.m[1][1]; matrix.m[1][2] = m.m[2][1]; matrix.m[1][3] = 0.0f;
	matrix.m[2][0] = m.m[0][2]; matrix.m[2][1] = m.m[1][2]; matrix.m[2][2] = m.m[2][2]; matrix.m[2][3] = 0.0f;
	matrix.m[3][0] = -(m.m[3][0] * matrix.m[0][0] + m.m[3][1] * matrix.m[1][0] + m.m[3][2] * matrix.m[2][0]);
	matrix.m[3][1] = -(m.m[3][0] * matrix.m[0][1] + m.m[3][1] * matrix.m[1][1] + m.m[3][2] * matrix.m[2][1]);
	matrix.m[3][2] = -(m.m[3][0] * matrix.m[0][2] + m.m[3][1] * matrix.m[1][2] + m.m[3][2] * matrix.m[2][2]);
	matrix.m[3][3] = 1.0f;
	return matrix;
}
vec3d Vector_IntersectPlane(vec3d& plane_p, vec3d& plane_n, vec3d& lineStart, vec3d& lineEnd)
{
	plane_n = Vector_Normalise(plane_n);
	float plane_d = -Vector_DotProduct(plane_n, plane_p);
	float ad = Vector_DotProduct(lineStart, plane_n);
	float bd = Vector_DotProduct(lineEnd, plane_n);
	float t = (-plane_d - ad) / (bd - ad);
	vec3d lineStartToEnd = Vector_Sub(lineEnd, lineStart);
	vec3d lineToIntersect = Vector_Mul(lineStartToEnd, t);
	return Vector_Add(lineStart, lineToIntersect);
}
int Triangle_ClipAgainstPlane(vec3d plane_p, vec3d plane_n, triangle& in_tri, triangle& out_tri1, triangle& out_tri2)
{
	plane_n = Vector_Normalise(plane_n);

	auto dist = [&](vec3d& p)
	{
		vec3d n = Vector_Normalise(p);
		return (plane_n.x * p.x + plane_n.y * p.y + plane_n.z * p.z - Vector_DotProduct(plane_n, plane_p));
	};


	vec3d* inside_points[3];
	int nInsidePointCount = 0;

	vec3d* outside_points[3];
	int nOutsidePointCount = 0;

	// Get signed distance of each point in triangle to plane
	float d0 = dist(in_tri.p[0]);
	float d1 = dist(in_tri.p[1]);
	float d2 = dist(in_tri.p[2]);

	if (d0 >= 0)
		inside_points[nInsidePointCount++] = &in_tri.p[0];
	else
		outside_points[nOutsidePointCount++] = &in_tri.p[0];

	if (d1 >= 0)
		inside_points[nInsidePointCount++] = &in_tri.p[1];
	else
		outside_points[nOutsidePointCount++] = &in_tri.p[1];

	if (d2 >= 0)
		inside_points[nInsidePointCount++] = &in_tri.p[2];
	else
		outside_points[nOutsidePointCount++] = &in_tri.p[2];


	if (nInsidePointCount == 0)
	{
		return 0; // No returned triangles are valid
	}

	if (nInsidePointCount == 3)
	{
		out_tri1 = in_tri;
		return 1; // Just the one returned original triangle is valid
	}

	if (nInsidePointCount == 1 && nOutsidePointCount == 2)
	{
		out_tri1.light = in_tri.light;

		out_tri1.p[0] = *inside_points[0];
		out_tri1.p[1] = Vector_IntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[0]);
		out_tri1.p[2] = Vector_IntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[1]);

		return 1; // Return the newly formed single triangle
	}

	if (nInsidePointCount == 2 && nOutsidePointCount == 1)
	{
		out_tri1.light = in_tri.light;
		out_tri2.light = in_tri.light;

		out_tri1.p[0] = *inside_points[0];
		out_tri1.p[1] = *inside_points[1];
		out_tri1.p[2] = Vector_IntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[0]);

		out_tri2.p[0] = *inside_points[1];
		out_tri2.p[1] = out_tri1.p[2];
		out_tri2.p[2] = Vector_IntersectPlane(plane_p, plane_n, *inside_points[1], *outside_points[0]);

		return 2; // Return two newly formed triangles which form a quad
	}
}
void loadObjFile(const char path[], mesh& m)
{
	FILE* fp = fopen(path, "r");
	if (fp == NULL)
	{
		printf("cannot open %s\n", path);
		exit(1);
	}
	vector<vec3d> verts;
	char line[128];
	while (fgets(line, 128, fp) != NULL)
	{
		//	printf("%s", line);
		char junk;
		if (line[0] == 'v')
		{
			vec3d v;
			sscanf_s(line, "v %lf %lf %lf", &v.x, &v.y, &v.z);
			//	printf("v %lf %lf %lf\n", v.x, v.y, v.z);
			verts.push_back(v);
		}
		else if (line[0] == 'f')
		{
			int f[3];
			sscanf_s(line, "f %d %d %d", &f[0], &f[1], &f[2]);
			//	printf("f %d %d %d\n", f[0], f[1], f[2]);
			m.tris.push_back({ verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1] });
		}
	}

	fclose(fp);
}
void drawTriangle(triangle tri, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	const int n = 3;
	Sint16 vx[n] = { tri.p[0].x, tri.p[1].x, tri.p[2].x };
	Sint16 vy[n] = { tri.p[0].y, tri.p[1].y, tri.p[2].y };
	polygonRGBA(renderer, vx, vy, n, r, g, b, a);
}
void drawFilledTriangle(triangle tri, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	const int n = 3;
	Sint16 vx[n] = { tri.p[0].x, tri.p[1].x, tri.p[2].x };
	Sint16 vy[n] = { tri.p[0].y, tri.p[1].y, tri.p[2].y };
	filledPolygonRGBA(renderer, vx, vy, n, r, g, b, a);
}

mesh meshCube;
mesh meshWall;
double fNear = 0.1f;
double fFar = 1000.0f;
double fFov = 90.0f;
double fAspectRatio = (double)HEIGHT / WIDTH;
double fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);

vec3d vLookDir = { 0,0,1 };
vec3d vCamera = { 0.5,0,-1.5 };
//vec3d vCamera = { 162,0,338 };
int fYaw = 0;
vec3d vForward;
vec3d light_direction;

void draw3DWall()
{
	fNear = 0.1f;
	fFar = 1000.0f;
	fFov = 90.0f;
	fAspectRatio = (double)HEIGHT / WIDTH;
	fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);

	vForward = Vector_Mul(vLookDir, 1);
	vec3d vUp = { 0,1,0 };
	vec3d vTarget = { 0,0,1 };
	mat4x4 matCameraRot = Matrix_MakeRotationY(fYaw / 180.0 * 3.14159);
	vLookDir = Matrix_MultiplyVector(matCameraRot, vTarget);
	vTarget = Vector_Add(vCamera, vLookDir);
	mat4x4 matCamera = Matrix_PointAt(vCamera, vTarget, vUp);
	mat4x4 matView = Matrix_QuickInverse(matCamera);

	// Store triagles for rastering later
	vector<triangle> vecTrianglesToRaster;
	vecTrianglesToRaster.clear();

	// Draw Triangles
	for (auto tri : meshWall.tris)
	{
		triangle triRotatedX, triRotatedY, triRotatedZ;
		rotateX(tri, triRotatedX, 0);
		rotateY(triRotatedX, triRotatedY, 0);
		rotateZ(triRotatedY, triRotatedZ, 0);


		// Offset into the screen
		triangle triTransformed;
		offset(triRotatedZ, triTransformed, 0);


		// Calculate triangle Normal
		vec3d normal, line1, line2;
		line1 = Vector_Sub(triTransformed.p[1], triTransformed.p[0]);
		line2 = Vector_Sub(triTransformed.p[2], triTransformed.p[0]);
		normal = Vector_CrossProduct(line1, line2);
		normal = Vector_Normalise(normal);


		vec3d vCameraRay = Vector_Sub(triTransformed.p[0], vCamera);

		if (Vector_DotProduct(normal, vCameraRay) < 0.0)
		{
			light_direction = { 1,-2,-3 };
			light_direction = Vector_Normalise(light_direction);

			float dp = max(0.1f, Vector_DotProduct(light_direction, normal));


			// Convert World Space --> View Space
			triangle triViewed;
			view_space(triTransformed, triViewed, matView);


			// Clip Viewed Triangle against near plane, this could form two additional triangles. 
			triangle clipped[2];
			int nClippedTriangles = Triangle_ClipAgainstPlane({ 0,0,0.1 }, { 0,0,1 }, triViewed, clipped[0], clipped[1]);
			for (int n = 0; n < nClippedTriangles; n++)
			{
				// Project triangles from 3D --> 2D
				triangle triProjected;
				project(clipped[n], triProjected, fFov, fAspectRatio, fNear, fFar);


				// Scale into view
				triProjected.p[0] = Vector_Div(triProjected.p[0], triProjected.p[0].w);
				triProjected.p[1] = Vector_Div(triProjected.p[1], triProjected.p[1].w);
				triProjected.p[2] = Vector_Div(triProjected.p[2], triProjected.p[2].w);


				// Offset verts into visible normalised space
				vec3d vOffsetView = { 1,1,0 };
				triProjected.p[0] = Vector_Add(triProjected.p[0], vOffsetView);
				triProjected.p[1] = Vector_Add(triProjected.p[1], vOffsetView);
				triProjected.p[2] = Vector_Add(triProjected.p[2], vOffsetView);
				triProjected.p[0].x *= 0.5 * (double)WIDTH;
				triProjected.p[0].y *= 0.5 * (double)HEIGHT;
				triProjected.p[1].x *= 0.5 * (double)WIDTH;
				triProjected.p[1].y *= 0.5 * (double)HEIGHT;
				triProjected.p[2].x *= 0.5 * (double)WIDTH;
				triProjected.p[2].y *= 0.5 * (double)HEIGHT;

				triProjected.light = 255 * dp;

				vecTrianglesToRaster.push_back(triProjected);
			}
		}
	}
	std::sort(vecTrianglesToRaster.begin(), vecTrianglesToRaster.end(), [](triangle& t1, triangle& t2)
		{
			float z1 = (t1.p[0].z + t1.p[1].z + t1.p[2].z) / 3.0f;
			float z2 = (t2.p[0].z + t2.p[1].z + t2.p[2].z) / 3.0f;
			return z1 > z2;
		});
	for (auto& triToRaster : vecTrianglesToRaster)
	{
		triangle clipped[2];
		list<triangle> listTriangles;

		// Add initial triangle
		listTriangles.push_back(triToRaster);
		int nNewTriangles = 1;

		for (int p = 0; p < 4; p++)
		{
			int nTrisToAdd = 0;
			while (nNewTriangles > 0)
			{
				// Take triangle from front of queue
				triangle test = listTriangles.front();
				listTriangles.pop_front();
				nNewTriangles--;

				switch (p)
				{
				case 0:
					nTrisToAdd = Triangle_ClipAgainstPlane({ 0,0,0 }, { 0,1,0 }, test, clipped[0], clipped[1]);
					break;
				case 1:
					nTrisToAdd = Triangle_ClipAgainstPlane({ 0, (double)HEIGHT - 1, 0 }, { 0,-1,0 }, test, clipped[0], clipped[1]);
					break;
				case 2:
					nTrisToAdd = Triangle_ClipAgainstPlane({ 0,0,0 }, { 1,0,0 }, test, clipped[0], clipped[1]);
					break;
				case 3:
					nTrisToAdd = Triangle_ClipAgainstPlane({ (double)WIDTH - 1, 0,0 }, { -1,0,0 }, test, clipped[0], clipped[1]);
					break;
				}

				for (int w = 0; w < nTrisToAdd; w++)
					listTriangles.push_back(clipped[w]);
			}
			nNewTriangles = listTriangles.size();
		}
		for (auto& triProjected : listTriangles)
		{
			//  printf("%lf %lf %lf %lf %lf %lf\n", triProjected.p[0].x, triProjected.p[1].x, triProjected.p[2].x, triProjected.p[0].y, triProjected.p[1].y, triProjected.p[2].y);
			//  drawTriangle(triProjected, 255, 0, 0, 255);
			drawFilledTriangle(triProjected, triProjected.light, triProjected.light, 240, 255);
		}
	}
	//SDL_RenderPresent(renderer);
}

mesh meshGhost;
vec3d vLookDir2 = { 0,0,1 };
vec3d vForward2;
void draw3DGhost(vec3d vCamera2, int type)
{
	vForward2 = Vector_Mul(vLookDir2, 20);
	vec3d vUp2 = { 0,1,0 };
	vec3d vTarget2 = { 0,0,1 };
	mat4x4 matCameraRot2 = Matrix_MakeRotationY(fYaw / 180.0 * 3.14159);
	vLookDir2 = Matrix_MultiplyVector(matCameraRot2, vTarget2);
	vLookDir2 = { 0,0,1 };
	vTarget2 = Vector_Add(vCamera2, vLookDir2);
	mat4x4 matCamera2 = Matrix_PointAt(vCamera2, vTarget2, vUp2);
	mat4x4 matView2 = Matrix_QuickInverse(matCamera2);

	// Store triagles for rastering later
	vector<triangle> vecTrianglesToRaster;
	vecTrianglesToRaster.clear();


	// Draw Triangles
	for (auto tri : meshGhost.tris)
	{
		triangle triRotatedX, triRotatedY, triRotatedZ;
		rotateX(tri, triRotatedX, 0);
		rotateY(triRotatedX, triRotatedY, 0);
		rotateZ(triRotatedY, triRotatedZ, 0);


		// Offset into the screen
		triangle triTransformed;
		offset(triRotatedZ, triTransformed, 0);


		// Calculate triangle Normal
		vec3d normal, line1, line2;
		line1 = Vector_Sub(triTransformed.p[1], triTransformed.p[0]);
		line2 = Vector_Sub(triTransformed.p[2], triTransformed.p[0]);
		normal = Vector_CrossProduct(line1, line2);
		normal = Vector_Normalise(normal);


		vec3d vCameraRay = Vector_Sub(triTransformed.p[0], vCamera);

		if (Vector_DotProduct(normal, vCameraRay) < 0.0)
		{
			vec3d light_direction = { 0,0,-1 };
			light_direction = Vector_Normalise(light_direction);

			float dp = max(0.1f, Vector_DotProduct(light_direction, normal));


			// Convert World Space --> View Space
			triangle triViewed;
			view_space(triTransformed, triViewed, matView2);


			// Clip Viewed Triangle against near plane, this could form two additional triangles. 
			triangle clipped[2];
			int nClippedTriangles = Triangle_ClipAgainstPlane({ 0,0,0.1 }, { 0,0,1 }, triViewed, clipped[0], clipped[1]);
			for (int n = 0; n < nClippedTriangles; n++)
			{
				// Project triangles from 3D --> 2D
				triangle triProjected;
				project(clipped[n], triProjected, fFov, fAspectRatio, fNear, fFar);


				// Scale into view
				triProjected.p[0] = Vector_Div(triProjected.p[0], triProjected.p[0].w);
				triProjected.p[1] = Vector_Div(triProjected.p[1], triProjected.p[1].w);
				triProjected.p[2] = Vector_Div(triProjected.p[2], triProjected.p[2].w);


				// Offset verts into visible normalised space
				vec3d vOffsetView = { 1,1,0 };
				triProjected.p[0] = Vector_Add(triProjected.p[0], vOffsetView);
				triProjected.p[1] = Vector_Add(triProjected.p[1], vOffsetView);
				triProjected.p[2] = Vector_Add(triProjected.p[2], vOffsetView);
				triProjected.p[0].x *= 0.5 * (double)WIDTH;
				triProjected.p[0].y *= 0.5 * (double)HEIGHT;
				triProjected.p[1].x *= 0.5 * (double)WIDTH;
				triProjected.p[1].y *= 0.5 * (double)HEIGHT;
				triProjected.p[2].x *= 0.5 * (double)WIDTH;
				triProjected.p[2].y *= 0.5 * (double)HEIGHT;

				triProjected.light = 255 * dp;

				vecTrianglesToRaster.push_back(triProjected);
			}
		}
	}
	std::sort(vecTrianglesToRaster.begin(), vecTrianglesToRaster.end(), [](triangle& t1, triangle& t2)
		{
			float z1 = (t1.p[0].z + t1.p[1].z + t1.p[2].z) / 3.0;
			float z2 = (t2.p[0].z + t2.p[1].z + t2.p[2].z) / 3.0;
			return z1 > z2;
		});
	for (auto& triToRaster : vecTrianglesToRaster)
	{
		triangle clipped[2];
		list<triangle> listTriangles;
		listTriangles.clear();

		// Add initial triangle
		listTriangles.push_back(triToRaster);
		int nNewTriangles = 1;

		for (int p = 0; p < 4; p++)
		{
			int nTrisToAdd = 0;
			while (nNewTriangles > 0)
			{
				// Take triangle from front of queue
				triangle test = listTriangles.front();
				listTriangles.pop_front();
				nNewTriangles--;

				switch (p)
				{
				case 0:
					nTrisToAdd = Triangle_ClipAgainstPlane({ 0,0,0 }, { 0,1,0 }, test, clipped[0], clipped[1]);
					break;
				case 1:
					nTrisToAdd = Triangle_ClipAgainstPlane({ 0, (double)HEIGHT - 1, 0 }, { 0,-1,0 }, test, clipped[0], clipped[1]);
					break;
				case 2:
					nTrisToAdd = Triangle_ClipAgainstPlane({ 0,0,0 }, { 1,0,0 }, test, clipped[0], clipped[1]);
					break;
				case 3:
					nTrisToAdd = Triangle_ClipAgainstPlane({ (double)WIDTH - 1, 0,0 }, { -1,0,0 }, test, clipped[0], clipped[1]);
					break;
				}

				for (int w = 0; w < nTrisToAdd; w++)
					listTriangles.push_back(clipped[w]);
			}
			nNewTriangles = listTriangles.size();
		}
		for (auto& tri : listTriangles)
		{
			//  drawTriangle(tri, 255, 0, 0, 255);
			switch (type)
			{
			case 0:
				drawFilledTriangle(tri, 240, tri.light, tri.light, 255);
				break;
			case 1:
				drawFilledTriangle(tri, 240, tri.light, 240, 255);
				break;
			case 2:
				drawFilledTriangle(tri, tri.light, 240, 240, 255);
				break;
			case 3:
				drawFilledTriangle(tri, 240, 100, tri.light, 255);
				break;
			case 4:
				drawFilledTriangle(tri, 0, 0, 200, 255);
				break;
			}
		}
	}
	//SDL_RenderPresent(renderer);
}

mesh meshDot;
mesh meshBigdot;
mesh meshTmp;
vec3d vLookDir3 = { 0,0,1 };
vec3d vForward3;
vec3d vCamera3 = { 20,-100,-100 };
void draw3DDot(bool bigdot)
{
	if (bigdot)
		meshTmp = meshBigdot;
	else
		meshTmp = meshDot;

	vForward3 = Vector_Mul(vLookDir3, 20);
	vec3d vUp3 = { 0,1,0 };
	vec3d vTarget3 = { 0,0,1 };
	mat4x4 matCameraRot3 = Matrix_MakeRotationY(fYaw / 180.0 * 3.14159);
	vLookDir3 = Matrix_MultiplyVector(matCameraRot3, vTarget3);
	vLookDir3 = { 0,0,1 };
	vTarget3 = Vector_Add(vCamera3, vLookDir3);
	mat4x4 matCamera3 = Matrix_PointAt(vCamera3, vTarget3, vUp3);
	mat4x4 matView3 = Matrix_QuickInverse(matCamera3);

	vector<triangle> vecTrianglesToRaster;
	vecTrianglesToRaster.clear();


	// Draw Triangles
	for (auto tri : meshTmp.tris)
	{
		triangle triRotatedX, triRotatedY, triRotatedZ;
		rotateX(tri, triRotatedX, 0);
		rotateY(triRotatedX, triRotatedY, 0);
		rotateZ(triRotatedY, triRotatedZ, 0);


		// Offset into the screen
		triangle triTransformed;
		offset(triRotatedZ, triTransformed, 0);


		// Calculate triangle Normal
		vec3d normal, line1, line2;
		line1 = Vector_Sub(triTransformed.p[1], triTransformed.p[0]);
		line2 = Vector_Sub(triTransformed.p[2], triTransformed.p[0]);
		normal = Vector_CrossProduct(line1, line2);
		normal = Vector_Normalise(normal);


		vec3d vCameraRay = Vector_Sub(triTransformed.p[0], vCamera);

		if (Vector_DotProduct(normal, vCameraRay) < 0.0)
		{
			vec3d light_direction = { 0,0,-1 };
			light_direction = Vector_Normalise(light_direction);

			float dp = max(0.1f, Vector_DotProduct(light_direction, normal));


			// Convert World Space --> View Space
			triangle triViewed;
			view_space(triTransformed, triViewed, matView3);


			// Clip Viewed Triangle against near plane, this could form two additional triangles. 
			triangle clipped[2];
			int nClippedTriangles = Triangle_ClipAgainstPlane({ 0,0,0.1 }, { 0,0,1 }, triViewed, clipped[0], clipped[1]);
			for (int n = 0; n < nClippedTriangles; n++)
			{
				// Project triangles from 3D --> 2D
				triangle triProjected;
				project(clipped[n], triProjected, fFov, fAspectRatio, fNear, fFar);


				// Scale into view
				triProjected.p[0] = Vector_Div(triProjected.p[0], triProjected.p[0].w);
				triProjected.p[1] = Vector_Div(triProjected.p[1], triProjected.p[1].w);
				triProjected.p[2] = Vector_Div(triProjected.p[2], triProjected.p[2].w);


				// Offset verts into visible normalised space
				vec3d vOffsetView = { 1,1,0 };
				triProjected.p[0] = Vector_Add(triProjected.p[0], vOffsetView);
				triProjected.p[1] = Vector_Add(triProjected.p[1], vOffsetView);
				triProjected.p[2] = Vector_Add(triProjected.p[2], vOffsetView);
				triProjected.p[0].x *= 0.5 * (double)WIDTH;
				triProjected.p[0].y *= 0.5 * (double)HEIGHT;
				triProjected.p[1].x *= 0.5 * (double)WIDTH;
				triProjected.p[1].y *= 0.5 * (double)HEIGHT;
				triProjected.p[2].x *= 0.5 * (double)WIDTH;
				triProjected.p[2].y *= 0.5 * (double)HEIGHT;

				triProjected.light = 255 * dp;

				vecTrianglesToRaster.push_back(triProjected);
			}
		}
	}
	std::sort(vecTrianglesToRaster.begin(), vecTrianglesToRaster.end(), [](triangle& t1, triangle& t2)
		{
			float z1 = (t1.p[0].z + t1.p[1].z + t1.p[2].z) / 3.0;
			float z2 = (t2.p[0].z + t2.p[1].z + t2.p[2].z) / 3.0;
			return z1 > z2;
		});
	for (auto& triToRaster : vecTrianglesToRaster)
	{
		triangle clipped[2];
		list<triangle> listTriangles;
		listTriangles.clear();

		listTriangles.push_back(triToRaster);
		int nNewTriangles = 1;

		for (int p = 0; p < 4; p++)
		{
			int nTrisToAdd = 0;
			while (nNewTriangles > 0)
			{
				triangle test = listTriangles.front();
				listTriangles.pop_front();
				nNewTriangles--;

				switch (p)
				{
				case 0:
					nTrisToAdd = Triangle_ClipAgainstPlane({ 0,0,0 }, { 0,1,0 }, test, clipped[0], clipped[1]);
					break;
				case 1:
					nTrisToAdd = Triangle_ClipAgainstPlane({ 0, (double)HEIGHT - 1, 0 }, { 0,-1,0 }, test, clipped[0], clipped[1]);
					break;
				case 2:
					nTrisToAdd = Triangle_ClipAgainstPlane({ 0,0,0 }, { 1,0,0 }, test, clipped[0], clipped[1]);
					break;
				case 3:
					nTrisToAdd = Triangle_ClipAgainstPlane({ (double)WIDTH - 1, 0,0 }, { -1,0,0 }, test, clipped[0], clipped[1]);
					break;
				}

				for (int w = 0; w < nTrisToAdd; w++)
					listTriangles.push_back(clipped[w]);
			}
			nNewTriangles = listTriangles.size();
		}
		for (auto& tri : listTriangles)
		{
			//  drawTriangle(tri, 255, 0, 0, 255);
			drawFilledTriangle(tri, 255, 255, 255, 255);
		}
	}
}

void draw3D()
{
	hint = loadTextTexture(" ", "../fonts/TaipeiSansTCBeta-Regular.ttf", 24, 255, 0, 0, SHADED, 0, 0, 0);
//	forwardFlag = true;
	stdwall(map1, map2);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(renderer);
	char score_str[100] = "score: \0";
	char tmp_str[100] = "\0";
	sprintf_s(tmp_str, "%d", score);
	strcat(score_str, tmp_str);
	score_text = loadTextTexture(score_str, "../fonts/TaipeiSansTCBeta-Regular.ttf", 14, 255, 255, 0, SHADED, 0, 0, 0);

	int timer = SDL_GetTicks() - time_init - time_total_paused;
	if (period_init)
	{
		game_initialize();
		hint_alp = 255;
		hint = loadTextTexture("READY?", "../fonts/TaipeiSansTCBeta-Regular.ttf", 14, 255, 0, 0, SHADED, 0, 0, 0);
		if (timer > 4000) {
			period_init = false;
		}
		pacc = { 15 * l_grid + l_grid / 2, 23 * l_grid + l_grid / 2 };
		ghostc[0] = { 15 * l_grid, (10 + y_down) * l_grid + l_grid / 2 };
		ghostc[1] = { 13 * l_grid + l_grid / 2, (13 + y_down) * l_grid + l_grid / 2 };
		ghostc[2] = { 15 * l_grid + l_grid / 2, (13 + y_down) * l_grid + l_grid / 2 };
		ghostc[3] = { 17 * l_grid + l_grid / 2, (13 + y_down) * l_grid + l_grid / 2 };

		vCamera = { (pacc.x + 9) * (-1.0 / 18) + 185.0 / 6 ,-2.0,(pacc.y + 9) * 1.0 / 18 - 5.0 / 6 };
		pacIndex[0] = 6;
		fYaw = 180;
		dir = 1;
	}
	else
	{
		if (Mix_PlayingMusic() == 0 && !period_die && !period_eatghost) {
			Mix_PlayMusic(woooo, -1);
			cout << "play_woooo\n";
		}

		hint_alp = 0;
		int dot = 0;
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				if (map1[i][j] == 1)
					dot++;
		if (dot == 0 && !passFlag)
		{
			passFlag = true;
			Mix_PlayMusic(beginning, 0);
			cout << "play_beginning\n";
			time_pass = SDL_GetTicks();
			ghost_alp = 0;
			pac_alp = 0;
			die_alp = 0;
		}
		if (passFlag && SDL_GetTicks() - time_pass > 1500)
		{
			map1 = map;
			period_init = true;
			time_init = SDL_GetTicks();
			pause_duration = 0;
			time_total_paused = 0;
			passFlag = false;
		}
		if (!period_die && !period_eatghost && live > 0)
		{
			gmove(0, 10);
			gmove(1, 0);
			gmove(2, 0);
			gmove(3, 0);

			pacmove();

			if ((map1[pacp.y][pacp.x] == 1))
			{
				eeat = true;
				map1[pacp.y][pacp.x] = 2;
				score += 10;
			}
			if ((map1[pacp.y][pacp.x] == 3))
			{
				Mix_PlayMusic(frighten, -1);
				cout << "play_frighten\n";
				time_frightened = timer;
				period_frightened = true;
				period_frightened_end = false;
				for (int i = 0; i < 4; i++) {
					if (!ghost_isolated[i] && !ghost_eaten[i]) {
						ghost_frightened[i] = true;
					}
				}
				map1[pacp.y][pacp.x] = 2;
				printf("frightened\n");
			}

			for (int i = 0; i < 4; i++) {
				if (dist(pacc, ghostc[i], l_char * l_grid) && !ghost_frightened[i] && !period_die && !ghost_eaten[i])
				{
					printf("dead\n");
					period_die = true;
					period_paceaten = true;
					time_die = timer;
					diec = pacc;
					live--;
					playDeathMusic = true;
				}
			}
		}
		if (period_frightened)
		{
			period_eatghost = false;
			for (int i = 0; i < 4; i++)
			{
				if (ghost_eaten[i] && timer - time_ghost_eaten[i] > 600) {
					ghost_eatening[i] = false;
				}
				if (dist(pacc, ghostc[i], l_char * l_grid) && ghost_frightened && !ghost_eaten[i])
				{
					ghost_eaten[i] = true;
					ghost_eatening[i] = true;
					time_ghost_eaten[i] = timer;
					cnt++;
					score += cnt * 200;
					Mix_PlayChannel(2, eatghost, 0);
					Mix_HaltMusic();
					cout << "haltmusic\n";
				}
				if (ghost_eatening[i]) {
					period_eatghost = true;
				}
			}
			if (timer - time_frightened > 6000) {
				period_frightened_end = true;
			}
			if (timer - time_frightened > 8000) {
				period_eatghost = false;
				period_frightened = false;
				period_frightened_end = false;
				for (int i = 0; i < 4; i++) {
					ghost_frightened[i] = false;
					ghost_eatening[i] = false;
				}
				cnt = 0;
				Mix_HaltMusic();
			}
		}

		if (period_die)
		{
			if (timer - time_die < 500) {
				period_paceaten = true;
				die_alp = 0;
				dieIndex[0] = 0;
			}
			else if (timer - time_die < 1600)
			{
				period_paceaten = false;
				period_dissolve = true;
				pac_alp = 0;
				die_alp = 255;
				ghost_alp = 0;
				if (playDeathMusic)
				{
					Mix_PlayMusic(death, 0);
					cout << "play_death\n";
					playDeathMusic = false;
				}
			}
			else if (timer - time_die < 2000)
			{
				period_dissolve = false;
				period_disappear = true;
				lives_alp[live] = 0;
				pac_alp = 0;
				//pv = { 1,0 };
				die_alp = 0;
				ghost_alp = 0;
			}
			else if (timer - time_die < 4500)
			{
				period_end = true;
				period_disappear = false;
				if (live == 0) {
					hint = loadTextTexture("GAME OVER", "../fonts/TaipeiSansTCBeta-Regular.ttf", 14, 255, 0, 0, SHADED, 0, 0, 0);
					hint_alp = 255;
				}
			}
			else if (timer - time_die > 5500) {
				if (live == 0) {
					if (score > r[4].score)
					{
						status = ENTER_NAME;
						strcpy(inputString, " ");
					}
					else
					{
						status = MENU;
						Mix_HaltMusic();
						time_animation = SDL_GetTicks();
					}
					period_die = false;
				}
				else {
					period_init = true;
					time_init = SDL_GetTicks();
					Mix_PlayMusic(beginning, 0);
					cout << "play_beginning\n";
					pause_duration = 0;
					time_total_paused = 0;
				}
			}
		}
		vCamera = { (pacc.x + 9) * (-1.0 / 18) + 185.0 / 6 , -0.5 , (pacc.y + 9) * 1.0 / 18 - 5.0 / 6 };
	}
	SDL_Rect r[2] = { {580, 20, 50, 50}, {580, 80, 50, 50} };
	if (mouseX > r[0].x && mouseX < r[0].x + r[0].w && mouseY > r[0].y && mouseY < r[0].y + r[0].h)
		if (mouseState == LB_SC || mouseState == LB_DC)
		{
			pauseFlag = true;
			pausedisplay = false;
			Mix_PauseMusic();
			Mix_Pause(-1);
			time_pause = SDL_GetTicks();
		}
	if (mouseX > r[1].x && mouseX < r[1].x + r[1].w && mouseY > r[1].y && mouseY < r[1].y + r[1].h)
		if (mouseState == LB_SC || mouseState == LB_DC)
		{
			pauseFlag = true;
			pausedisplay = true;
			Mix_PauseMusic();
			Mix_Pause(-1);
			time_pause = SDL_GetTicks();
		}
	for (int i = 0; i < 2; i++) {
			imgRender(renderer, images[i], r[i].x, r[i].y, 0, NULL, NULL, NULL, no, 255, 1, 1);
	}


	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			imgRender(renderer, wall, padding + j * l_grid / 2, padding + i * l_grid / 2, map2[i][j], NULL, NULL, NULL, no, 255, 0.5, 0.5);
	imgRender(renderer, pac, (pacc.x - padding) / 2 + padding, (pacc.y - padding) / 2 + padding, pacIndex[0], NULL, NULL, NULL, no, pac_alp, 0.5, 0.5);
	imgRender(renderer, die, (diec.x - padding) / 2 + padding, (diec.y - padding) / 2 + padding, dieIndex[0], NULL, NULL, NULL, no, die_alp, 0.5, 0.5);
	for (int i = 0; i < 4; i++)
		imgRender(renderer, ghost[i], (ghostc[i].x - padding) / 2 + padding, (ghostc[i].y - padding) / 2 + padding, ghostIndex[i], NULL, NULL, NULL, no, ghost_alp, 0.5, 0.5);

	for (int i = 0; i < 3; i++)
		imgRender(renderer, lives[i], padding + (l_char * i + l_grid / 2) / 2, padding + (l_grid * M + l_grid / 2) / 2, 1, NULL, NULL, NULL, no, lives_alp[i], 0.5, 0.5);
	textRender(renderer, score_text, padding + l_char * 8, padding + (l_grid * M + l_grid / 2) / 2, NULL, NULL, NULL, no, 255);
	textRender(renderer, hint, padding + 15 * l_grid / 2 - hint.width / 2, padding + 17 * l_grid / 2 + l_grid / 4 - hint.height / 2, NULL, NULL, NULL, no, hint_alp);


	bool see[4] = { false,false,false,false };
	double d[4] = { 0,0,0,0 };
	vec3d vGhostCamera[4] = { {0,0,0},{0,0,0},{0,0,0},{0,0,0} };
	switch (pv.x + 2 * pv.y)
	{
	case 1:
		if (fYaw == 90)
			fYaw = 90;
		else if (fYaw > 90 && fYaw < 270)
			fYaw = (fYaw + 350) % 360;
		else
			fYaw = (fYaw + 10) % 360;

		vGhostCamera[0].x = -20;
		vGhostCamera[1].x = -20;
		vGhostCamera[2].x = -20;
		vGhostCamera[3].x = -20;
		for (int i = 0; i < 4; i++)
		{
			if (abs(pacc.y - ghostc[i].y) < 5 && pacp.x < ghostp[i].x && fYaw % 90 == 0)
			{
				see[i] = true;
				d[i] = ghostc[i].x - pacc.x;
				for (int j = pacp.x + 1; j < ghostp[i].x; j++)
					if (map1[pacp.y][j] == 0)
					{
						see[i] = false;
						break;
					}
			}
		}
		break;
	case -1:
		if (fYaw == 270)
			fYaw = 270;
		else if (fYaw > 90 && fYaw < 270)
			fYaw = (fYaw + 10) % 360;
		else
			fYaw = (fYaw + 350) % 360;

		vGhostCamera[0].x = 20;
		vGhostCamera[1].x = 20;
		vGhostCamera[2].x = 20;
		vGhostCamera[3].x = 20;
		for (int i = 0; i < 4; i++)
		{
			if (abs(pacc.y - ghostc[i].y) < 5 && pacp.x > ghostp[i].x && fYaw % 90 == 0)
			{
				see[i] = true;
				d[i] = pacc.x - ghostc[i].x;
				for (int j = ghostp[i].x + 1; j < pacp.x; j++)
					if (map1[pacp.y][j] == 0)
					{
						see[i] = false;
						break;
					}
			}
		}
		break;
	case -2:
		if (fYaw == 180)
			fYaw = 180;
		else if (fYaw > 0 && fYaw < 180)
			fYaw = (fYaw + 10) % 360;
		else
			fYaw = (fYaw + 350) % 360;

		vGhostCamera[0].x = -20;
		vGhostCamera[1].x = -20;
		vGhostCamera[2].x = -20;
		vGhostCamera[3].x = -20;
		for (int i = 0; i < 4; i++)
		{
			if (abs(pacc.x - ghostc[i].x) < 5 && pacp.y > ghostp[i].y && fYaw % 90 == 0)
			{
				see[i] = true;
				d[i] = pacc.y - ghostc[i].y;
				for (int j = ghostp[i].y + 1; j < pacp.y; j++)
					if (map1[j][pacp.x] == 0)
					{
						see[i] = false;
						break;
					}
			}
		}
		break;
	case 2:
		if (fYaw == 0)
			fYaw = 0;
		else if (fYaw > 0 && fYaw < 180)
			fYaw = (fYaw + 350) % 360;
		else
			fYaw = (fYaw + 10) % 360;

		vGhostCamera[0].x = 20;
		vGhostCamera[1].x = 20;
		vGhostCamera[2].x = 20;
		vGhostCamera[3].x = 20;
		for (int i = 0; i < 4; i++)
		{
			if (abs(pacc.x - ghostc[i].x) < 5 && pacp.y < ghostp[i].y && fYaw % 90 == 0)
			{
				see[i] = true;
				d[i] = ghostc[i].y - pacc.y;
				for (int j = pacp.y + 1; j < ghostp[i].y; j++)
					if (map1[j][pacp.x] == 0)
					{
						see[i] = false;
						break;
					}
			}
		}
		break;
	}
	draw3DWall();


	vLookDir2 = { 0,0,-1 };
	for (int i = 0; i < 4; i++)
	{
		vGhostCamera[i].y = -100;
		vGhostCamera[i].z = -100 * d[i] / 18.0;
		if (see[i])
			draw3DGhost(vGhostCamera[i], ghost_frightened[i] ? 4 : i);
	}


	vLookDir3 = { 0,0,-1 };
	switch (pv.x + 2 * pv.y)
	{
	case 1:
		if (fYaw == 90)
		{
			for (int i = 1; i < 12 && pacp.x + i < N - 1 && map1[pacp.y][pacp.x + i] != 0; i++)
			{
				vCamera3 = { -20,-100,-100 * ((padding + (pacp.x + i - 1) * 18 + 9) - pacc.x) / 18.0 };
				if (map1[pacp.y][pacp.x + i] == 1)
					draw3DDot(false);
				else if (map1[pacp.y][pacp.x + i] == 3 && map2[pacp.y][pacp.x + i] == 8)
					draw3DDot(true);
			}
		}
		break;
	case -1:
		if (fYaw == 270)
		{
			for (int i = 1; i < 12 && pacp.x - i > 0 && map1[pacp.y][pacp.x - i] != 0; i++)
			{
				vCamera3 = { 20,-100,-100 * (pacc.x - (padding + (pacp.x - i - 1) * 18 + 9)) / 18.0 };
				if (map1[pacp.y][pacp.x - i] == 1)
					draw3DDot(false);
				else if (map1[pacp.y][pacp.x - i] == 3 && map2[pacp.y][pacp.x - i] == 8)
					draw3DDot(true);
			}
		}
		break;
	case -2:
		if (fYaw == 180)
		{
			for (int i = 1; i < 12 && pacp.y - i > 0 && map1[pacp.y - i][pacp.x] != 0; i++)
			{
				vCamera3 = { -20,-100,-100 * (pacc.y - (padding + (pacp.y - i - 1) * 18 + 9)) / 18.0 };
				if (map1[pacp.y - i][pacp.x] == 1)
					draw3DDot(false);
				else if (map1[pacp.y - i][pacp.x] == 3 && map2[pacp.y - i][pacp.x] == 8)
					draw3DDot(true);
			}
		}
		break;
	case 2:
		if (fYaw == 0)
		{
			for (int i = 1; i < 12 && pacp.y + i < M - 1 && map1[pacp.y + i][pacp.x] != 0; i++)
			{
				vCamera3 = { 20,-100,-100 * ((padding + (pacp.y + i - 1) * 18 + 9) - pacc.y) / 18.0 };
				if (map1[pacp.y + i][pacp.x] == 1)
					draw3DDot(false);
				else if (map1[pacp.y + i][pacp.x] == 3 && map2[pacp.y + i][pacp.x] == 8)
					draw3DDot(true);
			}
		}
		break;
	}
	SDL_RenderPresent(renderer);
}
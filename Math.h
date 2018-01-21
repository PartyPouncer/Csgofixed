#pragma once

#define square( x ) ( x * x )

namespace M
{
	extern inline void SinCos(float radians, float *sine, float *cosine);
	extern void AngleVectors(const Vector &angles, Vector *forward);
	extern void VectorAngles(const Vector& forward, QAngle &angles);
	extern void AngleVectors(const QAngle& angles, Vector *forward);
	extern void AngleVectors(const QAngle &angles, Vector *forward, Vector *right, Vector *up);
	extern void AngleVectors2D(Vector& vecAngles, Vector& vecForward);
	extern void VectorAngles2D(Vector& vecForward, Vector& vecAngles);
	extern void NormalizeAngles2D(Vector& vecAngles);
	extern QAngle CalcAngle(Vector v1, Vector v2);
	extern float GetFov(const QAngle& viewAngle, const QAngle& aimAngle, float distance);
	extern float VectorDistance(Vector v1, Vector v2);
	/*extern void VectorTransform(Vector& in1, matrix3x4a_t& in2, Vector &out);*/
	void VectorTransform(Vector & in1, matrix3x4a_t & in2, Vector & out);
	extern float GetDelta(float hspeed, float maxspeed, float airaccelerate);
	extern Vector ExtrapolateTick(Vector p0, Vector v0);
	extern inline float RandFloat(float M, float N);

	// sperg cried about the previous method, 
	//here's not only a faster one but inaccurate as well to trigger more people

	inline float FastSqrt_x(float x)
	{
		__m128 root = _mm_sqrt_ss(_mm_load_ss(&x));
		return *(reinterpret_cast<float *>(&root));
	}
}
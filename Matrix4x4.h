#pragma once
#include <memory>
#include "Vector3D.h"
#include "Vector4D.h"

class Matrix4x4
{

public:
    Matrix4x4(){
    }

    ~Matrix4x4(){}

    void setIdentity(){
        ::memset(m_mat, 0, sizeof(float) * 16);
        m_mat[0][0] = 1;
        m_mat[1][1] = 1;
        m_mat[2][2] = 1;
        m_mat[3][3] = 1;
    }

    void setTranslation(Vector3D translation){
        setIdentity();
        m_mat[3][0] = translation.getX();
        m_mat[3][1] = translation.getY();
        m_mat[3][2] = translation.getZ();
    }
    
    void setScale(Vector3D scale){
        setIdentity();
        m_mat[0][0] = scale.getX();
        m_mat[1][1] = scale.getY();
        m_mat[2][2] = scale.getZ();
    }

    void setRotationX(float x){
        setIdentity();
        m_mat[1][1] = cos(x);
        m_mat[1][2] = sin(x);
        m_mat[2][1] = -sin(x);
        m_mat[2][2] = cos(x);
    }
    
    void setRotationY(float y){
        setIdentity();
        m_mat[0][0] = cos(y);
        m_mat[0][2] = -sin(y);
        m_mat[2][0] = sin(y);
        m_mat[2][2] = cos(y);
    }

    void setRotationZ(float z){
        setIdentity();
        m_mat[0][0] = cos(z);
        m_mat[0][1] = sin(z);
        m_mat[1][0] = -sin(z);
        m_mat[1][1] = cos(z);
    }

    Vector3D getZDirection(){
		return Vector3D(m_mat[2][0], m_mat[2][1], m_mat[2][2]);
	}

    Vector3D getYDirection()
    {
        return Vector3D(m_mat[1][0], m_mat[1][1], m_mat[1][2]);
    }

	Vector3D getXDirection(){
		return Vector3D(m_mat[0][0], m_mat[0][1], m_mat[0][2]);
	}
    
	Vector3D getTranslation(){
		return Vector3D(m_mat[3][0], m_mat[3][1], m_mat[3][2]);
	}

    float getDeterminant()
	{
		Vector4D minor, v1, v2, v3;
		float det;

		v1 = Vector4D(this->m_mat[0][0], this->m_mat[1][0], this->m_mat[2][0], this->m_mat[3][0]);
		v2 = Vector4D(this->m_mat[0][1], this->m_mat[1][1], this->m_mat[2][1], this->m_mat[3][1]);
		v3 = Vector4D(this->m_mat[0][2], this->m_mat[1][2], this->m_mat[2][2], this->m_mat[3][2]);


		minor.cross(v1, v2, v3);
		det = -(this->m_mat[0][3] * minor.m_x + this->m_mat[1][3] * minor.m_y + this->m_mat[2][3] * minor.m_z +
			this->m_mat[3][3] * minor.m_w);
		return det;
	}

	void getInverse()
	{
		int a, i, j;
		Matrix4x4 out;
		Vector4D v, vec[3];
		float det = 0.0f;

		det = this->getDeterminant();
		if (!det) return;
		for (i = 0; i<4; i++)
		{
			for (j = 0; j<4; j++)
			{
				if (j != i)
				{
					a = j;
					if (j > i) a = a - 1;
					vec[a].m_x = (this->m_mat[j][0]);
					vec[a].m_y = (this->m_mat[j][1]);
					vec[a].m_z = (this->m_mat[j][2]);
					vec[a].m_w = (this->m_mat[j][3]);
				}
			}
			v.cross(vec[0], vec[1], vec[2]);

			out.m_mat[0][i] = pow(-1.0f, i) * v.m_x / det;
			out.m_mat[1][i] = pow(-1.0f, i) * v.m_y / det;
			out.m_mat[2][i] = pow(-1.0f, i) * v.m_z / det;
			out.m_mat[3][i] = pow(-1.0f, i) * v.m_w / det;
		}

		this->setMatrix(out);
	}

    void operator *=(const Matrix4x4& matrix){

        Matrix4x4 out;

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                out.m_mat[i][j] = 
                m_mat[i][0] * matrix.m_mat[0][j] + m_mat[i][1] * matrix.m_mat[1][j] + 
                m_mat[i][2] * matrix.m_mat[2][j] + m_mat[i][3] * matrix.m_mat[3][j];
            }
        }

        setMatrix(out);
    }

    Matrix4x4 operator * (const Matrix4x4& matrix){
        Matrix4x4 out;

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                out.m_mat[i][j] = 
                m_mat[i][0] * matrix.m_mat[0][j] + m_mat[i][1] * matrix.m_mat[1][j] + 
                m_mat[i][2] * matrix.m_mat[2][j] + m_mat[i][3] * matrix.m_mat[3][j];
            }
        }

    return out;

    }

	Matrix4x4 multiplyTo(Matrix4x4 matrix)
{
	Matrix4x4 out;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			out.m_mat[i][j] =
				this->m_mat[i][0] * matrix.m_mat[0][j] + this->m_mat[i][1] * matrix.m_mat[1][j] +
				this->m_mat[i][2] * matrix.m_mat[2][j] + this->m_mat[i][3] * matrix.m_mat[3][j];
		}
	}

	return out;
}

    void setMatrix(const Matrix4x4& matrix){
        ::memcpy(m_mat, matrix.m_mat, sizeof(float) * 16);
    }

    void setMatrix(float matrix[4][4]){
        ::memcpy(m_mat, matrix, sizeof(float) * 16);
    }

    float* getMatrix(){
        return *this->m_mat;
    }
    void setOrthoLH(float width, float height, float near_plane, float far_plane){
        setIdentity();
        m_mat[0][0] = 2.0f / width;
        m_mat[1][1] = 2.0f / height;
        m_mat[2][2] = 1.0f / (far_plane - near_plane);
        m_mat[3][2] = -(near_plane / (far_plane - near_plane));
    }

    void setPerspectiveFovLH(float fov, float aspect, float znear, float zfar)
	{
        setIdentity();
		float yscale = 1.0f / tan(fov / 2.0f);
		float xscale = yscale / aspect;
		m_mat[0][0] = xscale;
		m_mat[1][1] = yscale;
		m_mat[2][2] = zfar / (zfar - znear);
		m_mat[2][3] = 1.0f;
		m_mat[3][2] = (-znear*zfar)/ (zfar - znear);
	}

private:

    void matrixInitialize(){
    for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			this->m_mat[i][j] = 0.0f;
		}
	}
    }

    float m_mat[4][4] = {};
};
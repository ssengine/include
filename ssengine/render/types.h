#pragma once

#include <ssengine/ssengine.h>

#ifdef __cplusplus

#include <stack>
#include <initializer_list>

namespace ss{

	struct float4{
		union {
			struct {
				float x, y, z, w;
			};
			float data[4];
		};
		float4(float _x = 0, float _y = 0, float _z = 0, float _w = 1)
			: x(_x), y(_y), z(_z), w(_w){
		}
	};

	struct float3{
		union {
			struct {
				float x, y, z;
			};
			float data[3];
		};

		float3(float _x = 0, float _y = 0, float _z = 0)
			: x(_x), y(_y), z(_z){
		}

		float3(const float4& o)
			: x(o.x/o.w), y(o.y/o.w), z(o.z/o.w) {
		}

		float3 operator/(float d){
			return float3(x / d, y / d, z / d);
		}
	};


	struct float2{
		union{
			struct {
				float x, y;
			};
			float data[2];
		};
		float2(float _x = 0, float _y = 0)
			: x(_x), y(_y){
		}

		float2 operator/(float d){
			return float2(x / d, y / d);
		}
	};

	struct color{
		union {
			float data[4];
			struct {
				float r, g, b, a;
			};
		};
		color(float _r = 0.0f, float _g = 0.0f, float _b = 0.0f, float _a = 1.0f)
			: r(_r), g(_g), b(_b), a(_a)
		{

		}
	
	};

	struct SS_CORE_API matrix{
		union {
			float arr[4][4];
			float data[16];
		};
		static const matrix identity;

		matrix(std::initializer_list<float> l);
		matrix(const matrix& other);
		matrix(float(&arr)[16]);
		//matrix(const matrix& other);


		bool operator ==(const matrix& other) const;
		bool operator !=(const matrix& other) const{
			return !((*this) == other);
		}

		matrix& operator = (const matrix& other);

		float2 transpose(const float2& vec) const;
		float3 transpose(const float3& vec) const;
		float4 transpose(const float4& vec) const;

		void push_translate(float dx, float dy);
		void push_translate(float dx, float dy, float dz);

		void push_scale(float sx, float sy);
		void push_scale(float sx, float sy, float sz);

		void push_rotate2d(float cos, float sin);
		void push_rotate2d(float angel);

		static matrix ortho2d(float width, float height, float x=0, float y=0);
	};

	struct matrix_stack{
        matrix_stack(){
            stack.push(matrix::identity);
        }
		// Copy and push the top of stack
		void push(){
			stack.push(matrix(stack.top()));
		}

		// Push one mat
		void push(const matrix& mat){
			stack.push(mat);
		}

		// Pop a matrix. If stack is empty, push identity matrix after pop.
		void pop(){
			if (stack.size() == 1)
			{
				stack.top() = matrix::identity;
			} else {
				stack.pop();
			}
		}

		// Get stack top.
		matrix& top(){
			return stack.top();
		}
	private:
		std::stack<matrix>   stack;
	};
}
typedef ss::matrix ss_matrix;
typedef ss::matrix_stack ss_matrix_stack;

#else	//__cplusplus
typedef struct ss_matrix ss_matrix;
typedef struct ss_matrix_stack ss_matrix_stack;
#endif  //__cplusplus
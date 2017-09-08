#ifndef UAD_PRIMITIVEBASE_H
#define UAD_PRIMITIVEBASE_H
#include <string>
using namespace std;
class PrimitiveBase {
public:
	virtual void Create() = 0;
	virtual void Create(string filename) = 0;
	virtual void Transform(float *t) = 0;
	virtual void Draw(float *t,float *vp) = 0;
	virtual void Destroy() = 0;
};


#endif
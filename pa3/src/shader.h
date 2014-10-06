#ifndef SHADER_INC
#   define SHADER_INC

#define STRINGIFY(A) #A

const char* GouraudVS = STRINGIFY(
varying vec3 normal;            \n
varying vec4 pos;               \n
varying vec4 rawpos;		\n
varying vec4 color;
void main()                     \n
{                               \n
	normal = gl_NormalMatrix * gl_Normal;         	\n
    	gl_Position = ftransform(); 			\n
    	pos = gl_ModelViewMatrix * gl_Vertex;  		\n

	vec4 Ia= gl_LightSource[0].ambient; 			\n
	vec4 Ka = gl_FrontMaterial.ambient; 			\n
	vec4 Iamb = Ia*Ka; 					\n
	
	vec4 Kd = gl_FrontMaterial.diffuse; 			\n
	vec4 lpos = gl_LightSource[0].position;			\n
	vec3 L = (normalize(lpos-pos)).xyz; 			\n
	vec3 n = normalize(normal); 				\n
	vec4 Id = gl_LightSource[0].diffuse; 			\n
	vec4 Idiff = Kd * max(0.0, dot(n,L)) * Id; 		\n

	vec3 R = reflect(-L,n); 				\n
	R = normalize(R); 					\n
	vec3 V = -pos.xyz; 					\n
	V = normalize(V); 					\n
	vec4 Is = gl_LightSource[0].specular; 			\n
	vec4 Ks = gl_FrontMaterial.specular;			\n
	float shininess = gl_FrontMaterial.shininess; 		\n
	vec4 Ispec; 						\n
	if(shininess != 0.0) 					\n
	{ 							\n
		Ispec = Ks * pow(max(0.0, dot(R, V)), shininess) * Is; \n
	} 							\n
	else 							\n 
	{ 							\n
		Ispec = vec4(0.0, 0.0, 0.0, 0.0);  		\n
	} 							\n

	color = clamp(Iamb, 0.0, 1.0) + clamp(Idiff, 0.0, 1.0) + clamp(Ispec, 0.0, 1.0); 			\n
	
}                               			\n
);

const char* GouraudFS = STRINGIFY(
varying vec3 normal;            \n
varying vec4 pos;		\n
varying vec4 color;
void main()                     \n
{                               \n

	
	
	gl_FragColor = color;			\n

}       						\n                        

);


const char* BlinnPhongVS = STRINGIFY(
varying vec3 normal;            \n
varying vec4 pos;               \n
varying vec4 rawpos;		\n
void main()                     \n
{                               \n
	normal = gl_NormalMatrix * gl_Normal;         					\n
    	gl_Position = ftransform(); 					\n
    	pos = gl_ModelViewMatrix * gl_Vertex;  				\n

}                               					\n
);

const char* BlinnPhongFS = STRINGIFY(
varying vec3 normal;            					\n
varying vec4 pos;							\n
void main()                     					\n
{                               					\n
	vec4 Ia= gl_LightSource[0].ambient; 			\n
	vec4 Ka = gl_FrontMaterial.ambient; 			\n
	vec4 Iamb = Ia*Ka; 					\n
	
	vec4 Kd = gl_FrontMaterial.diffuse; 			\n
	vec4 lpos = gl_LightSource[0].position;			\n
	vec3 L = (normalize(lpos-pos)).xyz; 			\n
	vec3 n = normalize(normal); 				\n
	vec4 Id = gl_LightSource[0].diffuse; 			\n
	vec4 Idiff = Kd * max(0.0, dot(n,L)) * Id; 		\n

	vec3 R = reflect(-L,n); 				\n
	R = normalize(R); 					\n
	vec3 V = -pos.xyz; 					\n
	V = normalize(V); 
	vec3 H = normalize(L+V);					\n
	vec4 Is = gl_LightSource[0].specular; 			\n
	vec4 Ks = gl_FrontMaterial.specular;			\n
	float shininess = gl_FrontMaterial.shininess; 		\n
	vec4 Ispec; 						\n
	if(shininess != 0.0) 					\n
	{ 							\n
		Ispec = Ks * pow(max(0.0, dot(H, n)), shininess) * Is; \n
	} 							\n
	else 							\n 
	{ 							\n
		Ispec = vec4(0.0, 0.0, 0.0, 0.0);  		\n
	} 							\n
	
	gl_FragColor = Iamb + Idiff + Ispec; 			\n

}       						\n                        

);



const char* CheckerboardGVS = STRINGIFY(
varying vec3 normal;            \n
varying vec4 pos;               \n
varying vec4 texCoord; 		\n

void main()                     \n
{                               \n
	normal =gl_NormalMatrix*gl_Normal;         	\n
    	gl_Position = ftransform(); 			\n
    	pos = gl_ModelViewMatrix * gl_Vertex;  		\n
	texCoord = gl_MultiTexCoord0;			\n
}                               			\n
);

const char* CheckerboardGFS = STRINGIFY(
varying vec3 normal;            \n
varying vec4 pos;		\n
varying vec4 texCoord;		\n

vec4 checker(vec4 uv) {							\n
  float checkSize = 16.0;						\n
  float fmodResult = mod(floor(checkSize * uv.x) + floor(checkSize * uv.y),2.0);\n
  if (fmodResult < 1.0) {						\n
    return vec4(0.6, 0, 0.2, 1);  						\n
  } else {								\n
    return vec4(0.1, 0.6, 0, 1);  						\n
  }									\n
}

void main()                     \n
{                               \n

	vec4 Ia= gl_LightSource[0].ambient; 			\n
	vec4 Ka = gl_FrontMaterial.ambient; 			\n
	vec4 Iamb = Ia*Ka; 					\n
	
	vec4 Kd = gl_FrontMaterial.diffuse; 			\n
	vec4 lpos = gl_LightSource[0].position;			\n
	vec3 L = (normalize(lpos-pos)).xyz; 			\n
	vec3 n = normalize(normal); 				\n
	vec4 Id = gl_LightSource[0].diffuse; 			\n
	vec4 Idiff = Kd * max(0.0, dot(n,L)) * Id; 		\n

	vec3 R = reflect(-L,n); 				\n
	R = normalize(R); 					\n
	vec3 V = -pos.xyz; 					\n
	V = normalize(V); 					\n
	vec4 Is = gl_LightSource[0].specular; 			\n
	vec4 Ks = gl_FrontMaterial.specular;			\n
	float shininess = gl_FrontMaterial.shininess; 		\n
	vec4 Ispec; 						\n
	if(shininess != 0.0) 					\n
	{ 							\n
		Ispec = Ks * pow(max(0.0, dot(R, V)), shininess) * Is; \n
	} 							\n
	else 							\n 
	{ 							\n
		Ispec = vec4(0.0, 0.0, 0.0, 0.0);  		\n
	} 							\n
	vec4 check = checker(texCoord);				\n
	gl_FragColor = Iamb + Idiff + Ispec + check; 		\n

}       						\n                        

);

const char* CheckerboardBVS = STRINGIFY(
varying vec3 normal;            \n
varying vec4 pos;               \n
varying vec4 texCoord; 		\n

void main()                     \n
{                               \n
	normal = gl_NormalMatrix * gl_Normal;          	\n
    	gl_Position = ftransform(); 			\n
    	pos = gl_ModelViewMatrix * gl_Vertex;  		\n
	texCoord = gl_MultiTexCoord0;			\n
}                               			\n
);

const char* CheckerboardBFS = STRINGIFY(
varying vec3 normal;            \n
varying vec4 pos;		\n
varying vec4 texCoord;		\n

vec4 checker(vec4 uv) {							\n
  float checkSize = 8.0;						\n
  float fmodResult = mod(floor(checkSize * uv.x) + floor(checkSize * uv.y),2.0);\n
  if (fmodResult < 1.0) {						\n
    return vec4(1, 0, 0, 1);  						\n
  } else {								\n
    return vec4(0, 1, 0, 1);  						\n
  }									\n
}

void main()                     \n
{                               \n

	vec4 Ia= gl_LightSource[0].ambient; 			\n
	vec4 Ka = gl_FrontMaterial.ambient; 			\n
	vec4 Iamb = Ia*Ka; 					\n
	
	vec4 Kd = gl_FrontMaterial.diffuse; 			\n
	vec4 lpos = gl_LightSource[0].position;			\n
	vec3 L = (normalize(lpos-pos)).xyz; 			\n
	vec3 n = normalize(normal); 				\n
	vec4 Id = gl_LightSource[0].diffuse; 			\n
	vec4 Idiff = Kd * max(0.0, dot(n,L)) * Id; 		\n

	vec3 R = reflect(-L,n); 				\n
	R = normalize(R); 					\n
	vec3 V = -pos.xyz; 					\n
	V = normalize(V); 	
	vec3 H = normalize(L+V);				\n
	vec4 Is = gl_LightSource[0].specular; 			\n
	vec4 Ks = gl_FrontMaterial.specular;			\n
	float shininess = gl_FrontMaterial.shininess; 		\n
	vec4 Ispec; 						\n
	if(shininess != 0.0) 					\n
	{ 							\n
		Ispec = Ks * pow(max(0.0, dot(H, n)), shininess) * Is; \n
	} 							\n
	else 							\n 
	{ 							\n
		Ispec = vec4(0.0, 0.0, 0.0, 0.0);  		\n
	} 							\n
	vec4 check = checker(texCoord);				\n
	gl_FragColor = Iamb + Idiff + Ispec + check; 		\n

}       						\n                        

);

const char* NormalVS = STRINGIFY(
varying vec3 normal;            \n
varying vec4 pos;               \n
varying vec4 rawpos;		\n
varying vec4 texCoord;		\n
varying vec4 color;
void main()                     \n
{                               \n
	normal =gl_NormalMatrix *gl_Normal;         	\n
    	gl_Position = ftransform(); 			\n
    	pos = gl_ModelViewMatrix * gl_Vertex;  		\n
	texCoord = gl_MultiTexCoord0;			\n
	vec4 Ia= gl_LightSource[0].ambient; 			\n
	vec4 Ka = gl_FrontMaterial.ambient; 			\n
	vec4 Iamb = Ia*Ka; 					\n
	
	vec4 Kd = gl_FrontMaterial.diffuse; 			\n
	vec4 lpos = gl_LightSource[0].position;			\n
	vec3 L = (normalize(lpos-pos)).xyz; 			\n
	vec3 n = normalize(normal); 				\n
	vec4 Id = gl_LightSource[0].diffuse; 			\n
	vec4 Idiff = Kd * max(0.0, dot(n,L)) * Id; 		\n

	vec3 R = reflect(-L,n); 				\n
	R = normalize(R); 					\n
	vec3 V = -pos.xyz; 					\n
	V = normalize(V); 					\n
	vec4 Is = gl_LightSource[0].specular; 			\n
	vec4 Ks = gl_FrontMaterial.specular;			\n
	float shininess = gl_FrontMaterial.shininess; 		\n
	vec4 Ispec; 						\n
	if(shininess != 0.0) 					\n
	{ 							\n
		Ispec = Ks * pow(max(0.0, dot(R, V)), shininess) * Is; \n
	} 							\n
	else 							\n 
	{ 							\n
		Ispec = vec4(0.0, 0.0, 0.0, 0.0);  		\n
	} 							\n
	
	color = Iamb + Idiff + Ispec; 			\n
}                               			\n
);

const char* NormalFS = STRINGIFY(
varying vec3 normal;            				\n
varying vec4 pos;						\n
varying vec4 texCoord;						\n
varying vec4 color;


void main()                     				\n
{                               				\n

	
	vec3 temp1 = vec3(0.6, 0.3, 0.3);			\n
	vec3 temp2 = normalize(normal)*0.5+temp1;		\n
	gl_FragColor = color + vec4(temp2, 1);			\n
}       							\n                        

);


#endif

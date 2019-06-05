/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#ifndef __SYMTAB_H__
#define __SYMTAB_H__

#include "token.h"
#include "instructions.h"

enum TypeClass {//Phan loai ky hieu
  TP_INT,
  TP_CHAR,
  TP_FLOAT,
  TP_ARRAY
};

enum ObjectKind {//Phan loai ky hieu
  OBJ_CONSTANT,
  OBJ_VARIABLE,
  OBJ_TYPE,
  OBJ_FUNCTION,
  OBJ_PROCEDURE,
  OBJ_PARAMETER,
  OBJ_PROGRAM
};

enum ParamKind {
  PARAM_VALUE,
  PARAM_REFERENCE
};

struct Type_ {
  enum TypeClass typeClass;
  int arraySize;//chi su dung cho kieu mang
  struct Type_ *elementType;
};

typedef struct Type_ Type;
typedef struct Type_ BasicType;


struct ConstantValue_ {//Hang so
  enum TypeClass type;
  union {
    int intValue;
    char charValue;
    float floatValue;
  };
};

typedef struct ConstantValue_ ConstantValue;

struct Scope_;
struct ObjectNode_;
struct Object_;

struct ConstantAttributes_ {
  ConstantValue* value;
};

struct VariableAttributes_ {
  Type *type;
  struct Scope_ *scope;//Pham vi cua bien, su dung cho pha sinh ma
  int localOffset;        // offset of the local variable calculated from the base of the stack frame
};

struct TypeAttributes_ {
  Type *actualType;
};

struct ProcedureAttributes_ {
  struct ObjectNode_ *paramList;//Tham bien hoac Tham tri
  struct Scope_* scope;

  int paramCount;
  CodeAddress codeAddress;
};

struct FunctionAttributes_ {
  struct ObjectNode_ *paramList;
  Type* returnType;
  struct Scope_ *scope;

  int paramCount;
  CodeAddress codeAddress;
};

struct ProgramAttributes_ {
  struct Scope_ *scope;
  CodeAddress codeAddress;
};

struct ParameterAttributes_ {
  enum ParamKind kind;
  Type* type;
  struct Scope_ *scope;

  int localOffset;
};

typedef struct ConstantAttributes_ ConstantAttributes;
typedef struct TypeAttributes_ TypeAttributes;
typedef struct VariableAttributes_ VariableAttributes;
typedef struct FunctionAttributes_ FunctionAttributes;
typedef struct ProcedureAttributes_ ProcedureAttributes;
typedef struct ProgramAttributes_ ProgramAttributes;
typedef struct ParameterAttributes_ ParameterAttributes;

struct Object_ {//Thuoc tinh cua doi tuong tren bang ky hieu
  char name[MAX_IDENT_LEN];
  enum ObjectKind kind;
  union {
    ConstantAttributes* constAttrs;
    VariableAttributes* varAttrs;
    TypeAttributes* typeAttrs;
    FunctionAttributes* funcAttrs;
    ProcedureAttributes* procAttrs;
    ProgramAttributes* progAttrs;
    ParameterAttributes* paramAttrs;
  };
};

typedef struct Object_ Object;

struct ObjectNode_ {
  Object *object;
  struct ObjectNode_ *next;
};

typedef struct ObjectNode_ ObjectNode;

struct Scope_ {//Pham vi cua 1 bloc
  ObjectNode *objList;//Danh sach doi tuong cua block
  Object *owner;//Ham, Thu tuc, Chuong trinh tuong ung voi Block
  struct Scope_ *outer;//Pham vi bao ngoai
  int frameSize;
};

typedef struct Scope_ Scope;

struct SymTab_ {//Bang ky hieu
  Object* program;//Chuong trinh chinh
  Scope* currentScope;//Pham vi hien tai
  ObjectNode *globalObjectList;//Cac doi tuong toan cuc nhu WRITEI, WRITEC, WRITELN, READI, READC
};

typedef struct SymTab_ SymTab;

//Cac ham tao kieu
Type* makeIntType(void);
Type* makeCharType(void);
Type* makeFloatType(void);
Type* makeArrayType(int arraySize, Type* elementType);
Type* duplicateType(Type* type);
int compareType(Type* type1, Type* type2);
void freeType(Type* type);
int sizeOfType(Type* type);

//Cac ham tao gia tri hang so
ConstantValue* makeIntConstant(int i);
ConstantValue* makeCharConstant(char ch);
ConstantValue* makeFloatConstant(float f);
ConstantValue* duplicateConstantValue(ConstantValue* v);

Scope* createScope(Object* owner);

Object* createProgramObject(char *programName);
Object* createConstantObject(char *name);
Object* createTypeObject(char *name);
Object* createVariableObject(char *name);
Object* createFunctionObject(char *name);
Object* createProcedureObject(char *name);
Object* createParameterObject(char *name, enum ParamKind kind);

Object* findObject(ObjectNode *objList, char *name);

void initSymTab(void);//Khoi tao bang ky hieu
void cleanSymTab(void);
void enterBlock(Scope* scope);
void exitBlock(void);
void declareObject(Object* obj);

#endif

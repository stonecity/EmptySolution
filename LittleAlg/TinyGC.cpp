// TinyGC.c
// 精简版垃圾回收器

#include "stdafx.h"
#include <stdlib.h>

#define STACK_MAX 256

typedef enum {
	OBJ_INT,
	OBJ_PAIR
} ObjectType;

// 基类对象
typedef struct SObject {
	ObjectType type;
	unsigned char marked;

	// 对象链表中的下一个对象
	struct SObject* next;

	union {
		/* OBJ_INT */
		int value;

		/* OBJ_PAIR */
		struct {
			struct SObject* head;
			struct SObject* tail;
		};
	};
} MObject;

// 对象池
typedef struct {
	MObject* stack[STACK_MAX];
	int stackSize;

	// 在堆上所有的对象链表中的第一个对象
	MObject* firstObject;

	// 当前分配的对象个数
	int numObjects;

	// 能够容纳对象的最大个数
	int maxObjects;
} VM;

void MAssert(int condition, const char* message) {
	if (!condition) {
		printf("Hint Assert: %s\n", message);
		exit(1);
	}
}

// 创建虚拟机，管理内存
VM* newVM() {
	VM* vm = (VM*)malloc(sizeof(VM));
	vm->stackSize = 0;
	vm->firstObject = NULL;
	vm->numObjects = 0;
	vm->maxObjects = 8;
	return vm;
}

void push(VM* vm, MObject* value) {
	MAssert(vm->stackSize < STACK_MAX, "Stack overflow!");
	vm->stack[vm->stackSize++] = value;
}

MObject* pop(VM* vm) {
	MAssert(vm->stackSize > 0, "Stack underflow!");
	return vm->stack[--vm->stackSize];
}

void mark(MObject* object) {
	// 如果已经为对象做了标记，就不再处理，防止出现无限递归
	if (object->marked)	{
		return;
	}

	object->marked = 1;

	if (object->type == OBJ_PAIR) {
		mark(object->head);
		mark(object->tail);
	}
}

void markAll(VM* vm) {
	for (int i = 0; i < vm->stackSize; i++) {
		mark(vm->stack[i]);
	}
}

// 释放未被标记的无用对象
void sweep(VM* vm) {
	MObject** object = &vm->firstObject;
	while (*object) {
		if (!(*object)->marked) {
			// 遇到了不可达的对象，开始进行GC调用
			MObject* unreached = *object;

			*object = unreached->next;
			free(unreached);

			vm->numObjects--;
		}
		else {
			// 对象是可达的，取消标记
			(*object)->marked = 0;
			object = &(*object)->next;
		}
	}
}

void gc(VM* vm) {
	int numObjects = vm->numObjects;

	// 标记对象
	markAll(vm);

	// 清扫无用对象
	sweep(vm);

	vm->maxObjects = vm->numObjects * 2;

	printf("Collected %d objects, %d remaining.\n", 
			numObjects - vm->numObjects,
			vm->numObjects);
}

MObject* newObject(VM* vm, ObjectType type) {
	MObject* object = NULL;
	if (vm->numObjects == vm->maxObjects) gc(vm);

	object = (MObject*)malloc(sizeof(MObject));
	object->type = type;
	object->next = vm->firstObject;
	vm->firstObject = object;
	object->marked = 0;

	vm->numObjects++;

	return object;
}

// 将对象放到对象池中
void pushInt(VM* vm, int intValue) {
	MObject* object = newObject(vm, OBJ_INT);
	object->value = intValue;

	push(vm, object);
}

MObject* pushPair(VM* vm) {
	MObject* object = newObject(vm, OBJ_PAIR);
	object->tail = pop(vm);
	object->head = pop(vm);

	push(vm, object);
	return object;
}

void objectPrint(MObject* object) {
	switch (object->type) {
	case OBJ_INT:
		printf("%d", object->value);
		break;

	case OBJ_PAIR:
		printf("(");
		objectPrint(object->head);
		printf(", ");
		objectPrint(object->tail);
		printf(")");
		break;
	}
}

//************** 测试用例 ****************

void test1() {
	printf("Test 1: Objects on stack are preserved.\n");
	VM* vm = newVM();
	pushInt(vm, 1);
	pushInt(vm, 2);

	gc(vm);
	MAssert(vm->numObjects == 2, "Should have preserved objects.");
}

void test2() {
	printf("Test 2: Unreached objects are collected.\n");
	VM* vm = newVM();
	pushInt(vm, 1);
	pushInt(vm, 2);
	pop(vm);
	pop(vm);

	gc(vm);
	MAssert(vm->numObjects == 0, "Should have collected objects.");
}

void test3() {
	printf("Test 3: Reach nested objects.\n");
	VM* vm = newVM();
	pushInt(vm, 1);
	pushInt(vm, 2);
	pushPair(vm);
	pushInt(vm, 3);
	pushInt(vm, 4);
	pushPair(vm);
	pushPair(vm);

	gc(vm);
	MAssert(vm->numObjects == 7, "Should have reached objects.");
}

void test4() {
	printf("Test 4: Handle cycles.\n");
	VM* vm = newVM();
	pushInt(vm, 1);
	pushInt(vm, 2);
	MObject* a = pushPair(vm);
	pushInt(vm, 3);
	pushInt(vm, 4);
	MObject* b = pushPair(vm);

	a->tail = b;
	b->tail = a;

	gc(vm);
	MAssert(vm->numObjects == 4, "Should have collected objects.");
}

void perfTest() {
	printf("Performance Test.\n");
	VM* vm = newVM();

	for (int i = 0; i < 10; i++) 
	{
		for (int j = 0; j < 20; j++) 
		{
			pushInt(vm, i);
		}

		for (int k = 0; k < 20; k++) 
		{
			pop(vm);
		}
	}
}

int gc_main() 
{
	test1();
	test2();
	test3();
	test4();

	perfTest();

	return 0;
}

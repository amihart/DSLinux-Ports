#ifndef _LIB_SYSARG_
#define _LIB_SYSARG_ 1
#define PACK0(n)
#define PACK1(n,r1) \
	(uint64_t)r1
#define PACK2(n,r1,r2) \
	(uint64_t)r1, (uint64_t)r2
#define PACK3(n,r1,r2,r3) \
	(uint64_t)r1, (uint64_t)r2, (uint64_t)r3
#define PACK4(n,r1,r2,r3,r4) \
	(uint64_t)r1, (uint64_t)r2, (uint64_t)r3, \
	(uint64_t)r4
#define PACK5(n,r1,r2,r3,r4,r5) \
	(uint64_t)r1, (uint64_t)r2, (uint64_t)r3, \
	(uint64_t)r4, (uint64_t)r5
#define PACK6(n,r1,r2,r3,r4,r5,r6) \
	(uint64_t)r1, (uint64_t)r2, (uint64_t)r3, \
	(uint64_t)r4, (uint64_t)r5, (uint64_t)r6
#define PACK7(n,r1,r2,r3,r4,r5,r6,r7) \
	(uint64_t)r1, (uint64_t)r2, (uint64_t)r3, \
	(uint64_t)r4, (uint64_t)r5, (uint64_t)r6, \
	(uint64_t)r7
#define PACK8(n,r1,r2,r3,r4,r5,r6,r7,r8) \
	(uint64_t)r1, (uint64_t)r2, (uint64_t)r3, \
	(uint64_t)r4, (uint64_t)r5, (uint64_t)r6, \
	(uint64_t)r7, (uint64_t)r8
#define PACK9(n,r1,r2,r3,r4,r5,r6,r7,r8,r9) \
	(uint64_t)r1, (uint64_t)r2, (uint64_t)r3, \
	(uint64_t)r4, (uint64_t)r5, (uint64_t)r6, \
	(uint64_t)r7, (uint64_t)r8, (uint64_t)r9
#define PACK10(n,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10) \
	(uint64_t)r1, (uint64_t)r2, (uint64_t)r3, \
	(uint64_t)r4, (uint64_t)r5, (uint64_t)r6, \
	(uint64_t)r7, (uint64_t)r8, (uint64_t)r9, \
	(uint64_t)r10
#define PACK11(n,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11) \
	(uint64_t)r1, (uint64_t)r2, (uint64_t)r3, \
	(uint64_t)r4, (uint64_t)r5, (uint64_t)r6, \
	(uint64_t)r7, (uint64_t)r8, (uint64_t)r9, \
	(uint64_t)r10, (uint64_t)r11
#define PACK12(n,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12) \
	(uint64_t)r1, (uint64_t)r2, (uint64_t)r3, \
	(uint64_t)r4, (uint64_t)r5, (uint64_t)r6, \
	(uint64_t)r7, (uint64_t)r8, (uint64_t)r9, \
	(uint64_t)r10, (uint64_t)r11, (uint64_t)r12
#define PACK13(n,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13) \
	(uint64_t)r1, (uint64_t)r2, (uint64_t)r3, \
	(uint64_t)r4, (uint64_t)r5, (uint64_t)r6, \
	(uint64_t)r7, (uint64_t)r8, (uint64_t)r9, \
	(uint64_t)r10, (uint64_t)r11, (uint64_t)r12, \
	(uint64_t)r13
#define PACK14(n,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14) \
	(uint64_t)r1, (uint64_t)r2, (uint64_t)r3, \
	(uint64_t)r4, (uint64_t)r5, (uint64_t)r6, \
	(uint64_t)r7, (uint64_t)r8, (uint64_t)r9, \
	(uint64_t)r10, (uint64_t)r11, (uint64_t)r12, \
	(uint64_t)r13, (uint64_t)r14
#define PACK15(n,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15) \
	(uint64_t)r1, (uint64_t)r2, (uint64_t)r3, \
	(uint64_t)r4, (uint64_t)r5, (uint64_t)r6, \
	(uint64_t)r7, (uint64_t)r8, (uint64_t)r9, \
	(uint64_t)r10, (uint64_t)r11, (uint64_t)r12, \
	(uint64_t)r13, (uint64_t)r14, (uint64_t)r15
#define PACK16(n,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16) \
	(uint64_t)r1, (uint64_t)r2, (uint64_t)r3, \
	(uint64_t)r4, (uint64_t)r5, (uint64_t)r6, \
	(uint64_t)r7, (uint64_t)r8, (uint64_t)r9, \
	(uint64_t)r10, (uint64_t)r11, (uint64_t)r12, \
	(uint64_t)r13, (uint64_t)r14, (uint64_t)r15, \
	(uint64_t)r16
#define PACK17(n,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16,r17) \
	(uint64_t)r1, (uint64_t)r2, (uint64_t)r3, \
	(uint64_t)r4, (uint64_t)r5, (uint64_t)r6, \
	(uint64_t)r7, (uint64_t)r8, (uint64_t)r9, \
	(uint64_t)r10, (uint64_t)r11, (uint64_t)r12, \
	(uint64_t)r13, (uint64_t)r14, (uint64_t)r15, \
	(uint64_t)r16, (uint64_t)r17
#define PACK18(n,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16,r17,r18) \
	(uint64_t)r1, (uint64_t)r2, (uint64_t)r3, \
	(uint64_t)r4, (uint64_t)r5, (uint64_t)r6, \
	(uint64_t)r7, (uint64_t)r8, (uint64_t)r9, \
	(uint64_t)r10, (uint64_t)r11, (uint64_t)r12, \
	(uint64_t)r13, (uint64_t)r14, (uint64_t)r15, \
	(uint64_t)r16, (uint64_t)r17, (uint64_t)r18
#define PACK19(n,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16,r17,r18,r19) \
	(uint64_t)r1, (uint64_t)r2, (uint64_t)r3, \
	(uint64_t)r4, (uint64_t)r5, (uint64_t)r6, \
	(uint64_t)r7, (uint64_t)r8, (uint64_t)r9, \
	(uint64_t)r10, (uint64_t)r11, (uint64_t)r12, \
	(uint64_t)r13, (uint64_t)r14, (uint64_t)r15, \
	(uint64_t)r16, (uint64_t)r17, (uint64_t)r18, \
	(uint64_t)r19
#define PACK_SHIFT( \
		N0, N1, N2, N3, N4, N5, \
		N6, N7, N8, N9, N10, N11, \
		N12, N13, N14, N15, N16, N17, \
		N18, N19,\
		NAME, ...\
	) NAME
#define PACK(...) PACK_SHIFT( \
		__VA_ARGS__, \
		PACK19, PACK18, PACK17, PACK16, \
		PACK15, PACK14, PACK13, PACK12, \
		PACK11, PACK10, PACK9, PACK8, \
		PACK7, PACK6, PACK5, PACK4, \
		PACK3, PACK2, PACK1, PACK0 \
	)(__VA_ARGS__)

#define CONCATX(x,y) x##y
#define CONCAT(x,y) CONCATX(x,y)
#define VARGS(Y, ...) uint64_t CONCAT(TMP,__LINE__) [] = {PACK(1,__VA_ARGS__)}; \
Y((sizeof(CONCAT(TMP,__LINE__) )/sizeof(uint64_t)), CONCAT(TMP,__LINE__) )
#endif

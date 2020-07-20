	.intel_syntax noprefix

	.text

	.global sum
	.global diff

# int sum(int a, int b)
sum:
	push	ebp
	mov		ebp,esp
	mov		eax,[ebp+8]	 # a
	add		eax,[ebp+12] # b
	pop 	ebp
	ret

# int diff(int *a, int *b)
diff:
	push 	ebp
	mov		ebp,esp
	push	ebx
	mov		ebx,[ebp+8]	 # &a
	mov		eax,[ebx]	 # a
	mov		ebx,[ebp+12] # &b
	sub		eax,[ebx]	 # b
	pop 	ebx
	pop		ebp
	ret

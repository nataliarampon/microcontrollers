	.intel_syntax noprefix

	.text

	.global print_uppercase

# void print_uppercase(char* lowercase_string)
print_uppercase:
	push	ebp	# save stack place so we can restore it later
	mov 	ebp,esp # put stack pointer to base pointer so we can use ebp from now on
	push 	esi	# save source index
	push	edi	# save destination index
	push	ebx
	xor 	edx,edx	# so edx = 0 (it's going to be the string length counter)
	mov		esi, [ebp+8] # the pointer to the string beginning is at the first parameter of the function [ebp+8]
	mov 	edi, [ebp+8] # we're writing to the same string
	cld			# clear direction flag so the edi,esi registers are incremented for strings op
loop:
	lodsb		# load a byte from the string pointed by esi+increment into register al
	add		edx,1 # increment length counter by 1
	and 	al,0xDF	# mask 0xDF, making this AND with 0xDF will add a 1 at position 5 of a byte		
	jz		print # if it's zero, it means it was an and of 0xDF and 0x0, that is, end of string
	stosb		# stores a byte from al into string pointed by edi+increment
	jmp 	loop
print:
	mov 	eax,4	# linux kernel function code for the writing function
	mov		ebx,1	# file descriptor, 1 means stdout
	mov		ecx, [ebp+8]	# pointer to message to write
	int 	0x80	# interruption 0x80 is the write function in the linux kernel
	pop 	ebx		# now we restore all registers supposed to be restored in a function call
	pop		edi
	pop		esi
	pop 	ebp		# restore stack to original place, taking the function context out of it
	ret

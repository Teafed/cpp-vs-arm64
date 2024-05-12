//subroutine bubble_sort_ass: given a pointer to the beginning of an
//	int array and an integer representing the array's size, this function
//	will use bubble sort to sort the array.
//returned contents:
//x0: contains a pointer to the starting address of the sorted int array

	.global bubble_sort_ass 			//ass stands for assembly

	.text

bubble_sort_ass:

	stp		x30, x29, [sp, #-16]!	//push lr, x29

												//x0 = nums[]
												//x1 = num_count
												//x2 = nums current address
	mov		x3, x1
	sub		x3, x3, #1					//x3 = num_count - 1
	mov		x4, #0						//x4 = i
												//x5 = j
	mov		x6, #0						//x6 = temp
												//x7 = (num_count - 1) - i

		bsa_iloop:
		mov		x2, x0						//set &nums to nums[0]
		cmp		x4, x3						//compare x4 and x3~ rawr
		bge		bsa_exit						//break when i >= num_count - 1

			mov		x5, #0						//j = 0
			sub		x7, x3, x4					//x7 = (num_count - 1) - i
			bsa_jloop:
			cmp		x5, x7						//compare j and x7
			bge		bsa_iloop_end				//end j loop when j >= x7

				bsa_comparison:
				ldr		w8, [x2]						//w8 = nums[i]
				add		x2, x2, #4					//shift nums& forward 4 bytes
				ldr		w9, [x2]						//w9 = nums[i + 1]

				cmp		w8, w9						//is nums[j] < nums[j + 1]?
				blt		bsa_jloop_end				//if true, no swap
				bl			bsa_swap						//stop 'n' swop!

			bsa_jloop_end:
			add		x5, x5, #1					//j++
			b			bsa_jloop					//repeat j loop

		bsa_iloop_end:
		add		x4, x4, #1					//i++
		b			bsa_iloop					//repeat i loop

bsa_exit:

	ldp		x30, x29, [sp], #16		//pop lr, x29
	ret		lr								//return to sender

bsa_swap:

	stp		x29, x30, [sp, #-16]!	//push x29, lr

	str		w8, [x2]						//store nums[j] in nums[j + 1]
	sub		x2, x2, #4					//shift nums& back 4 bytes
	str		w9, [x2]						//store nums[j + 1] in nums[j]
	add		x2, x2, #4					//shift nums& forward 4 bytes

	ldp		x29, x30, [sp], #16		//pop x29, lr
	ret		lr								//return

.end


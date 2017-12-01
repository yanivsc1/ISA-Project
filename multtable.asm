MEM[1024 + (j-1)*10 + (i-1)] = j*i

mul(int i, int j){
	res = 0;
	for (k = 1; k <= i; ++k){
		res = res + j;
	}
}

main(){
	for (j = 1; j <= 10; ++j){
		for (i = 1; i <= 10; ++i){
			MEM[1024+(j-1)*10+(i-1)] = mul(i,j);
		}
	}
}



MAIN:
limm $sp, $zero, $zero, 2048		# $sp = 2048
limm $t0, $zero, $zero, 1		# $t0 = 1

limm $t1, $zero, $zero, 12		# $t1 = 12
sub $sp, $sp, $t1, 0			# allocate stack space
sw $s0, $sp, $zero, $zero		# store $s0 on stack
sw $s1, $sp, $zero, 4			# store $s1 on stack
sw $s2, $sp, $zero, 8			# store $s2 on stack

limm $t1, $zero, $zero, 1024		# $t1 = 1024

add $s0, $t0, $zero, 0			# $s0 := i = 1
add $s1, $t0, $zero, 0			# $s1 := j = 1
limm $s2, $zero, $zero, 10		# $s2 = 10

MAIN_FOR_1:
bgt $zero, $s1, $s2, END_MAIN_FOR_1	# if (j > 10) jump to END_MAIN_FOR_1

MAIN_FOR_2:
bgt $zero, $s0, $s2, END_MAIN_FOR_2	# if (i > 10) jump to EMD_MAIN_FOR_2

limm $t2, $zero, $zero, 1		# $t2 := k = 1
limm $t3, $zero, $zero, 0		# $t3 := res = 0
MUL_FOR:
bgt $zero, $t2, $s0, END_MUL_FOR	# if (k > i) jump to END_MUL_FOR
add $t3, $t3, $s1, 0			# res = res + j
add $t2, $t2, $t0, 0			# k++

END_MUL_FOR:
sw $t3, $t1, $zero, 0			# MEM[1024+(j-1)*10+(i-1)] = i * j
add $t1, $t1, $t0, 0			# $t1++

add $s0, $s0, $t0, 0			# i++
END_MAIN_FOR_2:
add $s1, $s1, $t0, 0			# j++

END_MAIN_FOR_1:
lw $s0, $sp, $zero, 0			# restore $s0's original value 
lw $s1, $sp, $zero, 4			# restore $s1's original value
lw $s2, $sp, $zero, 8			# restore $s2's original value
limm $t0, $zero, $zero, 12		# $t0 = 12
add $sp, $sp, $t0, 0			# restore stack pointer to original value
halt $zero, $zero, $zero, 0		# finish

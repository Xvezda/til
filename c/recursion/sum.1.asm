    0x100000ed0 <+0>:   pushq  %rbp
    0x100000ed1 <+1>:   movq   %rsp, %rbp   ; Create stack frame
    0x100000ed4 <+4>:   subq   $0x20, %rsp  ; Allocate 0x20 -> 4 byte
    0x100000ed8 <+8>:   movl   $0x0, -0x4(%rbp)  ; [rbp-0x4] = 0
    0x100000edf <+15>:  movl   %edi, -0x8(%rbp)  ; [rbp-0x8] = edi
    0x100000ee2 <+18>:  movq   %rsi, -0x10(%rbp) ; [rbp-0x10] = rsi
    0x100000ee6 <+22>:  cmpl   $0x2, -0x8(%rbp)  ; if ([rbp-0x8] == 0x2)
    0x100000eea <+26>:  je     0x100000f1e       ; <+78> at main.c:19:29
    0x100000ef0 <+32>:  movq   0x111(%rip), %rax ; (void *)0x00007fff8e9db9a0: __stderrp
    0x100000ef7 <+39>:  movq   (%rax), %rdi
    0x100000efa <+42>:  movq   -0x10(%rbp), %rax
    0x100000efe <+46>:  movq   (%rax), %rdx
    0x100000f01 <+49>:  leaq   0x8e(%rip), %rsi ; "usage: %s [NUMBER]\n"
    0x100000f08 <+56>:  movb   $0x0, %al
    0x100000f0a <+58>:  callq  0x100000f5c      ; symbol stub for: fprintf
    0x100000f0f <+63>:  movl   $0x1, -0x4(%rbp)
    0x100000f16 <+70>:  movl   %eax, -0x14(%rbp)
    0x100000f19 <+73>:  jmp    0x100000f4c      ; <+124> at main.c:22:1
->  0x100000f1e <+78>:  movq   -0x10(%rbp), %rax; rax = [rbp-0x10] = rsi
    0x100000f22 <+82>:  movq   0x8(%rax), %rdi  ; rdi = [rax+0x8]
    0x100000f26 <+86>:  callq  0x100000f56      ; symbol stub for: atoi
    0x100000f2b <+91>:  movl   %eax, %edi       ; edi = eax
    0x100000f2d <+93>:  callq  0x100000e90      ; sum at main.c:7
    0x100000f32 <+98>:  leaq   0x71(%rip), %rdi ; "%d\n"
    0x100000f39 <+105>: movl   %eax, %esi
    0x100000f3b <+107>: movb   $0x0, %al
    0x100000f3d <+109>: callq  0x100000f62      ; symbol stub for: printf
    0x100000f42 <+114>: movl   $0x0, -0x4(%rbp)
    0x100000f49 <+121>: movl   %eax, -0x18(%rbp)
    0x100000f4c <+124>: movl   -0x4(%rbp), %eax
    0x100000f4f <+127>: addq   $0x20, %rsp
    0x100000f53 <+131>: popq   %rbp
    0x100000f54 <+132>: retq

; sum
; disas -F intel -n sum
    0x100000e90 <+0>:  push   rbp
    0x100000e91 <+1>:  mov    rbp, rsp
    0x100000e94 <+4>:  sub    rsp, 0x10
    0x100000e98 <+8>:  mov    dword ptr [rbp - 0x8], edi  ; [rbp-0x8] = edi
                              ; [rbp-0x8] == argv[0] == edi
    0x100000e9b <+11>: cmp    dword ptr [rbp - 0x8], 0x1  ; if ([rbp-0x8] == 1)
    0x100000e9f <+15>: jg     0x100000eb1               ; <+33> at main.c:9:16
    0x100000ea5 <+21>: mov    dword ptr [rbp - 0x4], 0x1 ; [rbp-0x4] = 0x1

                              ; 0x100000ec4 => eax = [rbp-0x4] = 0x1
                              ; -> return 1
    0x100000eac <+28>: jmp    0x100000ec4               ; <+52> at main.c:10:1
    0x100000eb1 <+33>: mov    eax, dword ptr [rbp - 0x8]  ; eax = [rbp-0x8]
    0x100000eb4 <+36>: sub    eax, 0x1 ; eax -= 0x1
    0x100000eb7 <+39>: mov    edi, eax ; edi = eax
                              ; this({edi: eax})
    0x100000eb9 <+41>: call   0x100000e90 ; Recursion - <+0> at main.c:7
                              ; return this(argv[0]-1) + argv[0]
    0x100000ebe <+46>: add    eax, dword ptr [rbp - 0x8]  ; eax += [rbp-0x8]
    0x100000ec1 <+49>: mov    dword ptr [rbp - 0x4], eax  ; [rbp-0x4] = eax
    0x100000ec4 <+52>: mov    eax, dword ptr [rbp - 0x4]  ; eax = [rbp-0x4]
                                                          ; Return eax

    0x100000ec7 <+55>: add    rsp, 0x10
    0x100000ecb <+59>: pop    rbp
    0x100000ecc <+60>: ret

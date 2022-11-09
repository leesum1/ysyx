#include <proc.h>
#include <elf.h>
#include <fs.h>
#ifdef __LP64__
// ELF Header
# define Elf_Ehdr Elf64_Ehdr
// Program header
# define Elf_Phdr Elf64_Phdr 
#else
# define Elf_Ehdr Elf32_Ehdr
# define Elf_Phdr Elf32_Phdr
#endif


#if defined(__ISA_AM_NATIVE__)
# define EXPECT_TYPE EM_X86_64
#elif defined(__ISA_X86__)
# define EXPECT_TYPE EM_386
#elif defined(__ISA_RISCV32__) || defined(__ISA_RISCV64__)
# define EXPECT_TYPE EM_RISCV
#else
# error Unsupported ISA
#endif


/* ramdisk 读写函数  */
extern size_t ramdisk_read(void* buf, size_t offset, size_t len);
extern size_t ramdisk_write(const void* buf, size_t offset, size_t len);
extern void init_ramdisk();
extern size_t get_ramdisk_size();



static uintptr_t loader(PCB* pcb, const char* filename) {

  // 打开文件
  Log("start loader %s\n", filename);
  int fd = fs_open(filename, 0, 0);

  /* 获取 elf header */
  Elf_Ehdr* Ehdr = (Elf_Ehdr*)malloc(sizeof(Elf_Ehdr));
  assert(Ehdr);

  fs_read(fd, Ehdr, sizeof(Elf_Ehdr));

  // 检查 magic
  assert(*(uint32_t*)Ehdr->e_ident == 0x464C457F);
  // 检查架构信息
  assert(EXPECT_TYPE == Ehdr->e_machine);
  /* 获取所有 Program header Table,Ehdr->e_phnum 为个数信息 */
  assert(Ehdr->e_phnum != 0);

  Elf_Phdr* Phdr = (Elf_Phdr*)malloc(sizeof(Elf_Phdr) * Ehdr->e_phnum);
  assert(Phdr);

  fs_lseek(fd, Ehdr->e_phoff, 0);
  fs_read(fd, (void*)Phdr, sizeof(Elf_Phdr) * Ehdr->e_phnum);

  /* 加载进内存,空闲空间需要清零 */
  for (int i = 0; i < Ehdr->e_phnum; i++) {

    if (Phdr[i].p_type == PT_LOAD) {
      fs_lseek(fd, Phdr[i].p_offset, 0);
      fs_read(fd, (void*)Phdr[i].p_vaddr, Phdr[i].p_filesz);
      // 清理未使用空间 !!!! 血的教训,清理空间的长度为 (p_memsz - p_filesz + 1),少一个byte都不行,不然 free 会报错
      memset((char*)(Phdr[i].p_vaddr + Phdr[i].p_filesz), 0, Phdr[i].p_memsz - Phdr[i].p_filesz + 1);
    }
  }

  Log("Ehdr->e_entry:%p\n", (void*)Ehdr->e_entry);

  free(Ehdr);
  free(Phdr);
  asm volatile("fence.i"); // 添加 fencei 指令
  return Ehdr->e_entry;
}

void naive_uload(PCB* pcb, const char* filename) {
  uintptr_t entry = loader(pcb, filename); // TODO 需要加 fencei 指令
  Log("Jump to entry = %p", (void*)entry);
  ((void(*)())entry) ();
}


void context_kload(PCB* pcb_p, void (*entry)(void*), void* arg) {

  pcb_p->cp = kcontext(RANGE(pcb_p->stack, pcb_p->stack + STACK_SIZE - 1), entry, arg);
}


void context_uload(PCB* pcb_p, const char* filename, char* const argv[], char* const envp[]) {

  uintptr_t entry = loader(pcb_p, filename);
  pcb_p->cp = ucontext(&pcb_p->as, RANGE(pcb_p->stack, pcb_p->stack + STACK_SIZE - 1), (void*)entry);

  uintptr_t ustack_end = pcb_p->cp->GPRx;
  Log("ustack_end: %p\n", ustack_end);

  int argc = 0;
  int envc = 0;
  while (argv[argc] != NULL) {
    argc++;
  }
  while (envp[envc] != NULL) {
    envc++;
  }
  Log("argc:%d,envc%d\n", argc, envc);

  // 统计 argv 中字符串长度
  int argv_str_len = 0;
  for (size_t argc_i = 0; argc_i < argc; argc_i++) {
    argv_str_len += strlen(argv[argc_i]) + 1; // 加上字符串结束的 \0
    Log("argv%d:%s\n", argc_i, argv[argc_i]);
  }

  // 统计 envp 中字符串长度
  int envp_str_len = 0;
  for (size_t envc_i = 0; envc_i < envc; envc_i++) {
    envp_str_len += strlen(envp[envc_i]) + 1;
    Log("envp%d:%s\n", envc_i, envp[envc_i]);
  }


  uintptr_t str_area_end = (uintptr_t)ustack_end - envp_str_len - argv_str_len;

  uintptr_t str_area_p = str_area_end;
  for (size_t argc_i = 0; argc_i < argc; argc_i++) {
    strcpy((char*)str_area_p, argv[argc_i]);
    str_area_p += strlen(argv[argc_i]) + 1;
  }

  for (size_t envc_i = 0; envc_i < envc; envc_i++) {
    strcpy((char*)str_area_p, envp[envc_i]);
    str_area_p += strlen(envp[envc_i]) + 1;
  }


  assert(str_area_p == ustack_end); // 不留空
  assert((str_area_end + envp_str_len + argv_str_len) == ustack_end);

  uintptr_t str_area_end_align = ROUNDDOWN(str_area_end, 8); // 地址对齐


  printf("pre:%p,next:%p\n", str_area_end, str_area_end_align);



  uintptr_t argv_aria_end = str_area_end_align - (envc + argc + 2) * 8;// 2 NULL

  // 指向 用户栈 地址
  uintptr_t* argv_aria_end_p = (uintptr_t*)argv_aria_end;

  str_area_p = str_area_end;
  for (size_t argc_i = 0; argc_i < argc; argc_i++) {
    *(argv_aria_end_p) = str_area_p; // 用户堆栈指向字符串
    Log("%s", *argv_aria_end_p);
    argv_aria_end_p++;
    str_area_p += strlen(argv[argc_i]) + 1;
  }
  *(argv_aria_end_p++) = (uintptr_t)NULL;


  for (size_t envc_i = 0; envc_i < envc; envc_i++) {
    *(argv_aria_end_p) = str_area_p;
    Log("%s", *argv_aria_end_p);
    argv_aria_end_p++;
    str_area_p += strlen(envp[envc_i]) + 1;
  }

  assert(str_area_p == ustack_end);

  *(argv_aria_end_p++) = (uintptr_t)NULL;



  *(uintptr_t*)(argv_aria_end - 8) = argc;

  pcb_p->cp->GPRx = (argv_aria_end - 8);

  uintptr_t argc_test = *(uintptr_t*)(pcb_p->cp->GPRx);

  // uintptr_t argv_test = 
  uintptr_t* argv_test = (uintptr_t*)argv_aria_end;
  uintptr_t** envp_test = (uintptr_t**)(argv_test + argc_test  + 1);

  Log("argv_test:%p,envp_test:%p", argv_test,envp_test);


  for (size_t i = 0; i < argc_test; i++) {
    Log("argc_test%d:%s", i, argv_test[i]);
  }

  while ((*envp_test) != NULL) {
    Log("envp_test:%s", *(envp_test++));
  }



  //assert(0);
  Log("argv_str_len:%d,envp_str_len%d\n", argv_str_len, envp_str_len);
}
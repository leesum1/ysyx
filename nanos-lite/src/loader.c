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

  Log("Ehdr->e_entry:%p\n", Ehdr->e_entry);

  free(Ehdr);
  free(Phdr);
  return Ehdr->e_entry;
}

void naive_uload(PCB* pcb, const char* filename) {
  uintptr_t entry = loader(pcb, filename); // TODO 需要加 fencei 指令
  Log("Jump to entry = %p", entry);
  ((void(*)())entry) ();
}


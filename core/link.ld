/* Copyright (c) 2020 Sonal Pinto       */
/* SPDX-License-Identifier: Apache-2.0  */

/*KRZ::picolibc.ld*/

OUTPUT_ARCH( "riscv" )

MEMORY {
  bootrom  (rx) : ORIGIN = 0x00000000, LENGTH = 1K
  ram      (rwx): ORIGIN = 0x00010000, LENGTH = 128K
  system   (rw) : ORIGIN = 0x00800000, LENGTH = 8M
}

ENTRY(_start)

PHDRS
{
  text PT_LOAD;
  ram PT_LOAD;
  ram_init PT_LOAD;
  tls PT_TLS;
}

SECTIONS
{
  PROVIDE(__stack = ORIGIN(ram) + LENGTH(ram));

  .init : {
    KEEP (*(.text.init.enter))
    KEEP (*(.data.init.enter))
    KEEP (*(SORT_BY_NAME(.init) SORT_BY_NAME(.init.*)))
  } >ram :text

  .text : {
    *(.text.unlikely .text.unlikely.*)
    *(.text.startup .text.startup.*)
    *(.text .text.*)
    *(.gnu.linkonce.t.*)
  } >ram :text

  PROVIDE (__etext = __text_end);
  PROVIDE (_etext = __text_end);
  PROVIDE (etext = __text_end);

  rodata : {
    *(.rdata)
    *(.rodata .rodata.*)
    *(.gnu.linkonce.r.*)
    . = ALIGN(8);
    *(.srodata.cst16)
    *(.srodata.cst8)
    *(.srodata.cst4)
    *(.srodata.cst2)
    *(.srodata .srodata.*)
  } >ram :text

  . = ALIGN(8);

  .preinit_array : {
    PROVIDE_HIDDEN ( __preinit_array_start = . );
    KEEP (*(.preinit_array))
    PROVIDE_HIDDEN ( __preinit_array_end = . );
  } >ram :text

  .init_array : {
    PROVIDE_HIDDEN ( __init_array_start = . );
    KEEP (*(SORT_BY_INIT_PRIORITY(.init_array.*) SORT_BY_INIT_PRIORITY(.ctors.*)))
    KEEP (*(.init_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .ctors))
    PROVIDE_HIDDEN ( __init_array_end = . );
  } >ram :text

  .fini_array : {
    PROVIDE_HIDDEN ( __fini_array_start = . );
    KEEP (*(SORT_BY_INIT_PRIORITY(.fini_array.*) SORT_BY_INIT_PRIORITY(.dtors.*)))
    KEEP (*(.fini_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .dtors))
    PROVIDE_HIDDEN ( __fini_array_end = . );
  } >ram :text

  ctors : {
    KEEP (*crtbegin.o(.ctors))
    KEEP (*crtbegin?.o(.ctors))
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
  } >ram :text

  .dtors : {
    KEEP (*crtbegin.o(.dtors))
    KEEP (*crtbegin?.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
  } >ram :text

  /*
   * Data values which are preserved across reset
   */
  .preserve (NOLOAD) : {
    PROVIDE(__preserve_start__ = .);
    *(.preserve .preserve.*)
    PROVIDE(__preserve_end__ = .);
  } >ram :ram

  .data : ALIGN_WITH_INPUT {
    PROVIDE(__data_start = .);
    *(.data .data.*)
    *(.gnu.linkonce.d.*)
    . = ALIGN(8);
    PROVIDE( __global_pointer$ = . + 0x800 );
    *(.sdata .sdata.* .sdata2.*)
    *(.gnu.linkonce.s.*)
  } >ram :ram_init
  PROVIDE(__data_source = LOADADDR(.data));

  /* Thread local initialized data. This gets
   * space allocated as it is expected to be placed
   * in ram to be used as a template for TLS data blocks
   * allocated at runtime. We're slightly abusing that
   * by placing the data in flash where it will be copied
   * into the allocate ram addresses by the existing
   * data initialization code in crt0
   */
  .tdata : ALIGN_WITH_INPUT {
    PROVIDE( __tls_base = .);
    *(.tdata .tdata.* .gnu.linkonce.td.*)
    PROVIDE(__data_end = .);
  } >ram :tls :ram_init
  PROVIDE( __tdata_source = LOADADDR(.tdata) );
  PROVIDE( __tdata_size = SIZEOF(.tdata) );

  PROVIDE( __edata = __data_end );
  PROVIDE( _edata = __data_end );
  PROVIDE( edata = __data_end );
  PROVIDE( __data_size = __data_end - __data_start );

  .tbss (NOLOAD) : {
    PROVIDE( __bss_start = . );
    *(.tbss .tbss.* .gnu.linkonce.tb.*)
    *(.tcommon)
    PROVIDE( __tls_end = . );
  } >ram :tls :ram
  PROVIDE( __tbss_size = SIZEOF(.tbss) );
  PROVIDE( __tls_size = __tls_end - __tls_base );

  /*
   * The linker special cases .tbss segments which are
   * identified as segments which are not loaded and are
   * thread_local.
   *
   * For these segments, the linker does not advance 'dot'
   * across them.  We actually need memory allocated for tbss,
   * so we create a special segment here just to make room
   */
  .tbss_space (NOLOAD) : {
    . = . + __tbss_size;
  } >ram :ram

  .bss (NOLOAD) : {
    *(.sbss*)
    *(.gnu.linkonce.sb.*)
    *(.bss .bss.*)
    *(.gnu.linkonce.b.*)
    *(COMMON)
    . = ALIGN(8);
    __bss_end = .;
  } >ram :ram
  PROVIDE( __end = __bss_end );
  PROVIDE( _end = __bss_end );
  PROVIDE( end = __bss_end );
  PROVIDE( __bss_size = __bss_end - __bss_start );

  /* Make the rest of memory available for heap storage */
  PROVIDE( __heap_start = __end );
  PROVIDE( __heap_end = __stack - (DEFINED(__stack_size) ? __stack_size : 0x800) );
  PROVIDE( __heap_size = __heap_end - __heap_start );

  /* Throw away C++ exception handling information */
  /DISCARD/ : {
    *(.eh_frame .eh_frame.*)
  }
}

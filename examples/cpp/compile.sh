clang -DCORE_SUPPORTED -Dbpf_target_x86 \
      -target bpf -O2 -g -c \
      randomread_kern.c

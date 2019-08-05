#include "vmlinux.h"
#include "helpers.h"

struct event_t {
  int pid;
  char comm[16];
  int cpu;
  int got_bits;
};

BPF_PERF_OUTPUT(events);

int on_urandom_read(struct trace_event_raw_urandom_read* attr) {
  struct event_t event = {};
  event.pid = bpf_get_current_pid_tgid();
  bpf_get_current_comm(&event.comm, sizeof(event.comm));
  event.cpu = bpf_get_smp_processor_id();
  event.got_bits = attr->got_bits;

  events.perf_submit(attr, &event, sizeof(event));
  return 0;
}

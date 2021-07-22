use std::collections::HashMap;

static TEST_SIZE: usize = 1 << 22;

#[derive(Debug, Copy, Clone, Default, PartialEq, Eq, Hash, Ord, PartialOrd)]
#[repr(C, packed)]
pub struct Flow {
    pub src_ip: u32,
    pub dst_ip: u32,
    pub src_port: u16,
    pub dst_port: u16,
    pub proto: u8,
}

type Hasher = core::hash::BuildHasherDefault<wyhash::WyHash>;
type FnvHasher = core::hash::BuildHasherDefault<fnv::FnvHasher>;


fn main() {
    
    let mut map: HashMap<Flow, Flow> = HashMap::with_capacity(TEST_SIZE);
    map.reserve(TEST_SIZE);

    let mut flow = Flow {
        src_ip: 0,
        dst_ip: 0,
        src_port: 0,
        dst_port: 0,
        proto: 0,
    };

    let start = unsafe { core::arch::x86_64::_rdtsc() };

    for i in 0..TEST_SIZE {
        flow.src_ip = i as u32;
        map.insert(flow, flow);
    }

    let mut dummy: u32 = 0;
    let end = unsafe { core::arch::x86_64::__rdtscp(&mut dummy) };
    let duration = end - start;

    println!("Benchmark results for rust flow with default hasher");
    println!("Duration: {} cycles", duration);
    println!("Insertions: {}", TEST_SIZE);
    println!("Cycles per insertion: {} cycles", duration as f64 / TEST_SIZE as f64);
    println!();

    let mut map: HashMap<Flow, Flow, Hasher> = HashMap::with_capacity_and_hasher(TEST_SIZE, Default::default());
    map.reserve(TEST_SIZE);

    let mut flow = Flow {
        src_ip: 0,
        dst_ip: 0,
        src_port: 0,
        dst_port: 0,
        proto: 0,
    };

    let start = unsafe { core::arch::x86_64::_rdtsc() };

    for i in 0..TEST_SIZE {
        flow.src_ip = i as u32;
        map.insert(flow, flow);
    }

    let mut dummy: u32 = 0;
    let end = unsafe { core::arch::x86_64::__rdtscp(&mut dummy) };
    let duration = end - start;

    println!("Benchmark results for rust flow with fnv");
    println!("Duration: {} cycles", duration);
    println!("Insertions: {}", TEST_SIZE);
    println!("Cycles per insertion: {} cycles", duration as f64 / TEST_SIZE as f64);
    println!();

    let mut map: HashMap<Flow, Flow, FnvHasher> = HashMap::with_capacity_and_hasher(TEST_SIZE, Default::default());
    map.reserve(TEST_SIZE);

    let mut flow = Flow {
        src_ip: 0,
        dst_ip: 0,
        src_port: 0,
        dst_port: 0,
        proto: 0,
    };

    let start = unsafe { core::arch::x86_64::_rdtsc() };

    for i in 0..TEST_SIZE {
        flow.src_ip = i as u32;
        map.insert(flow, flow);
    }

    let mut dummy: u32 = 0;
    let end = unsafe { core::arch::x86_64::__rdtscp(&mut dummy) };
    let duration = end - start;

    println!("Benchmark results for rust flow with wyhash");
    println!("Duration: {} cycles", duration);
    println!("Insertions: {}", TEST_SIZE);
    println!("Cycles per insertion: {} cycles", duration as f64 / TEST_SIZE as f64);
    println!();
}

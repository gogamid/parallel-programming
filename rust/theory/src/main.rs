fn main() {
    let mut v = Vec::new();
    v.push(1);
    v.push(2);

    // move ownership
    take(v);
    // error: use of moved variable v
    //v.push(1);

    let mut v1 = Vec::new();
    //borrowing
    push(&mut v1);
    //borrowing
    read(&v1);
}

//take owns the v
fn take(v: Vec<i32>) {
    println!("v[0] = {}", v[0]);
}

//push borrows the v and can modify it
fn push(v: &mut Vec<i32>) {
    v.push(1);
}

//read borrows the v and can't modify it
fn read(v: &Vec<i32>) {
    println!("v[0] = {}", v[0]);
}

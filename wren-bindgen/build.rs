use std::env;
use std::path::PathBuf;

fn main() {
    println!("cargo:rerun-if-changed=wrapper.h"); // invalidate the built crate if warpper.h changes

    cc::Build::new()
        .file("wren-c/src/vm/wren_compiler.c")
        .file("wren-c/src/vm/wren_core.c")
        .file("wren-c/src/vm/wren_debug.c")
        .file("wren-c/src/vm/wren_primitive.c")
        .file("wren-c/src/vm/wren_utils.c")
        .file("wren-c/src/vm/wren_value.c")
        .file("wren-c/src/vm/wren_vm.c")
        .file("wren-c/src/optional/wren_opt_meta.c")
        .file("wren-c/src/optional/wren_opt_random.c")
        .includes(["wren-c/src/include", "wren-c/src/optional", "wren-c/src/vm"])
        .compile("wren");

    let bindings = bindgen::Builder::default()
        .header("wrapper.h")
        .clang_args(["-Iwren-c/src/include", "-Iwren-c/src/optional", "-Iwren-c/src/vm",
                     "-Wno-unused-parameter", "-Wno-unused-variable"])
        .parse_callbacks(Box::new(bindgen::CargoCallbacks))
        .generate()
        .expect("unable to generate bindings");

    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    bindings
        .write_to_file(out_path.join("bindings.rs"))
        .expect("couldn't write bindings..");
}
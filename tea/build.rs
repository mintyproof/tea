/// this step is necesasry for our bundled SDL2 build to behave when distributing on macOS and Linux.
///
/// from [Rust-SDL2's](https://github.com/Rust-SDL2/rust-sdl2) GitHub page:
/// > By default, macOS and Linux only load libraries from system directories like /usr/lib.
/// > If you wish to distribute the newly built libSDL2.so/libSDL2.dylib alongside your executable,
/// > you will need to add rpath to your executable.
fn add_rpath_to_executable() {
    #[cfg(target_os = "macos")]
    println!("cargo:rustc-link-arg=-Wl,-rpath,@loader_path");
    #[cfg(target_os = "linux")]
    println!("cargo:rustc-link-arg=-Wl,-rpath,$ORIGIN");
}

fn main() {
    add_rpath_to_executable();
}

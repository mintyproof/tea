// windows only- this prevents a console window from automatically appearing alongside tea when running in release mode!
#![cfg_attr(not(debug_assertions), windows_subsystem = "windows")]

fn main() {
    println!("Hello, world!");
}

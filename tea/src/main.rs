// windows only- this prevents a console window from automatically appearing alongside tea when running in release mode!
#![cfg_attr(not(debug_assertions), windows_subsystem = "windows")]

use std::env;

fn main() {
    let config = tea::Config {
        args: env::args().collect()
    };

    if let Err(e) = tea::run(config) {
        eprintln!("{}", e);
    }
}

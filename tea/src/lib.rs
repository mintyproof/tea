#![allow(unused_imports)]
#![allow(dead_code)]
#![recursion_limit = "512"] // lazy_static! invocation in gfx/colour.rs exceeds default recursion limit

pub mod core;
pub mod gfx;
pub mod implementations;

use implementations::{PlatformSDL2, RendererGL33};
use std::error::Error;

pub struct Config {
    pub args: Vec<String>,
}

pub fn run(_config: Config) -> Result<(), Box<dyn Error>> {
    let platform = PlatformSDL2::new();
    let renderer = RendererGL33 { };
    let mut engine = core::Engine::new(Box::new(platform), Box::new(renderer));
    while !engine.platform().should_quit() {
        engine.platform_mut().poll_events();
    }

    Ok(())
}

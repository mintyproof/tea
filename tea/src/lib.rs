#![allow(unused_imports)]
#![allow(dead_code)]
#![recursion_limit = "512"] // lazy_static! invocation in gfx/colour.rs exceeds default recursion limit

pub mod engine;
pub mod gfx;
pub mod implementations;
pub mod platform;

use implementations::{PlatformSDL2, RendererGL33};
use platform::PlatformSupportingOpenGL;
use std::error::Error;

pub struct Config {
    pub args: Vec<String>,
}

pub fn run(_config: Config) -> Result<(), Box<dyn Error>> {
    let platform = PlatformSDL2::new();
    let renderer = RendererGL33::new(|s| platform.gl_get_proc_address(s));
    let mut engine = engine::Engine::new(Box::new(platform), Box::new(renderer));
    while !engine.platform().should_quit() {
        engine.platform_mut().poll_events();
        engine.renderer_mut().test();
        engine.platform_mut().swap_buffers();
    }

    Ok(())
}

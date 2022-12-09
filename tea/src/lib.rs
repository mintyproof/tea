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
    let mut engine = core::Engine::new(Box::new(PlatformSDL2 {}), Box::new(RendererGL33 {}));
    println!("{}", engine.platform().get_name());
    println!("{}", engine.renderer().get_name());

    Ok(())
}

use crate::gfx::Renderer;

use gl::Gl;

pub struct RendererGL33 {}

impl RendererGL33 {
    pub fn new() -> Self {
        Self {}
    }
}

impl Renderer for RendererGL33 {
    fn get_name(&self) -> String {
        "OpenGL 3.3".to_owned()
    }
}

use crate::gfx::Renderer;

use gl::Gl;

pub struct RendererGL33 {
    gl: Gl,
}

impl RendererGL33 {
    pub fn new<F>(get_proc_address: F) -> Self
    where
        F: FnMut(&'static str) -> *const core::ffi::c_void,
    {
        Self {
            gl: Gl::load_with(get_proc_address),
        }
    }
}

impl Renderer for RendererGL33 {
    fn get_name(&self) -> String {
        "OpenGL 3.3".to_owned()
    }

    fn swap_buffers(&mut self) {
        
    }

    fn test(&mut self) {
        unsafe {
            self.gl.Viewport(0, 0, 800, 600);
            self.gl.ClearColor(0.0, 0.0, 0.5, 1.0);
            self.gl.Clear(gl::COLOR_BUFFER_BIT);
        }
    }
}

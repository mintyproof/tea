use crate::gfx::Renderer;

pub struct RendererGL33 {

}

impl Renderer for RendererGL33 {
    fn get_name(&self) -> String {
        "OpenGL 3.3".to_owned()
    }
}
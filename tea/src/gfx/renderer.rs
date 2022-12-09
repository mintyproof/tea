pub trait Renderer {
    /// returns a name identifying the renderer.
    fn get_name(&self) -> String;
}

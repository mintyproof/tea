pub trait Renderer {
    /// returns a name identifying the renderer.
    fn get_name(&self) -> String;

    fn swap_buffers(&mut self);
    
    fn test(&mut self);
}
